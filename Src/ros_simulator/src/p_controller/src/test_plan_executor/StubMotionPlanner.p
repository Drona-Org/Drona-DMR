event ePlanCompletion : int;

model fun RosInit(robotId: int)
{

}

model fun StartExecutingPath(path: seq[int], robotId: int)
{

}

machine StubMotionPlannerMachine {
	var robot_id : int;
	var trajs : seq[seq[int]];

	start state Init {
		entry {
			var traj:seq[int];
			robot_id = 0;
			RosInit(robot_id);
			traj += (0, 0);
			traj += (1, 1);
			traj += (2, 17);
			traj += (3, 16);			
			traj += (4, 0);
			trajs += (0, traj);
			goto SendCommandLoop;
		}
	}

	state SendCommandLoop {
		entry {
			StartExecutingPath(trajs[0], robot_id);
			trajs -= 0;
			if(sizeof(trajs) > 0) {
				goto SendCommandLoop;
			}
		}
	}
}