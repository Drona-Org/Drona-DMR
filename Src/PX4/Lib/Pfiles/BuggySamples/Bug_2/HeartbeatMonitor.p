event heartbeat_monitor_local;

machine HeartbeatMonitorMachine {
	var orb: machine;
	var commander : machine;
	var heartbeatTimerV : machine;
	var status : HeartbeatStatusType;

	start state Init {
		entry (payload: HelperMachinesType) {
		    
			commander = payload.commander;
			orb = payload.orb;		

			heartbeatTimerV = new TimerMachine(this);
			
			// configure these event streams (interval of 100000 microseconds is 100 milliseconds or 10 messages per second should be good)
			SetMessageInterval(commander, msg_heartbeat, 1000, this);

			//subscribe to the heartbeat message
			Subscribe(orb, (topic = heartbeat_topic, sub = this));
			//start timer for monitoring heartbeat message
			send heartbeatTimerV, timer_start, 10000;

			raise heartbeat_monitor_local;
		}
		on heartbeat_monitor_local goto MonitorHeartbeat;
	}

	state MonitorHeartbeat {
		on heartbeat do (payload: mavlink_heartbeat_t) {

			var timerCanceled: bool;
		    print ".";
			
			status.lastHeartbeat = GetSystemTime();

			//reset the timer			
			timerCanceled = CancelTimer(heartbeatTimerV);
			if(timerCanceled) {
				send heartbeatTimerV, timer_start, 10000;
			}
			status.isAlive = true;
			Publish(orb, (topic= heartbeat_status_topic, ev = heartbeat_status_changed, payload = status));
		}

		on timer_timeout do (timer: machine) {
			//timeout received something is wrong !!
			print "HeartbeatMonitorMachine: No Heartbeat for a long time !!\n";
			status.isAlive = false;
			Publish(orb, (topic= heartbeat_status_topic, ev = heartbeat_status_changed, payload = status));
		}
	}

	fun CancelTimer(timer: machine): bool {
		var timerCanceled: bool;
		send timer, timer_cancel;
		receive {
			case timer_cancel_success: (payload: machine) 
			{ 
				assert(timer == payload);
				timerCanceled = true; 
			}
			case timer_cancel_failure: (payload: machine) 
			{ 
				assert(timer == payload);
				timerCanceled = false; 
			}
		}
		return timerCanceled;
	 }

}