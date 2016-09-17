machine MotionPlanExecutor {
	var RState: machine;
	var RobotTP: machine;
	var currentLocation : int;
	model fun GotoLocation(rloc: int) : bool 
	{
		// In the simulation mode update the RobotStateManager
		// So that it knows that the state of robot has changed.
		// In the real-scenario the this function will move the robot to that location.
		currentLocation = rloc;
		//Do -1 only when you want to model the battery usage.
		//send RState, UpdateRobotState, (loc = rloc, battery = -1);
		send RState, UpdateRobotState, (loc = rloc, battery = 0);
		PRINT(currentLocation);
	}
	
	start state Init {
		entry {
			RState = (payload as (robot:machine, robotStManager:machine, currLoc:int)).robotStManager;
			RobotTP = (payload as (robot:machine, robotStManager:machine, currLoc:int)).robot;
			currentLocation = (payload as (robot:machine, robotStManager:machine, currLoc:int)).currLoc;
			
			raise local;
		}
		on local goto WaitForCommands;
	}
	
	state WaitForCommands {
		ignore CancelPlan;
		on ExecutePlan goto StartExecutingPlan with {
			currentPlan = payload.steps;
			assert(currentLocation == currentPlan[0]);
			currentPlan -= (0);
		};
		
	}
	
	var currentPlan: seq[int];
	state StartExecutingPlan {
		entry {
			if(sizeof(currentPlan) == 0)
			{
				raise done;
			}
			else
			{
				GotoLocation(currentPlan[0]);
				assert(currentLocation == currentPlan[0]);
				raise local;
			}	
		}
		on local goto StartExecutingPlan with { currentPlan -= (0); };
		on done goto WaitForCommands with {
			send RobotTP, ReachedDestination, currentLocation;
		};
		on CancelPlan goto WaitForCommands;
	}
	
}
