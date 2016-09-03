include "ModelOfMotionPlanning.p"


static model fun InvokeMotionPlanner(startConfiguration:int, endConfiguration:int, currentObstacles:seq[int]) {
	InitializeObstacles(currentObstacles, 0);
	GetPath(startConfiguration, endConfiguration);
}

static model fun GetPath(c : int, d : int) [invokeplugin = GenerateMotionPlan] {}
	   
static model fun AddObstacle(a : int) [invokeplugin = AddObstacle] {}

static model fun ResetObstacle() [invokeplugin = ResetObstacle] {}

static model fun InitializeObstacles(s: seq[int], iter:int)
{
	ResetObstacle();
	iter = 0;
	while(iter < sizeof(s))
	{
		AddObstacle(s[iter]);
		iter = iter + 1;
	}
}

//receives
event GotoGoalLocation : (curr:int, dest:int);
event MoveNext;

model Executor {
	var AllMotionPlans:map[(int, int), seq[int]];
	var seqToPerform : seq[int];
	var currLocation : int;
	var iter : int;
	var Robot : machine;
	
	//temp vars
	var tempSeq : seq[int];
	
	start state Init {
		entry {
			AllMotionPlans = InitializeMotionPlanning(tempSeq, AllMotionPlans);
			Robot = (payload as (machine, int)).0;
			currLocation = (payload as (machine, int)).1;
			raise done;
		}
		on done goto WaitForNextGoalLocation;
	}
	
	state WaitForNextGoalLocation {
		ignore MoveNext;
		on GotoGoalLocation push MoveUsingMotionPlanning;
		
	}
	
	model fun GetSeqFromComplan(curr: int, des:int) : seq[int] {
		//empty the retSeq;
		seqToPerform = default(seq[int]);
		if(des == curr + 1 || (curr == 16 && des == 1))
		{
			seqToPerform +=(0,des);
			seqToPerform +=(0, curr);
		}
		else{
			if((curr,des) in AllMotionPlans)
			{
				seqToPerform = AllMotionPlans[(curr,des)];
			}
			else
			{
				InvokeMotionPlanner(curr, des, default(seq[int]));
			}
		}
		
		return seqToPerform;

	}
	
	state MoveUsingMotionPlanning{
		entry {
			seqToPerform = GetSeqFromComplan(payload.curr, payload.dest);
			raise local;
		}
		on local goto ExecuteMotionPlan with {
			assert(currLocation == seqToPerform[0]);
			seqToPerform -=(0);
		};
		
	}
	
	state ExecuteMotionPlan {
		entry {
			//call the motion primitive to move to next position
			currLocation = seqToPerform[0];
			seqToPerform -= (0);
			if(sizeof(seqToPerform) == 0)
			{
				send Robot, GoalLocationReached, currLocation;
				raise done;
			}
			else 
			{
				send Robot, LocationChange, currLocation;
				
			}
			
		}
		on MoveNext goto ExecuteMotionPlan;
		on done do { pop; };
		
	}
}