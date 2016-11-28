machine MissionPlannerMachine
{
    //First this is to start the POrb so that everyone can communicate with each other.
	var orb: machine;
    var controller : machine;
	var landing: bool;
	var commander : machine;
	var landed: bool;
	var path: seq[LocalPositionType];
	var pathPos: int;
	var target: LocalPositionType;
	var timer: machine;
	var tracking: bool;

    // States: 
    start state Init
    {
        entry
        {
			orb = new POrbMachine();
			commander = new CommanderMachine(orb);
			timer = CreateTimer(this);
			
            Subscribe(orb, (topic = vehicle_landed_topic, sub = this));
            Subscribe(orb, (topic = vehicle_armed_topic, sub = this));
            Subscribe(orb, (topic = vehicle_disarmed_topic, sub = this));
            Subscribe(orb, (topic = vehicle_ready_topic, sub = this));
            Subscribe(orb, (topic = vehicle_loitering_topic, sub = this));
            Subscribe(orb, (topic = local_position_topic, sub = this));

			path = default(seq[LocalPositionType]);
			path += (0, (x=IntToFloat32(10), y=IntToFloat32(0), z=IntToFloat32(5)));
			path += (1, (x=IntToFloat32(10), y=IntToFloat32(10), z=IntToFloat32(5)));
			path += (2, (x=IntToFloat32(0), y=IntToFloat32(10), z=IntToFloat32(5)));
			path += (3, (x=IntToFloat32(0), y=IntToFloat32(0), z=IntToFloat32(5)));
			pathPos = 0;
			
            controller = new FlightControllerMachine((orb = orb, commander = commander));
        }
		on vehicle_ready goto StartMission;
		ignore local_position;
    }

    state StartMission 
	{
    	entry (payload: any)
		{
    		//send command to arm the drone
			print "MissionPlannerMachine: arming the drone\n";
    		send controller, mission_arm;
    	}
		on vehicle_armed do (payload: any){
			print "MissionPlannerMachine: sending take off to 5 meters\n";
			landed = false;
			send controller, mission_takeoff, IntToFloat32(5);
		}

		on vehicle_loitering push FollowPath;
		
		on vehicle_landed do (payload: any){
			if (landing && !landed) {
				landed = true;
				print "MissionPlannerMachine: landed, disarming drone\n";			
    			send controller, mission_disarm;
			}
		}
		on vehicle_crashed do {	
			landed = true;
			print "MissionPlannerMachine: crashed, disarming drone\n";			
    		send controller, mission_disarm;
		}

		on vehicle_disarmed goto MissionComplete;

		ignore local_position;
    }

	state MissionComplete
	{
		entry {
			print "MissionPlannerMachine: mission complete !!\n";	
		}

		ignore local_position;
	}

	state FollowPath 
	{
		entry 
		{
			print "MissionPlannerMachine: starting path\n";	
			NextPathSegment();
		}
		
		on local_position do (pos: mavlink_local_position_ned_t)
		{
			var x : float32;
			var y : float32;
			var z : float32;
			var xnear: bool;
			var ynear: bool;
			var delta: float32;

			if (!landing && tracking)
			{
				delta = IntToFloat32(2);
				x = pos._x;
				y = pos._y;
				z = pos._z;
			
				xnear = IsNearFloat32(x, target.x, delta);
				ynear = IsNearFloat32(y, target.y, delta);

				if (xnear && ynear) {
					NextPathSegment();
				}
			}
		}

		on timer_timeout do {
			var nan: float32;
			nan = NaNFloat32();
			CancelTimer(timer);
			tracking = true;
			send controller, mission_goto, (speed = IntToFloat32(2), x = target.x, y = target.y, z = target.z, yaw = nan);
		}

		ignore timer_cancel_success;
		ignore timer_cancel_failure;
	}

	fun NextPathSegment() {

		if (landed) 
		{
			// oops, did we crash?
			pop;
		}
		else if (pathPos == sizeof(path))
		{
			print "MissionPlannerMachine: mission complete, time to land\n";
			landing = true;
			send controller, mission_land;
			pop;
		}
		else
		{
			target = path[pathPos];
			pathPos = pathPos + 1;
			tracking = false;
			StartTimer(timer, 3000);
		}
	}

}

