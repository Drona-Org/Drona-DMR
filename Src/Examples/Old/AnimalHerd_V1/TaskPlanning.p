//We will model the animal Herding example from Pappas paper.
/*
The map under consideration is a 4 x 4 matrix
-------------------------------
CAT_CAGE | Dog | 	| DOG_CAGE |
-------------------------------
		 | NC  |    |         |
-------------------------------
Mice 	 | NC  | cat | 		   |
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
---------------------------------------------------------


*/

include "Executor.p"
include "Properties.p"
include "Environment.p"
//common local events
event done;
event local;


main machine StartMachine {
	var robotMachine : machine;
	var envMachine : machine;
	var scanLocations : seq[int];
	var objectsLocation : map[int, (dog: bool, cat: bool, mice: bool)];
	var iter : int;
	start state Init {
		entry {
		
			//set up all the monitors
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
			//initialize the environment
			iter = 1;
			while(iter <= 16)
			{
				if(iter == 2)
					objectsLocation[iter] = (dog = false, cat = false, mice = true);
				else if(iter == 5)
					objectsLocation[iter] = (dog = true, cat = false, mice = false);
				else if(iter == 10)
					objectsLocation[iter] = (dog = false, cat = true, mice = false);
				else
					objectsLocation[iter] = (dog = false, cat = false, mice = false);
				
				iter = iter + 1;
			}
			
			envMachine = new Environment(objectsLocation);
			
			//initialize the robot.
			iter = 16;
			while(iter >= 1)
			{
				scanLocations += (0, iter);
				iter = iter - 1;
			}
			robotMachine = new Robot((envMachine, scanLocations, 1));
			raise halt;
		}

	}
}

//receives from MP
event LocationChange : int;
event GoalLocationReached : int;
//receives from Env
event SensorOutput : (loc:int, st:(dog: bool, cat: bool, mice: bool));
//local events
event StartScanning;
event StartHerding;
event returnBack;
event switch_To_GoToCageMode;

//The robot works in two modes
//1> Scanning Mode.
//2> Herding to Cage Mode.
machine Robot {
	var scanLocations : seq[int];
	var currLocation : int;
	var envMachine : machine;
	var executor : machine;
	var iter:int;
	var retVal:int;
	var currSensorState : (dog: bool, cat: bool, mice: bool);
	var herdingDog : bool;
	var herdingCat : bool;
	var herdingMice : bool;
	var herdingTogether : int; //0:dog, 1:cat, 2:mice
	
	start state Init {
		entry{
			envMachine = (payload as (machine, seq[int], int)).0;
			scanLocations = (payload as (machine, seq[int], int)).1;
			currLocation = (payload as (machine, seq[int], int)).2;
			executor = new Executor(this, currLocation);
			herdingTogether = -1;
			raise StartScanning;
		}
		on StartScanning goto ScanningMode;
	}
	
	fun GetNextLocation() : int {
		iter = 0;
		while(true)
		{
			if(iter == sizeof(scanLocations))
				iter = 0;
			
			if(scanLocations[iter] == currLocation)
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
	
	var nextLocation : int;
	state ScanningMode {
		entry {
			nextLocation = GetNextLocation();
			send executor, GotoGoalLocation, (curr = currLocation, dest = nextLocation);
		}
		on LocationChange push SenseEnvironment;
		on GoalLocationReached push SenseEnvironment;
		on returnBack goto ScanningMode;
		on switch_To_GoToCageMode goto GoToCageMode;
		
		exit SendMoveNext;
	}

	state SenseEnvironment {
		entry {
			currLocation = payload as int;
			send envMachine, SenseEnv, (robot = this, loc = currLocation);
		}
		on SensorOutput do {
			assert(currLocation == payload.loc);
			currSensorState = payload.st;
			raise local;
		};
		on local goto TakeActionOnSensorOutput;
	}
	
	state TakeActionOnSensorOutput {
		entry {
			if(herdingCat || herdingDog || herdingMice)
			{
				if(currSensorState.dog && !herdingCat)
				{
					monitor M_sDog;
					monitor M_hDog;
					if(herdingMice)
						herdingTogether = 0;
					
					currSensorState.dog = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
				}
				if(currSensorState.mice && !herdingCat)
				{
					monitor M_sMice;
					monitor M_hMice;
					if(herdingDog)
						herdingTogether = 2;
					
					currSensorState.mice = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
				}
				if(currSensorState.cat && !herdingMice && !herdingDog)
				{
					monitor M_sCat;
					monitor M_hCat;
					currSensorState.cat = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
				}
				raise returnBack; // this should lead to pop;
			}
			else{
				if(currSensorState.dog)
				{
					monitor M_sDog;
					monitor M_hDog;
					herdingDog = true;
					
					if(currSensorState.mice)
					{
						monitor M_sMice;
						monitor M_hMice;
						herdingTogether = 2;
					}	
					currSensorState.mice = false; currSensorState.dog = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
					
					raise StartHerding;
					
				}
				else if(currSensorState.cat)
				{
					monitor M_sCat;
					monitor M_hCat;
					herdingCat = true;
					currSensorState.cat = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
					
					raise StartHerding;
					
				}
				else if(currSensorState.mice)
				{
					monitor M_sMice;
					monitor M_hMice;
					herdingMice = true;
					currSensorState.mice = false;
					send envMachine, ActuateEnv, (loc = currLocation, st = currSensorState);
					raise StartHerding;
				}
				else
				{
					raise returnBack;
				}
			}
		}
		on StartHerding goto SelectCageBasedOnAnimal;
	}
		
	
	state SelectCageBasedOnAnimal {
		entry {
			if(herdingDog)
			{
				nextLocation = 13;
			}
			else if(herdingMice)
			{
				nextLocation = 16;
			}
			else if(herdingCat)
			{
				nextLocation = 4;
			}
			else
				assert(false);
			
			raise switch_To_GoToCageMode;
		}
	}
	fun SendMoveNext () {
		send executor, MoveNext;
	}
	state GoToCageMode {
		entry {
			send executor, GotoGoalLocation, (curr = currLocation, dest = nextLocation);
		}
		on LocationChange push SenseEnvironment;
		on GoalLocationReached push DoPendingHerd;
		on done goto ScanningMode;
		on returnBack do SendMoveNext;
		on switch_To_GoToCageMode goto GoToCageMode;
		
		exit SendMoveNext;
	}
	
	state DoPendingHerd { 
		entry {
			currLocation = payload;
			herdingDog = false; herdingCat = false; herdingMice = false;
			//monitor which goal state have I reached
			if(nextLocation == 13)
				monitor M_rDog;
			else if(nextLocation == 16)
				monitor M_rMice;
			else
				monitor M_rCat;
			
			if(herdingTogether == 0)
			{
			 herdingTogether = -1;
			 herdingDog = true;
			 raise StartHerding;
			}
			else if(herdingTogether == 2)
			{
			 herdingTogether = -1;
			 herdingMice = true;
			 raise StartHerding;
			}
			else
			{
			 herdingTogether = -1;
			 raise done; // pop;
			}
		} 
		on StartHerding goto SelectCageBasedOnAnimal;
	 }
	
}

