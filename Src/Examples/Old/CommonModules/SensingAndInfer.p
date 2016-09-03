/*********************************************************************************************
This machine senses the environment and Infers the state of the robot and its surrounding.
*********************************************************************************************/

event infer;
machine SenseAndInfer {
	var robotTP: machine;
	var robotStManager:machine;
	var currentRobotState: (robot:(loc:int, battery:int), envState:any);
	start state Init {
		entry {
			robotTP = (payload as (machine, machine)).0;
			robotStManager = (payload as (machine, machine)).1;
			send robotStManager, initial_setup, this;
			raise local;
		}
		on local goto PeriodicallySenseUpdate;
	}
	
	state PeriodicallySenseUpdate {
		entry {

		}
		on null push SenseEnvironment;
		on GetRobotState do { 
			
			//sense the environment now.
			send robotStManager, GetRobotState;
			receive {
				case CurrentState: {currentRobotState = payload as (robot:(loc:int, battery:int), envState:any);}
			}
			InferCurrentStateAndInformTPorMP();
			send robotTP, CurrentState, currentRobotState; 
		};
	}
	
	state SenseEnvironment {
		defer GetRobotState; //defer requests from MP and TP
 		entry {
			send robotStManager, GetRobotState;
			receive {
				case CurrentState: {currentRobotState = payload as (robot:(loc:int, battery:int), envState: any);}
			}
			InferCurrentStateAndInformTPorMP();
			pop;
		}
	}

	fun InferCurrentStateAndInformTPorMP() {
		if(currentRobotState.robot.battery < BATTERY_THRESHOLD())
		{
			send robotTP, BatteryLow, currentRobotState.robot.battery;
		}
		if(currentRobotState.envState != null)
		{
			if(EventDetected(currentRobotState.envState))
			{
				send robotTP, EnvEventDetected, (loc = currentRobotState.robot.loc, envState = currentRobotState.envState);
			}
		}
	}
}