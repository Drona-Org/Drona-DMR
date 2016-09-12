event px4command: CommandType;

event d_px4_local;
event d_px4_publishstate;
event d_px4_updatestate;
event d_px4_servicecommand;

type PX4StateType = (
	curr_pos: LocalPositionType,
	battery_remaining : int,
	gps_locked : bool,
	vehicle_landed : int,
	home_pos : LocalPositionType
	); 

model DriverPX4Machine {
	var gps_statusV: mavlink_gps_status_t;
	var global_positionV: mavlink_global_position_int_t;
	var local_positionV: mavlink_local_position_ned_t;
	var battery_statusV: mavlink_battery_status_t;
	var gps_raw_intV : mavlink_gps_raw_int_t;
	var ex_sys_stateV : mavlink_extended_sys_state_t;

	var porbV : machine;
	var px4StateV : PX4StateType;

	var nextpositionV: LocalPositionType;

	fun InitialPX4State(){

		//initialize the pxstate
		px4StateV.curr_pos = (x = 1, y = 1, z = 0);
		px4StateV.battery_remaining = 70;
		px4StateV.gps_locked = true;
		px4StateV.vehicle_landed = 1;
		px4StateV.home_pos = (x = 1, y = 1, z = 0);

		//initialize the streams
		//gps status
		gps_statusV._satellites_visible = 8;

		//global position
		global_positionV._lat = 45;
		global_positionV._lon = 58;
		global_positionV._relative_alt = 0;

		//local position
		local_positionV._x = IntToFloat32(px4StateV.curr_pos.x);
		local_positionV._y = IntToFloat32(px4StateV.curr_pos.y);
		local_positionV._z = IntToFloat32(px4StateV.curr_pos.z);

		//batter status
		battery_statusV._battery_remaining = px4StateV.battery_remaining;

		//gps_raw
		gps_raw_intV._satellites_visible = 8;
		gps_raw_intV._fix_type = 2;
		gps_raw_intV._eph = 70;

		ex_sys_stateV._landed_state = 1;

	}
	start state Init {
		entry(payload: machine) {
			porbV = payload;
			InitialPX4State();
			raise d_px4_local;
		}
		on d_px4_local goto ChooseServiceCommandOrPublishStateOrUpdateState;
	}
		
	state ChooseServiceCommandOrPublishStateOrUpdateState{
		entry {
			if($)
			{
				raise d_px4_servicecommand;
			}
			else if($)
			{
				raise d_px4_publishstate;
			}
			else
			{
				raise d_px4_updatestate;
			}
		}
		on d_px4_servicecommand goto ServiceCommand;
		on d_px4_publishstate goto PublishState;
		on d_px4_updatestate goto UpdateState;
	}

	fun HandleCommand(command: CommandType) {
		//just respond back with command succeeded for now
		if(command.confirm)
			send command.caller, CommandSucceeded, command.cmd;

		//now handle the various commands being sent to PX4

		//mav_cmd_nav_return_to_launch
		if(command.cmd == mav_cmd_nav_return_to_launch)
		{
			nextpositionV = px4StateV.home_pos;
		}
		else
		//mav_cmd_set_message_interval
		if(command.cmd == mav_cmd_set_message_interval)
		{
			//ignore this message
		}
		else
		//mav_cmd_component_arm_disarm
		if(command.cmd == mav_cmd_component_arm_disarm)
		{
			//ignore this message
		}
		else
		//mav_cmd_nav_takeoff
		if(command.cmd == mav_cmd_nav_takeoff)
		{
			nextpositionV = (x = px4StateV.home_pos.x, y = px4StateV.home_pos.y, z = px4StateV.home_pos.z + (command.a7 as int));
			px4StateV.vehicle_landed = 2;
		}
		else
		//mav_cmd_nav_land
		if(command.cmd == mav_cmd_nav_land)
		{
			nextpositionV = (x = px4StateV.curr_pos.x, y = px4StateV.curr_pos.y, z = 0);
			px4StateV.vehicle_landed = 1;
		}
		else if (command.cmd == mav_cmd_do_set_home){
			px4StateV.home_pos = px4StateV.curr_pos;
		}
		else if (command.cmd == mav_cmd_do_reposition)
		{
			nextpositionV = (x = command.a5 as int, y = command.a6 as int , z = command.a7 as int);	
		}
		else
			assert(false);
	}

	state PublishState {
		defer px4command;

		entry {
			//nondeterministically choose to publish one of the stream.
			var publishMess : POrbPubMsgType;
			if($)
			{
				//update the global position message
				//TODO: not done right now
				publishMess.topic = global_position_topic;
				publishMess.ev = global_position;
				publishMess.payload = global_positionV;
			}
			else if($)
			{
				//local position
				local_positionV._x = IntToFloat32(px4StateV.curr_pos.x);
				local_positionV._y = IntToFloat32(px4StateV.curr_pos.y);
				local_positionV._z = IntToFloat32(px4StateV.curr_pos.z);
				//publish local position
				publishMess.topic = local_position_topic;
				publishMess.ev = local_position;
				publishMess.payload = local_positionV;
			}
			else if($)
			{
				battery_statusV._battery_remaining = px4StateV.battery_remaining;
				publishMess.topic = battery_status_topic;
				publishMess.ev = battery_status;
				publishMess.payload = battery_statusV;
			}
			else if($)
			{
				//gps_raw
				if(!px4StateV.gps_locked)
				{
					gps_raw_intV._satellites_visible = 2;
					gps_raw_intV._fix_type = 2;
					gps_raw_intV._eph = 10;
				}
				else
				{
					gps_raw_intV._satellites_visible = 8;
					gps_raw_intV._fix_type = 2;
					gps_raw_intV._eph = 70;
				}
				publishMess.topic = gps_raw_int_topic;
				publishMess.ev = gps_raw_int;
				publishMess.payload = gps_raw_intV;
			}
			else if($)
			{
				//gps_status
				if(!px4StateV.gps_locked)
				{
					gps_statusV._satellites_visible = 3;
				}
				else
				{
					gps_statusV._satellites_visible = 8;
				}
				publishMess.topic = gps_status_topic;
				publishMess.ev = gps_status;
				publishMess.payload = gps_statusV;
			}
			else
			{
				//ex sys state
				ex_sys_stateV._landed_state = px4StateV.vehicle_landed;
				publishMess.topic = extended_sys_state_topic;
				publishMess.ev = extended_sys_state;
				publishMess.payload = ex_sys_stateV;
			}
			Publish(porbV, publishMess);
			raise d_px4_local;
		}
		on d_px4_local goto ChooseServiceCommandOrPublishStateOrUpdateState;
	}
	state ServiceCommand {
		//if there are no commands to be serviced
		on null, d_px4_local goto ChooseServiceCommandOrPublishStateOrUpdateState;

		on px4command do (cmd: CommandType) { HandleCommand(cmd); raise d_px4_local; }
	}

	state UpdateState {
		defer px4command;
		entry {

			//nondet choose to decrease the battery by 10
			if(px4StateV.battery_remaining > 20)
			{
				if($)
				{
					px4StateV.battery_remaining = px4StateV.battery_remaining - 50;
				}
			}

			//nondet update the position of the drone to the next expected position
			if(px4StateV.curr_pos != nextpositionV)
			{
				if($)
					px4StateV.curr_pos = nextpositionV;
			}

			//nondet change the gps status
			if($)
			{
				px4StateV.gps_locked = !px4StateV.gps_locked;
			}

			send this, d_px4_local;
		}
		on d_px4_local goto ChooseServiceCommandOrPublishStateOrUpdateState;
	}
}