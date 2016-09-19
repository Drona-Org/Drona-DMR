event ePlanExecutorMachine: machine;
event eStartExecutingPlan : TimedTrajType;

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

			currTimePeriod = GetCurrentTimePeriod(localTimeV, robotId);
			if(currTimePeriod - payload[0].0 > 0)
			Sleep(currTimePeriod - payload[0].0);
			index = 0;
			while(index < sizeof(payload))
			{
				traj += (index, payload[index].1);
			    index = index + 1;
			}

			StartExecutingPath(traj, robotId);

			send motionplanner, ePlanCompletion, traj[sizeof(traj)];
		}
	}
}

