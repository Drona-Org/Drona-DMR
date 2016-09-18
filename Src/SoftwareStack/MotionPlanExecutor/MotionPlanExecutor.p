event ePlanExecutorMachine: machine;

machine PlanExecutorMachine {
	var motionplanner: machine;
	start state Init {
		entry(payload: machine) {
			motionplanner = payload;
			send motionplanner, ePlanExecutorMachine, this;
		}
	}
}

