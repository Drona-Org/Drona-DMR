type TimedTrajType = seq[(int, int)];
type TaskType = (taskid: int, g: int);

event eRequestCurrentTraj : (priority : int, robot : machine);
event eCurrentTraj : (robot: machine, currTraj : TimedTrajType);
event eNewTask : TaskType;
event eDistMotionPlanMachine: machine;
event ePlanCompletion: int;

machine DistributedMotionPlannerMachine
{
	var allRobotsMPV : seq[machine];
	var allAvoidsV : map[machine, TimedTrajType];
	var currentTrajV : TimedTrajType;
	var myIdV : int;
	var currTaskV : TaskType;
	var receivedTrajFromV : map[machine, bool];
	var planExecutorV : machine;
	var currentLocationV: int;
	var localTimeV: machine;
	var pendingRequestsV: seq[machine];
	var numOfRobots: int;
	
	start state Init {
		defer eDistMotionPlanMachine;
		entry (rinfo: RobotInfoType) {
			myIdV = rinfo.robotid;
			currentLocationV = rinfo.startpos;
			receive {
				case ePlanExecutorMachine: (payload: machine){ planExecutorV = payload; }
			}
			receive {
				case eTimeSyncId: (payload: machine) { localTimeV = payload; }
			}
			goto GetAllDistMotionPlanners;
		}
		
	}

	state GetAllDistMotionPlanners {
		defer eNewTask, eRequestCurrentTraj;
		on eDistMotionPlanMachine do (payload: machine){
			numOfRobots = GetNumOfRobots();
			receivedTrajFromV += (payload, true);
			if(sizeof(keys(receivedTrajFromV)) == numOfRobots - 1)
			{
				allRobotsMPV = keys(receivedTrajFromV);
				receivedTrajFromV = default(map[machine, bool]);
				goto WaitForRequests;
			}
		}
	}

	state WaitForRequests {
		entry {
			//reset the currentTraj variable to current location
			currentTrajV = default(TimedTrajType);
			currentTrajV += (0, (0, currentLocationV));
		}
		//on receiving a new task update the local task variable and goto GetCurrentStateOfAllRobots
		on eNewTask goto GetCurrentStateOfAllRobots with (payload: TaskType) {
			var index: int;
			currTaskV = payload; 
			index = 0;
			while(index < sizeof(allRobotsMPV))
			{
				receivedTrajFromV[allRobotsMPV[index]] = false; // reset the map
				index = index + 1;
			}
		}
		//on receiving request for latest trajectory send the enpty list, informing that I am not performing any task
		on eRequestCurrentTraj do (target: (priority : int, robot : machine)) {
			send target.robot, eCurrentTraj, (robot = this, currTraj = currentTrajV);
		}
	}

	fun allTrajsReceived(TrajMap:  map[machine, bool]) : bool {
		var index :int;
		var robots : seq[machine];
		robots = keys(TrajMap);
		index = 0;
		while(index < sizeof(robots))
		{
			if(!TrajMap[robots[index]])
				return false;
		    index = index + 1;
		}
		return true;
	}

	state GetCurrentStateOfAllRobots {
		defer eNewTask;
		entry {
			//send to all the machines in allRobotsV
			BROADCAST(allRobotsMPV, eRequestCurrentTraj, (priority = currTaskV.taskid, robot = this), this);
			if(allTrajsReceived(receivedTrajFromV))
			{
				goto ComputeTrajState;
			}
		}
		on eCurrentTraj do (payload: (robot: machine, currTraj : TimedTrajType)){
			allAvoidsV[payload.robot] = payload.currTraj;
			assert (payload.robot in receivedTrajFromV);
			receivedTrajFromV[payload.robot] = true;
			if(allTrajsReceived(receivedTrajFromV))
			{
				goto ComputeTrajState;
			}

		}
		on eRequestCurrentTraj do (payload: (priority: int, robot: machine)){
			if(payload.priority < currTaskV.taskid)
			{
				//there is a higher priority robot trying to compute traj
				//send your current (empty) traj to unblock the higher priority task
				send payload.robot, eCurrentTraj, (robot =  this, currTraj = currentTrajV);
			}
			else
			{
				pendingRequestsV += (0, payload.robot);
			}
		}
	}

	model fun PlanGenerator(s: int, g: int, avoids: seq[seq[int]], robotid: int) : seq[int] {
		var ret : seq[int];
		ret += (0, 1);
		return ret;
	}

	fun ConvertTimedTrajToTraj(timedTraj: TimedTrajType, s: int) : seq[int]
	{
		var retTraj: seq[int];
		var index : int;
		index = 0;
		while(index < sizeof(timedTraj))
		{
			if(timedTraj[index].0 >= s)
			{
				retTraj += (sizeof(retTraj), timedTraj[index].1);
			}
		    index = index + 1;
		}
		if(sizeof(retTraj) == 0)
		{
			retTraj += (0, timedTraj[sizeof(timedTraj)-1].1);
		}

		return retTraj;
	}
	fun ComputeTimedTraj (goal: int, avoid: map[machine, TimedTrajType])
	{
		var currTimePeriod : int;
		var startingTimePeriod : int;
		var maxComputeTimeForPlanner : int;
		var convertedAvoids: seq[seq[int]];
		var index : int;
		var traj: seq[int];

		maxComputeTimeForPlanner = 5;
		currTimePeriod = GetCurrentTimePeriod(localTimeV, myIdV, this);
		startingTimePeriod = currTimePeriod + maxComputeTimeForPlanner;

		index = 0;
		while(index < sizeof(allRobotsMPV))
		{
			traj = ConvertTimedTrajToTraj(avoid[allRobotsMPV[index]], startingTimePeriod);
			convertedAvoids += (0, traj);
			assert sizeof(traj) > 0;
		    index = index + 1;
		}

		assert sizeof(convertedAvoids) == numOfRobots - 1;
		traj = PlanGenerator(currentLocationV, goal, convertedAvoids, myIdV);
		currentTrajV = default(TimedTrajType);
		index = 0;
		assert sizeof(traj) > 0;
		while(index < sizeof(traj))
		{
			currentTrajV += (index, (startingTimePeriod + index, traj[index]));
		    index = index + 1;
		}
	}
	state ComputeTrajState {
		entry {
			//compute the current trajectory
			ComputeTimedTraj(currTaskV.g, allAvoidsV);
			send planExecutorV, eStartExecutingPlan, currentTrajV;
			BROADCAST(pendingRequestsV, eCurrentTraj, (robot =  this, currTraj = currentTrajV), this);
			pendingRequestsV = default(seq[machine]);
			goto WaitForPlanCompletionOrCancellation;
		}
	}

	state WaitForPlanCompletionOrCancellation{
		defer eNewTask;
		on ePlanCompletion do (payload: int){ 
			currentLocationV = payload; 
			print "--- Robot {0} completed task and is at location {1} ---\n", myIdV, currentLocationV;
			goto WaitForRequests; 
		}
		on eRequestCurrentTraj do (payload: (priority: int, robot: machine)) {
			send payload.robot, eCurrentTraj, (robot = this, currTraj = currentTrajV);
		}
	}
}

/****************************************************/
/* Common functions */
/****************************************************/

fun BROADCAST(allTarget: seq[machine], ev: event, payload: any, source: machine)
{
	var index: int;
	index = 0;
	while(index < sizeof(allTarget))
	{
		if(source != allTarget[index])
		{
			send allTarget[index], ev, payload;
		}
		index = index + 1;
	}
}
