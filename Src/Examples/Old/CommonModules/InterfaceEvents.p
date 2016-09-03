/****************************************************************
This file contains the interface events between different modules
*****************************************************************/

//Events received by Environment from RobotStateManager.
event GetEnv : (rtStateManager:machine, loc: int);
//the set event can also come from the RobotTaskPlanner in case it wants to actuate ...
event SetEnv : (loc: int, envState:any);

//Events received by RobotStateManager from Environment
event EnvState : (loc : int, envState : any);
event UpdateRobotState : (loc:int, battery:int);
//From SenseAndInfer
event GetRobotState assume 2;

//Events received by MotionPlanExecutor from Robot TaskPlanner 
event ExecutePlan: (steps:seq[int]);
event CancelPlan;

//Events received by MotionPlanner from RobotTaskPlanner
event GeneratePlanFor : (src:int, dest:int);
event CancelOperation;

//Events received by RobotTaskPlanner from MotionPlanner
event MotionPlanFor : (src:int, dest:int, steps:seq[int]);
event FailureToComputePlan;

//Event received by RobotTaskPlanner from MotionPlanExecutor
event ReachedDestination : int;
event FailureExecuting;
event CancelSucess: int;
//Event received by RobotTaskPlanner from SenseAndInfer
event BatteryLow : int;
event EnvEventDetected assume 1 : (loc:int, envState: any);


//Events received by SenseAndInfer from RobotStateManager
event CurrentState assume 2 : (robot:(loc:int, battery:int), envState:any) ;
//Events received by SenseAndInfer from motionPlanner and RobotTaskPlanner
//event GetRobotState;

// Events for interaction with the timer
// events from client to timer
event START: int;
event CANCEL;
// events from timer to client
event TIMEOUT: machine;
event CANCEL_SUCCESS: machine;
event CANCEL_FAILURE: machine;


//Local events used for raise
event local;
event done;
event initial_setup: any;
