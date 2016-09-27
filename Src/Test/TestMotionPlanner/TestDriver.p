include "..\..\SoftwareStack\MotionPlanner\DAMP.p"
include "..\..\SoftwareStack\MotionPlanExecutor\MotionPlanExecutor.p"
include "..\..\SoftwareStack\MotionPlanner\DistributedTimeSync.p"
include "..\..\Lib\WorkspaceParser\WorkspaceAPI.p"
include "..\..\SoftwareStack\Utilities\Timer\Timer.p"
include "Robot.p"

machine Main
{
	var allRobotsV : seq[machine];
	var timeSyncV: machine;
	fun InitializeSystem() {
		var noOfRobots: int;
		var robotInfo: RobotInfoType;
		var robot: machine;
		var index : int;

		//create the porb machine
		noOfRobots = GetNumOfRobots();
		index = 0;
		while(index < noOfRobots)
		{
			robotInfo = GetRobotInfo(index);
			robot = new RobotMachine(robotInfo);
			allRobotsV += (0, robot);
			index = index + 1;
		}
		//create the Distributed time-sync machine
		timeSyncV = new DistributedTimeSyncMachine(allRobotsV);

		BROADCAST(allRobotsV, eAllRobots, (allrobots = allRobotsV, timesync = timeSyncV), this);
		
	}
	start state Init {
		entry {
			InitializeSystem();
			goto StartSendingTaskRequest;
		}
	}

	model fun ExitP() {}

	var goalLocations: seq[int];
	var taskscompleted: int;
	state StartSendingTaskRequest {
		entry {
			//all the potential goal locations 
			var robotid: int;
			var counter: int;
			
			var noOfRobots: int;

			goalLocations = GetGoalLocations();
			noOfRobots = GetNumOfRobots();

			robotid = 0;
			counter = 0;
			//task task
			while(counter < sizeof(goalLocations))
			{
				send allRobotsV[robotid], eNewTask, (g = goalLocations[counter], source = this);
				counter = counter + 1;
				robotid = robotid + 1;
				if(robotid >= noOfRobots)
					robotid = 0;
			}
		}
		
		on eTask_completed do {
			taskscompleted = taskscompleted + 1;
			if(taskscompleted == sizeof(goalLocations))
			{
				ExitP();
			}
		}
	}
}

