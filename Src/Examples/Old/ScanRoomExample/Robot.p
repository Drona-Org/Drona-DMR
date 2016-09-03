
/*
The scenario for this example is as explained below:

-------------------------------
 S | X |   |   |   | BC|
-------------------------------
   | X | X |   | X |   |
-------------------------------
   |   | X |   | X |   |
-------------------------------
   |   |   | S | X |   |
-------------------------------

-------------------------------
4 | 5 | 12	| 13   | 20 | 21 |
-------------------------------
3  | 6  | 11  |14 | 19 | 22 |
-------------------------------
2  | 7  | 10 | 	15 | 18 | 23 |
-------------------------------
1  |  8  | 9 | 16  | 17 | 24 |
-------------------------------

X -> represents the static obstacles.
S -> represents the possible starting positions
BC -> represents the battery charging point.

There is an external controller that detects new goals and instructs the drone to go that that goal location.
The drone has to go to that goal location and wait for other instruction.

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


/* main driver machine */
main machine DriverMachine {
	var robot:machine;
	var envMachine: machine;
	var robotStMng: machine;
	
	start state Init {
		entry {
			//create all the monitors 

			
			//create all the simulation machines
			envMachine = new Environment();
			robotStMng = new RobotStateManager((robotst = ROBOT_START_STATE(), envM = envMachine));
			
			//create the robot task planner machine
			robot =  new RobotTaskPlanner((envMachine, robotStMng));
			raise halt;
		}
		
	}
	
}


event ReDo;
event success;
event TakePictureOf: (machine, int);
event returnBack;
event Picture;
machine RobotTaskPlanner {
	var senseInfer:machine;
	var envMachine:machine;
	var robotStMng: machine;
	var motionPlanner:machine;
	var motionPlanEx:machine;
	var currentRobotState:(loc:int, battery:int);
	var scanLocations : seq[int];
	var requests: seq[(machine, int)];
	
	//temp variables
	var iter: int;
	var retVal : int;
	
	start state Init {
		entry {
			envMachine = (payload as (machine, machine)).0;
			robotStMng = (payload as (machine, machine)).1;
			currentRobotState = ROBOT_START_STATE();
			scanLocations = ROBOT_SCAN_LOCATIONS(scanLocations, scanLocations, 0);
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
		on local goto WaitForNextCommand;
	}
	
	
	
	var nextLocation: int;
	state WaitForNextCommand {
		entry {
			UpdateCurrentRobotState();
		}
		on TakePictureOf goto SelectGoalLocationAndMove with {
			requests += (sizeof(requests), payload);
			nextLocation = requests[0].1;
		};
	}
	
	state SelectGoalLocationAndMove {
		entry {
			UpdateCurrentRobotState();
			send motionPlanner, GeneratePlanFor, (src = currentRobotState.loc, dest = nextLocation);
			
		}
		on returnBack goto WaitForNextCommand;
		on BatteryLow goto LowBatteryDetected with CancelCurrentExecution;
		on TakePictureOf do { requests += (0, payload);};
		on MotionPlanFor push ExecutePlan;
		on FailureToComputePlan do { /*not implemented*/ assert(false);};
		on ReDo goto SelectGoalLocationAndMove;
		on success do {
			send requests[0].0, Picture;
			requests -= (0);
			if(sizeof(requests) == 0)
				raise returnBack;
			else
			{
				nextLocation = requests[0].1;
				raise ReDo;
			}
		};
	}
	
	fun CancelCurrentExecution() {
		//can the current executor
		send motionPlanEx, CancelPlan;
	}
	
	state ExecutePlan {
		entry {
			if(payload.src != currentRobotState.loc || payload.src != nextLocation)
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
			};
			
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
		on TakePictureOf do { requests += (0, payload);};
		on success goto SelectGoalLocationAndMove with 
		{
			if(sizeof(requests) == 0)
				nextLocation = WAIT_LOCATION();
			else
			{
				nextLocation = requests[0].1;
			}
		};
	}
}

machine ExternalController {
	var RobotMach: machine;
	var GoalLocations : seq[int];
	
	start state Init {
		entry {
			//set of goal locations to be visited by the robot and taken picture of.
			GoalLocations += (0, 14);
			GoalLocations += (0, 7);
			GoalLocations += (0, 23);
			RobotMach = payload as machine;
			raise local;
		}
		on local goto StartSendingCommands;
	}
	
	state StartSendingCommands {
		entry {
			if(sizeof(GoalLocations) == 0)
			{
				raise halt;
			}
			send RobotMach, TakePictureOf, (this, GoalLocations[0]);
			
		}
		on Picture goto StartSendingCommands with {
			GoalLocations -= (0);
		};
		
	}
}

