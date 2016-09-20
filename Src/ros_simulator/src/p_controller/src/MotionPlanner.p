event ePlanCompletion : int;

machine MotionPlannerMachine {
	var planExecutor: machine;
	
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
			planExecutor = new PlanExecutorMachine(this);
			goto SendCommandLoop;
		}
	}

	state SendCommandLoop {
		entry {
			send planExecutor, eStartExecutingPlan, trajs[0];
			trajs -= 0;
		}
		on ePlanCompletion goto SendCommandLoop;
		ignore ePlanExecutorMachine;
	}
}