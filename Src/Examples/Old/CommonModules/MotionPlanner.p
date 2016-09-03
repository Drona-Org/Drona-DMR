/*************************************************************
The motion planner interacts with the robot task planner and generates motion plan to the 
destination location.
**************************************************************/
static model fun InvokeMotionPlanner(startConfiguration: int, endConfiguration: int, currentObstacles:seq[int]) {
	InitializeObstacles(currentObstacles);
	GetPath(startConfiguration, endConfiguration);
}

static model fun GetPath(c : int, d : int) [invokeplugin = GenerateMotionPlan] {}
	   
static model fun AddObstacle(a : int) [invokeplugin = AddObstacle] {}

static model fun ResetObstacle() [invokeplugin = ResetObstacle] {}

static model fun InitializeObstacles(obs: seq[int])
{
	var iter:int;
	iter = 0;
	ResetObstacle();
	while(iter < sizeof(obs))
	{
		AddObstacle(obs[iter]);
		iter = iter + 1;
	}
}

event newPlan : seq[int];
machine MotionPlanner {
	var RobotTP: machine;
	var Obstacles: seq[int];
	var AllMotionPlans : map[(int, int), seq[int]];
	start state Init {
		entry {
			RobotTP = payload as machine;
			Obstacles = GetStaticObstacles();
			AllMotionPlans = InitializeMotionPlanning();
			raise local;
		}
		on local goto WaitForCommands;
	}

	model fun GetMotionPlan(source:int, dest: int, obs:seq[int]) : seq[int]
	{
		if((source,dest) in AllMotionPlans)
		{
			return AllMotionPlans[(source, dest)];
		}
		else
		{
			InvokeMotionPlanner(source, dest, Obstacles);
		}
	}
	model fun KillMotionPlanner() 
	{
		
	}
	
	state WaitForCommands {
		on GeneratePlanFor do ComputeMotionPlanAndSend;
		
	}
	
	fun ComputeMotionPlanAndSend() {
		var source : int;
		var destination : int;
		var plan : seq[int];
		destination = payload.dest;
		source = payload.src;
		plan = GetMotionPlan(source, destination, Obstacles);
		if(sizeof(plan) == 0)
		{
			assert(false);
			send RobotTP, FailureToComputePlan;
		}
		else
		{
			send RobotTP, MotionPlanFor, (src = source, dest = destination, steps = plan);
		}

	}
}
