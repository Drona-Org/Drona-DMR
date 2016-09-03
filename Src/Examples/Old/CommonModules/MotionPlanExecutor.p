/*****************************************************************************************
The MotionPlanExecutor is responsible for performing the task of executing the motion plan, which is the
sequence of motion primitives returned by the motionPlanner (complan).
The MotionPlanExecutor interacts with:
1) Task Planner 
2) RobotStateManager

The MotionPlanExecutor receives the following events:
From TaskPlanner:
1) GotoGoalLocation: int, the motion planner takes the robot to this location and hovers there.
2) CancelPlan, the motionPlanner and executor, cancel the operation they are performing and start hovering at the current location.

The MotionPlanExecutor send the following events:
To TaskPlanner:
1) GoalLocationReached: int.
2) FailedToReachGoal:int.

To RobotStateManager:
The MotionPlanExecutor informs the RobotStateManager when it changes its state/location using a motion primitive.

******************************************************************************************

/**************************************************************************
Defining the motion primitives used in motion planning.

If not Way point based ---
1) PerformHovering()
2) PerformMoveLeft()
3) PerformMoveRight()
4) PerformMoveUp()
5) PerformMoveDown()

If way point based ---
1) GotoRelativeLocation()
**************************************************************************/



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
