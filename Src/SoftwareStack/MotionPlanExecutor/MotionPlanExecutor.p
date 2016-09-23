event ePlanExecutorMachine: machine;
event eStartExecutingPlan : TimedTrajType;

model fun RosInit(robotId: int)
{

}

fun InvokeStartExecutingPathAndWait(path: seq[int], robotId: int, timesync: machine)
{

	var currTimePeriod: int;
	var expectedEndTime: int;
	currTimePeriod = GetCurrentTimePeriod(timesync, robotId, this);
	expectedEndTime = sizeof(path) + currTimePeriod;

	//start executing path
	StartExecutingPath(path,robotId);
	
	currTimePeriod = GetCurrentTimePeriod(timesync, robotId, this);
	if(currTimePeriod < expectedEndTime) {
		Sleep((expectedEndTime - currTimePeriod)*MotionPrimitiveTimePeriod());
	}
}

model fun StartExecutingPath(path: seq[int], robotId: int)
{

}

model fun Sleep(time: int)
{

}

machine PlanExecutorMachine {
	var motionplanner: machine;
	var robotId: int;
	var localTimeV: machine;
	start state Init {
		entry(payload: (mp: machine, rid: int)) {
			motionplanner = payload.mp;
			robotId = payload.rid;
			RosInit(robotId);
			send motionplanner, ePlanExecutorMachine, this;
			receive {
				case eTimeSyncId: (ts: machine) { localTimeV = ts; }
			}
			goto WaitForPathToExecute;
		}
	}

	state WaitForPathToExecute {
		on eStartExecutingPlan do (payload: TimedTrajType) {
			var currTimePeriod: int;
			var traj: seq[int];
			var index: int;

			currTimePeriod = GetCurrentTimePeriod(localTimeV, robotId, this);
			if(currTimePeriod - payload[0].0 < 0)
			Sleep((payload[0].0 - currTimePeriod)*MotionPrimitiveTimePeriod());
			index = 0;
			while(index < sizeof(payload))
			{
				traj += (index, payload[index].1);
			    index = index + 1;
			}

			InvokeStartExecutingPathAndWait(traj, robotId, localTimeV);

			send motionplanner, ePlanCompletion, traj[sizeof(traj) - 1];
		}
	}
}

