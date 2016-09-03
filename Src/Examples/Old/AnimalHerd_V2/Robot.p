//We will model the animal Herding example from Pappas paper.
/*
The map under consideration is a 4 x 4 matrix
-------------------------------
CAT_CAGE | Dog | 	| DOG_CAGE |
-------------------------------
		 | NC  |    |         |
-------------------------------
Mice 	 | NC  | cat | BC   |
-------------------------------
start    |     | NM  | Mice_CAG|
-------------------------------

-------------------------------
4 | 5 | 12	| 13   |
-------------------------------
3  | 6  | 11  |14 |
-------------------------------
2  | 7  | 10 | 	15 |
-------------------------------
1  |  8  | 9 | 16  |
-------------------------------

---------------------------------------------------------
	Program
---------------------------------------------------------*/

include "..\CommonModules\MotionPlanner.p"
include "..\CommonModules\MotionPlanExecutor.p"
include "..\CommonModules\Environment.p"
include "..\CommonModules\HelperFunctions.p"
include "..\CommonModules\InterfaceEvents.p"
include "ModelOfMotionPlanning.p"
include "Globals.p"
include "..\CommonModules\RobotStateManager.p"
include "..\CommonModules\SensingAndInfer.p"
include "..\CommonModules\Timer.p"
include "Properties.p"


/* main driver machine */
main machine DriverMachine {
	var robot:machine;
	var envMachine: machine;
	var robotStMng: machine;
	
	start state Init {
		entry {
			//create all the monitors 
			new Prop_1();
			new Prop_2();
			new Prop_3(3);
			new Prop_6();
			new Prop_7();
			new Prop_8();
			new Prop_9();
			new Prop_10a();
			new Prop_10b();
			new Prop_10c();
			
			//create all the simulation machines
			envMachine = new Environment();
			robotStMng = new RobotStateManager((robotst = ROBOT_START_STATE(), envM = envMachine));
			
			//create the robot task planner machine
			robot =  new RobotTaskPlanner((envMachine, robotStMng));
			raise halt;
		}
		
	}
	
}


//local events 
event ReDo;
event success;
event doScanning;
event startNewHerding;
event continueCurrentHerding;

machine RobotTaskPlanner {
	var senseInfer:machine;
	var envMachine:machine;
	var robotStMng: machine;
	var motionPlanner:machine;
	var motionPlanEx:machine;
	var currentRobotState:(loc:int, battery:int);
	var currentSensorState: (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool);
	var scanLocations : seq[int];
	
	var herdingState : (herdingDog:bool, herdingCat:bool, herdingMice:bool);
	var herdingTogether : int;
	

	start state Init {
		entry {
			envMachine = (payload as (machine, machine)).0;
			robotStMng = (payload as (machine, machine)).1;
			currentRobotState = ROBOT_START_STATE();
			herdingState = (herdingDog = false, herdingCat = false, herdingMice = false);
			scanLocations = ROBOT_SCAN_LOCATIONS();
			raise local;
			
		}
		on local goto SetUpSystem;
		
	}
	
	state SetUpSystem {
		entry {
			senseInfer = new SenseAndInfer((this, robotStMng));
			motionPlanner = new MotionPlanner(this);
			motionPlanEx = new MotionPlanExecutor((robot = this, robotStManager = robotStMng, currLoc = currentRobotState.loc));
			raise local;
		}
		on local goto ScanningModeOfOperation;
	}
	
	
	//scanning algorithm
	fun GetNextScanLocation() : int 
	{
		var iter:int;
		var retVal : int;
		iter = 0;
		while(true)
		{
			if(iter == sizeof(scanLocations))
				iter = 0;
			
			if(scanLocations[iter] == currentRobotState.loc)
			{
				if(iter + 1 < sizeof(scanLocations))
				{
					retVal = scanLocations[iter + 1];
				}
				else
				{
					retVal = scanLocations[0];
				}
				return retVal;
			}
			else
			{
				iter = iter + 1;
			}	
		}
	}
	
	var nextLocation: int;
	state ScanningModeOfOperation {
		entry {
			UpdateCurrentRobotState();
			nextLocation = GetNextScanLocation();
			send motionPlanner, GeneratePlanFor, (src = currentRobotState.loc, dest = nextLocation); 
		}
		on MotionPlanFor push ExecutePlan;
		on FailureToComputePlan do { /*not implemented*/ assert(false);};
		on BatteryLow goto LowBatteryDetected with CancelCurrentExecution;
		on startNewHerding goto SelectGoalLocationAndComputePlan with CancelCurrentExecution;
		on EnvEventDetected push TakeActionOnEnvEventDetected;
		on ReDo goto ScanningModeOfOperation;
		on success goto ScanningModeOfOperation;
	}
	
	fun CancelCurrentExecution() {
		//can the current executor
		send motionPlanEx, CancelPlan;
	}
	
	state ExecutePlan {
		ignore continueCurrentHerding;
		entry {
			PRINT(currentRobotState.loc);
			PRINT(payload.src);
			PRINT(nextLocation);
			PRINT(payload.steps);
			if(payload.src != currentRobotState.loc || payload.dest != nextLocation)
			{
				raise ReDo;
			}
			else
			{
				send motionPlanEx, ExecutePlan, (steps = payload.steps,);
			}
		}

		on ReachedDestination do { 
			currentRobotState.loc = payload;
			raise success;
		};
	}
	
	fun UpdateCurrentRobotState() {
		send senseInfer, GetRobotState;
		receive {
			case CurrentState : 
			{
				currentRobotState = payload.robot;
			}
		}
	}
	
	state LowBatteryDetected {
		defer EnvEventDetected;
		entry {
			UpdateCurrentRobotState();
			nextLocation = BATTERY_CHARGE_LOCATION();
			send motionPlanner, GeneratePlanFor, (src = currentRobotState.loc, dest = nextLocation); 
		}
		on MotionPlanFor push ExecutePlan;
		on FailureToComputePlan do { /*not implemented*/ assert(false);};
		on BatteryLow goto LowBatteryDetected with CancelCurrentExecution;
		on ReDo goto LowBatteryDetected;
		on success goto ScanningModeOfOperation;
	}
	
	state TakeActionOnEnvEventDetected {
		entry {
			UpdateCurrentRobotState();
			assert(currentRobotState.loc == payload.loc);
			currentSensorState = payload.envState as (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool);
			//If robot is already herding animal
			if(herdingState.herdingCat || herdingState.herdingDog || herdingState.herdingMice)
			{
				if(currentSensorState.isDogPresent && !herdingState.herdingCat)
				{
					monitor M_sDog; monitor M_hDog;
					if(herdingState.herdingMice)
					{
						herdingTogether = DOG();
					}
					currentSensorState.isDogPresent = false;
				}
				if(currentSensorState.isMicePresent && !herdingState.herdingCat)
				{
					monitor M_sMice; monitor M_hMice;
					if(herdingState.herdingDog)
					{
						herdingTogether = MICE();
					}
					currentSensorState.isMicePresent = false;
				}
				if(currentSensorState.isCatPresent && !herdingState.herdingDog && !herdingState.herdingMice)
				{
					monitor M_sCat; monitor M_hCat;
					currentSensorState.isCatPresent = false;
				}
				raise continueCurrentHerding;
			}
			else
			{
				if(currentSensorState.isDogPresent)
				{
					monitor M_sDog; monitor M_hDog;
					herdingState.herdingDog = true;
					if(currentSensorState.isMicePresent)
					{
						monitor M_sMice; monitor M_hMice;
						herdingTogether = MICE();
					}
					currentSensorState.isMicePresent = false;
					currentSensorState.isDogPresent = false;
				}
				else if(currentSensorState.isCatPresent)
				{
					monitor M_sCat; monitor M_hCat;
					currentSensorState.isCatPresent = false;
					herdingState.herdingCat = true;
				}
				else if(currentSensorState.isMicePresent)
				{
					monitor M_sMice; monitor M_hMice;
					herdingState.herdingMice = true;
					currentSensorState.isMicePresent = false;
					
				}
				else
				{
					assert(false);
				}
				raise startNewHerding; 
			}
		}
		
	}
	
	state SelectGoalLocationAndComputePlan {
		ignore continueCurrentHerding;
		ignore ReachedDestination;
		entry {
			UpdateCurrentRobotState();
			if(herdingState.herdingDog)
				nextLocation = DOG_CAGE_LOC();
			else if(herdingState.herdingCat)
				nextLocation = CAT_CAGE_LOC();
			else if(herdingState.herdingMice)
				nextLocation = MICE_CAGE_LOC();
			else
				assert(false);
			
			send motionPlanner, GeneratePlanFor, (src = currentRobotState.loc, dest = nextLocation); 	
		}
		on MotionPlanFor push ExecutePlan; //push
		on FailureToComputePlan do { /*not implemented*/ assert(false);};
		on ReDo goto SelectGoalLocationAndComputePlan;
		on success do {
			if(herdingState.herdingCat)
				herdingState.herdingCat = !herdingState.herdingCat;
			else if(herdingState.herdingDog)
				herdingState.herdingDog = !herdingState.herdingDog;
			else if(herdingState.herdingMice)
				herdingState.herdingMice = !herdingState.herdingMice;
			
			if(herdingTogether != -1)
			{
				if(herdingTogether == MICE())
					nextLocation = MICE_CAGE_LOC();
				if(herdingTogether == DOG())
					nextLocation = DOG_CAGE_LOC();
				if(herdingTogether == CAT())
					nextLocation = DOG_CAGE_LOC();
				
				herdingTogether = -1;
				
				raise ReDo;
			}
			else 
				raise doScanning;
		};
		on doScanning goto ScanningModeOfOperation;
		on BatteryLow goto LowBatteryDetected with CancelCurrentExecution;
		on EnvEventDetected push TakeActionOnEnvEventDetected;
		
	}
	
	
}

