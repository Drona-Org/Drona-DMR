event eGetTimePeriod: machine;
event eCurrTimePeriod : int;

fun MotionPrimitiveTimePeriod() : int { return 500; /*0.5 ms*/ }

model fun GetCurrentTimePeriod(timeSync:machine, robotid: int) : int {
	var retVal: int;
	send timeSync, eGetTimePeriod, robotid;

	receive {
		case eCurrTimePeriod: (payload: int) { retVal = payload; }
	}
	return retVal;
}

machine DistributedTimeSyncMachine {
	var robotsLocalTimeV : map[machine, int];
	var timerV : machine;
	var allRobotsV: seq[machine];
	start state Init {
		entry(payload:seq[machine]) {
			var index: int;
			index = 0;
			while(index < sizeof(payload))
			{
				robotsLocalTimeV += (payload[index], 0);
			    index = index + 1;
			}
			allRobotsV = keys(robotsLocalTimeV);
			//create timer
			timerV = new Timer(this);
			
			//start timer
			StartTimer(this, MotionPrimitiveTimePeriod());
			goto WaitForGetTimeRequest;
		}
	}

	state WaitForGetTimeRequest {
		on TIMEOUT do {
			var index: int;
			index = 0;
			while(index < sizeof(allRobotsV))
			{
				robotsLocalTimeV[allRobotsV[index]] = robotsLocalTimeV[allRobotsV[index]] + 1;
			    index = index + 1;
			}
		}
		on eGetTimePeriod do (payload : machine) {
			send payload, eCurrTimePeriod, robotsLocalTimeV[payload];
		}

	}
}