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

	state StartSendingTaskRequest {
		entry {
			
			goto StartSendingTaskRequest;
		}
		
	}
}

