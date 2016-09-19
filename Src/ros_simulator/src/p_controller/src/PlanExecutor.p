#include "MotionPlanner.p" 

event ePlanExecutorMachine: machine;
event eStartExecutingPlan: seq[int];

machine PlanExecutorMachine {
    var motionplanner: machine;
    var robotId: int;

    model fun RosInit(robotId : int)
    {
        
    }

    start state Init {
        entry(payload: machine) {
            motionplanner = payload;
            RosInit(robotId);
            send motionplanner, ePlanExecutorMachine, this;
            goto WaitForPathToExecute;
        }
    }

    model fun StartExecutingPath(path: seq[int], robotId : int)
    {
    
    }

    state WaitForPathToExecute {
        on eStartExecutingPlan do (traj: seq[int]) {

            StartExecutingPath(traj, robotId);

            send motionplanner, ePlanCompletion, traj[sizeof(traj)];
        }
    }
}

