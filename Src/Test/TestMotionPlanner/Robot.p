event eAllRobots: (allrobots: seq[machine], timesync: machine);
event eTimeSyncId : machine;

model fun RosInit(robotId: int, startL: int)
{

}

machine RobotMachine
{
	var robotid: int;
	var currentLocation: int;
	var motionplanner: machine;
	var planexecutor: machine;
	var allRobots: seq[machine];

	start state Init {
		entry(payload: RobotInfoType)
		{
			robotid = payload.robotid;
			currentLocation = payload.startpos;
			RosInit(robotid, payload.startpos);
			motionplanner = new DistributedMotionPlannerMachine(payload);
			planexecutor = new PlanExecutorMachine((mp = motionplanner, rid = robotid));
		}

		on eAllRobots do (payload: (allrobots: seq[machine], timesync: machine)) {
			allRobots = payload.allrobots;
			send motionplanner, eTimeSyncId, payload.timesync;
			send planexecutor, eTimeSyncId, payload.timesync;
			BROADCAST(allRobots, eDistMotionPlanMachine, motionplanner, this);
		}

		on eDistMotionPlanMachine do (payload: any) {
			send motionplanner, eDistMotionPlanMachine, payload as machine;
		}

		on eNewTask do (payload: TaskType){ send motionplanner, eNewTask, payload; }
	}
}

