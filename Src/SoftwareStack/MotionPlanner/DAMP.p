type TimedTrajType = seq[(int, int)];
type TaskType = (taskid: int, s: int, g: int);

event eRequestCurrentTraj : (priority : int, mach : machine);
event eCurrentTraj : (mach: machine, currTraj : TimedTrajType);
event eNewTask : TaskType;
event eUnit;
event eComputeTraj;
event eConfiguration: seq[machine];

machine DistributedMotionPlannerMachine
{
	var allRobotsV : seq[machine];
	var allAvoidsV : map[machine, TimedTrajType];
	var currentTrajV : TimedTrajType;
	var myId : int;
	var currTask : TaskType;
	var receivedTrajFrom : map[machine, bool];
	start state Init {

		entry (id: int) {
			myId = id;
		}

		on eConfiguration goto WaitForRequests with (payload: seq[machine]){
			var index: int;
			index = 0;
			while(index < sizeof(payload))
			{
				if(payload[index] != this)
					allRobotsV += (0, payload[index]);
			    index = index + 1;
			}
		}
	}

	state WaitForRequests {
		entry {
			//reset the currentTraj variable to current location
			currentTrajV += (0, (-1, currLocation));
		}
		//on receiving a new task update the local task variable and goto GetCurrentStateOfAllRobots
		on eNewTask goto GetCurrentStateOfAllRobots with (payload: TaskType) {
			currTask = payload; 
			index = 0;
			while(index < sizeof(allRobotsV))
			{
				receivedTrajFrom[allRobotsV[index]] = false; // reset the map
				index = index + 1;
			}
			monitor mTaskReq, myId;
		};
		//on receiving request for latest trajectory send the enpty list, informing that I am not performing any task
		on eRequestCurrentTraj do (target: (priority : int, mach : machine)) {
			send target.mach, eCurrentTraj, (mach = this, currTraj = currentTrajV);
		};
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
			BROADCAST(allRobotsV, eRequestCurrentTraj, (priority = currTask.taskid, mach = this));
			if(allTrajsReceived(receivedTrajFrom))
			{
				raise eComputeTraj;
			}
		}
		on eCurrentTraj do (payload: (mach: machine, currTraj : TimedTrajType)){
			allAvoidsV[payload.mach] = payload.currTraj;
			receivedTrajFrom[payload.mach] = true;
			if(allTrajsReceived(receivedTrajFrom))
			{
				raise eComputeTraj;
			}
		};
		on eRequestCurrentTraj do (payload: (priority: int, mach: machine)){
			if(payload.priority < currTask.taskid)
			{
				//there is a higher priority robot trying to compute traj
				//send your current (empty) traj to unblock the higher priority task
				send payload.mach, eCurrentTraj, (mach =  this, currTraj = currentTrajV);
			}
			else
			{
				pendingRequests += (0, payload.mach);
			}
		};
		on eComputeTraj goto ComputeTrajState;
	}

	state ComputeTrajState {
		entry {
			BROADCAST(pendingRequests, eCurrentTraj, (mach =  this, currTraj = currentTrajV));
			pendingRequests = default(seq[machine]);
			raise eUnit;
		}
		on eUnit goto WaitForTaskCompletionOrCancellation;
	}

	state WaitForTaskCompletionOrCancellation{
		defer eNewTask;
		entry {
			//just a hack
			send this, TaskComplete;
			monitor mTaskComplete, myId;
		}
		on eRequestCurrentTraj do (payload: (priority: int, mach: machine)) {
			print "problem !!";
			send payload.mach, eCurrentTraj, (mach = this, currTraj = currentTrajV);
		};
	}
}

event mTaskReq: int;
event mTaskComplete: int;

spec EventualService monitors mTaskReq, mTaskComplete {
	var robotidV : int;
	start state Init {
		ignore mTaskComplete;
		on mTaskReq goto WaitForTaskCompletion with (priority: int){
			robotidV = priority;
		};
	}

	hot state WaitForTaskCompletion {
		ignore mTaskReq;
		on mTaskComplete do (priority :int) {
			if(robotidV == priority)
			{
				raise eUnit;
			}
		};
		on eUnit goto Init;
	}

}

/****************************************************/
/* Common functions */
/****************************************************/
static fun ChooseInt(s : int) : int {
	while(s > 0)
	{
		if($)
			return s;
		else
			s = s - 1;
	}
	return s;
}

static fun BROADCAST(allTarget: seq[machine], ev: event, payload: any)
{
	var index: int;
	index = 0;
	while(index < sizeof(allTarget))
	{
		send allTarget[index], ev, payload;
		index = index + 1;
	}
}
