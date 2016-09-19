event eGetTimePeriod: int;
event eCurrTimePeriod : int;

fun MotionPrimitiveTimePeriod() : int { return 500; /*0.5 ms*/ }

model fun GetCurrentTimePeriod(timeSync:machine, robot: int) : int {
	var retVal: int;
	send timeSync, eGetTimePeriod, robot;

	receive {
		case eCurrTimePeriod: (payload: int) { retVal = payload; }
	}
	return retVal;
}

machine DistributedTimeSyncMachine {
	var robotsLocalTimeV : map[int, int];
	var timerV : machine;
	var allRobotsV: seq[machine];

	var noOfRobots: int;
	start state Init {
		entry(payload:seq[machine]) {
			var index: int;
			allRobotsV = payload;
			noOfRobots = GetNumOfRobots();
			index = 0;
			while(index < noOfRobots)
			{
				robotsLocalTimeV += (index, 0);
			    index = index + 1;
			}
			//create timer
			timerV = new Timer(this);
			
			//start timer
			StartTimer(timerV, MotionPrimitiveTimePeriod());
			goto WaitForGetTimeRequest;
		}
	}

	state WaitForGetTimeRequest {
		on TIMEOUT do {
			var index: int;
			index = 0;
			while(index < noOfRobots)
			{
				robotsLocalTimeV[index] = robotsLocalTimeV[index] + 1;
			    index = index + 1;
			}
			//start timer
			StartTimer(timerV, MotionPrimitiveTimePeriod());
		}
		on eGetTimePeriod do (payload : int) {
			send allRobotsV[payload], eCurrTimePeriod, robotsLocalTimeV[payload];
		}

	}
}