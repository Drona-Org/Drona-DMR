event ePlanCompletion : int;

model fun RosInit(robotId: int)
{

}

model fun StartExecutingPath(path: seq[int], robotId: int)
{

}

machine StubMotionPlannerMachine {
	
	var trajs : seq[seq[int]];

	start state Init {
		entry {
			var traj:seq[int];
			traj += (0, 0);
			traj += (1, 1);
			traj += (2, 2);
			traj += (3, 3);			
			traj += (4, 7);			
			traj += (5, 6);
			trajs += (0, traj);
			goto SendCommandLoop;
		}
	}

	state SendCommandLoop {
		entry {
			StartExecutingPath(trajs[0], 0);
			if(sizeof(trajs) > 0) {
				goto SendCommandLoop;
			}
		}
	}
}