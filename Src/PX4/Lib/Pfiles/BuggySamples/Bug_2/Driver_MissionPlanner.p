machine MissionPlannerMachine
{
    //First this is to start the POrb so that everyone can communicate with each other.
    var orb: machine;
    var controller : machine;
    var px4 : machine;
    var timer : machine;
    var landing: bool;
    var commander : machine;
    // States: 
    start state Init
    {
        entry
        {
            orb = new POrbMachine();
            px4 = new DriverPX4Machine(orb);
            commander = new CommanderMachine(px4);
            timer = new TimerMachine(this);
           
            Subscribe(orb, (topic = vehicle_landed_topic, sub = this));
            Subscribe(orb, (topic = vehicle_armed_topic, sub = this));
            Subscribe(orb, (topic = vehicle_ready_topic, sub = this));
            Subscribe(orb, (topic = vehicle_loitering_topic, sub = this));
            
            controller = new FlightControllerMachine((orb = orb, commander = commander));
        }
        on vehicle_ready goto StartMission;
    }

    state StartMission {
        entry (payload: any){
            //send command to arm the drone
            print "MissionPlannerMachine: arming the drone\n";
            send controller, mission_arm;
        }
        on vehicle_armed do (payload: any){
            print "MissionPlannerMachine: sending take off to 5 meters\n";
            send controller, mission_takeoff, IntToFloat32(5);
        }
        on vehicle_loitering do (payload: any){
            if (!landing) {
                print "MissionPlannerMachine: loitering for 10 seconds\n";
                
                send controller, mission_goto, (speed = IntToFloat32(2), x = IntToFloat32(10),
                    y = IntToFloat32(10), z = IntToFloat32(20), yaw = IntToFloat32(0));
                
                //send timer, timer_start, 10000;
            }
        }
        on vehicle_landed do (payload: any){
            if (landing) {
                send timer, timer_cancel;
                print "MissionPlannerMachine: landed, disarming drone\n";           
                send controller, mission_disarm;
            }
        }

        on timer_timeout do (timer: machine) {
            send timer, timer_cancel;
            print "MissionPlannerMachine: mission complete, time to land\n";
            landing = true;
            send controller, mission_land;
        }

        ignore timer_cancel_success;
        ignore timer_cancel_failure;
    }

}

