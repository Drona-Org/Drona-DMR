/***************************************************************************************************************************
RobotStateManager component is a model machine that maintains relevant state of the robot.
The SensingAndInfer component periodically interacts with this model machine during zing simulation
to get the current sensor data. 
In the real world execution the SensingAndInfer unit will communicate with the sensors directly.

In other worlds, RobotStateManager maintains information about the environment and the robot so that it can feedback 
information to the robot about its sensor data during simulation.

RobotStateManager interacts with :
1) SensingAndInfer
2) MotionPlannerAndExecutor


****************************************************************************************************************************/

machine RobotStateManager {
	//state of the robot currently contains only 2 things location and battery status
	var currentLocation: int;
	var batteryLevel:int;
	var EnvMachine:machine;
	var sensingMachine: machine;
	start state Init {
		entry {
			currentLocation = (payload as (robotst:(loc:int, battery:int), envM:machine)).robotst.loc;
			batteryLevel = (payload as (robotst:(loc:int, battery:int), envM:machine)).robotst.battery;
			EnvMachine = (payload as (robotst:(loc:int, battery:int), envM:machine)).envM;
			assert(batteryLevel > 0);
		}
		on initial_setup goto WaitForCommands with { sensingMachine = payload as machine; };
	}
	
	state WaitForCommands {
		on GetRobotState push GetStateFromEnvMachine;
		on UpdateRobotState do 
		{ 
			if(payload.loc == BATTERY_CHARGE_LOCATION())
			{
				currentLocation = payload.loc;
				batteryLevel = 30;
			}
			else
			{
				currentLocation = payload.loc; 
				batteryLevel = payload.battery + batteryLevel; 
			}

		};
	}
	
	state GetStateFromEnvMachine {
		defer UpdateRobotState, GetRobotState;
		entry {
			send EnvMachine, GetEnv, (rtStateManager = this, loc = currentLocation);
		}
		on EnvState do { 
			assert(payload.loc == currentLocation);
			send sensingMachine, CurrentState, (robot = (loc = currentLocation, battery = batteryLevel), envState = payload.envState);
			pop;
		};
	}
}