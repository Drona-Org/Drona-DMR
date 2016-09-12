event heartbeat_monitor_local;
event heartbeat_monitor_failed;

machine HeartbeatMonitorMachine {
	var heartbeatStatus : HeartbeatStatusType;
	var POrbV : machine;
	start state Init {
		entry (payload: HelperMachinesType) {
			POrbV = payload.orb;
			raise heartbeat_monitor_local;
		}

		on heartbeat_monitor_local goto MonitorHeartbeat;
	}

	state MonitorHeartbeat {
		entry
		{
			/*
			if($)
			{
				heartbeatStatus.isAlive = true;
				Publish(POrbV, (topic= heartbeathealth_topic, ev = heartbeatmonitoring, payload = heartbeatStatus));
			}
			else
			{
				
				heartbeatStatus.isAlive = false;
				Publish(POrbV, (topic= heartbeathealth_topic, ev = heartbeatmonitoring, payload = heartbeatStatus));
				
			}
			send this, heartbeat_monitor_local;
			*/
			//our driver is going to send heartbeat only 3 times
			var index : int;
			index = 0;
			while(index < 3)
			{
				heartbeatStatus.isAlive = true;
				Publish(POrbV, (topic= heartbeat_status_topic, ev = heartbeat_status_changed, payload = heartbeatStatus));
			    index = index + 1;
			}

			raise halt;
		}

		on heartbeat_monitor_local goto MonitorHeartbeat;
	}


}