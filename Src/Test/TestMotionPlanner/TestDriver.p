include "..\..\SoftwareStack\MotionPlanner\DAMP.p"
include "..\..\SoftwareStack\MotionPlanExecutor\MotionPlanExecutor.p"
include "..\..\SoftwareStack\MotionPlanner\DistributedTimeSync.p"
include "..\..\SoftwareStack\Workspace\WorkspaceAPI.p"

machine Main
{
	var allRobotsV : seq[machine];
	var id : int;

	start state Init {
		entry {
			var numOfRobots: int;
			var robot: machine;
			numOfRobots = 3;
			//creates all robots
			id = 0;
			while(id < 3)
			{
				robot = new DistributedMotionPlannerMachine(id);
				allRobotsV += (id, robot);
			    id = id + 1;
			}

			//broadcast all robot information
			BROADCAST(allRobotsV, eConfiguration, allRobotsV);
			raise eUnit;
		}
		on eUnit goto StartSendingTaskRequest;
	}

	var taskid : int;
	state StartSendingTaskRequest {
		entry {
			var robotid : int;
			robotid = ChooseInt(sizeof(allRobotsV) - 1);
			send allRobotsV[robotid], eNewTask, (taskid= taskid, s= 0, g= 0);
			taskid = taskid + 1;
			if(taskid > 5)
				raise halt;
			else
				raise eUnit;

		}
		on eUnit goto StartSendingTaskRequest;
	}
}

