event d_px4_command: CommandType;
event d_px4_local;
event d_px4_serviceCommand : CommandType;

model PX4CommandReceiverMachine {
	var porb : machine;
	var px4StateManager : machine;
	fun HandleCommand(command: CommandType) {
		//just respond back with command succeeded for now
		if(command.confirm)
		{
			if($)
			{
				send command.caller, CommandSucceeded, command.cmd;
				if(command.cmd == mav_cmd_set_message_interval)
				{
					//ignore this command and not forward it to the stateManager
				}
				else
				{
					send px4StateManager, d_px4_serviceCommand, command;
				}
				
			}
			else
			{
				send command.caller, CommandFailed, command.cmd;
			}
			
		}
	}
	start state Init {
		entry(payload: machine)
		{
			porb = payload;
			px4StateManager = new PX4UpdateStateAndPublishMachine(porb);
		}
		on d_px4_command do (cmd: CommandType) { HandleCommand(cmd); raise d_px4_local; }
	}
}


type Px4InternalStateType = (
	local_pos : LocalPositionType,
	global_pos : GlobalPositionType,
	home_pos: LocalPositionType,
	gps_locked: bool,
	battery_remaining: int,
	px4_alive : bool,
	isHomeSet : bool,
	hasGlobalPosition : bool,
	isReady : bool,
	isLocalSet: bool,
	flying: bool,
	armed: bool
	);

model PX4UpdateStateAndPublishMachine {
	var px4State : Px4InternalStateType;
	var porbV: machine;
	start state Init {
		entry (payload: machine)
		{
			//initialize the vehicle state stored by flight controller
			px4State.gps_locked = false;
			px4State.battery_remaining = 100;
			px4State.px4_alive = false;
			px4State.armed = false;
			px4State.flying = false;
			px4State.isLocalSet = false;
			px4State.isReady = false;
			px4State.isHomeSet = false;
			px4State.hasGlobalPosition = false;
			px4State.local_pos = (x = 0, y = 0, z =0);
			px4State.global_pos = (timestamp = 118, lat = 48, lon = 55, alt = 100);
			porbV = payload;
			goto WaitForCommandsAndPublish;
		}
	}

	state WaitForCommandsAndPublish {
		entry {
		}
		on null push PublishCurrentState;
		on d_px4_serviceCommand do (command: CommandType) { ServiceCommandAndUpdateState(command); }
	}

	fun ServiceCommandAndUpdateState (command: CommandType){

		if(command.cmd == mav_cmd_nav_return_to_launch)
		{
			px4State.local_pos = px4State.home_pos;
		}
		else if(command.cmd == mav_cmd_component_arm_disarm)
		{
			if(command.a1 == 1)
			{
				px4State.armed = true;
			}
			else
			{
				px4State.armed = false;
			}
		}
		else if(command.cmd == mav_cmd_nav_takeoff)
		{
			px4State.local_pos = (x = px4State.local_pos.x, y = px4State.home_pos.y, z = px4State.home_pos.z + (command.a7 as int));
			px4State.flying = true;
		}
		else if(command.cmd == mav_cmd_nav_land)
		{
			px4State.local_pos = (x = px4State.local_pos.x, y = px4State.home_pos.y, z = 0);
			px4State.flying = false;
		}
		else if (command.cmd == mav_cmd_do_set_home){
			px4State.home_pos = px4State.local_pos;
		}
		else if (command.cmd == mav_cmd_do_reposition)
		{
			px4State.local_pos = (x = command.a5 as int, y = command.a6 as int , z = command.a7 as int);	
		}
		else
		{
			assert false, "Not implemented this command in px4 model";
		}

	}

	state PublishCurrentState {
		entry {
			//nondeterministically choose to publish one of the stream.
			var publishMess : POrbPubMsgType;
			var gps_statusV: mavlink_gps_status_t;
			var global_positionV: mavlink_global_position_int_t;
			var local_positionV: mavlink_local_position_ned_t;
			var battery_statusV: mavlink_battery_status_t;
			var gps_raw_intV : mavlink_gps_raw_int_t;
			var ex_sys_stateV : mavlink_extended_sys_state_t;
			
			
			//if($)
			{
				//update the global position message
				//TODO: not done right now
				global_positionV._lat = px4State.global_pos.lat;
				global_positionV._lon = px4State.global_pos.lon;
				global_positionV._alt = px4State.global_pos.alt;
				publishMess.topic = global_position_topic;
				publishMess.ev = global_position;
				publishMess.payload = global_positionV;

				Publish(porbV, publishMess);
			}

			
			//if($)
			{
				//local position
				local_positionV._x = px4State.local_pos.x;
				local_positionV._y = px4State.local_pos.y;
				local_positionV._z = px4State.local_pos.z;
				//publish local position
				publishMess.topic = local_position_topic;
				publishMess.ev = local_position;
				publishMess.payload = local_positionV;

				Publish(porbV, publishMess);
			}

			//if($)
			{
				//Update the batter status
				if(px4State.battery_remaining > 20)
				{
					if($)
					{
						px4State.battery_remaining = px4State.battery_remaining - 50;
					}
				}
				else
				{
					//TODO: Add the recharging case.
				}
				battery_statusV._battery_remaining = px4State.battery_remaining;
				publishMess.topic = battery_status_topic;
				publishMess.ev = battery_status;
				publishMess.payload = battery_statusV;
				Publish(porbV, publishMess);
			}
			
			//if($)
			{
				//Non-det update the gps status
				if($)
				{
					px4State.gps_locked = !px4State.gps_locked;
				}

				if(!px4State.gps_locked)
				{
					gps_raw_intV._satellites_visible = 2;
					gps_raw_intV._fix_type = 2;
					gps_raw_intV._eph = 70;
				}
				else
				{
					gps_raw_intV._satellites_visible = 8;
					gps_raw_intV._fix_type = 2;
					gps_raw_intV._eph = 10;
				}
				publishMess.topic = gps_raw_int_topic;
				publishMess.ev = gps_raw_int;
				publishMess.payload = gps_raw_intV;
				Publish(porbV, publishMess);
			}
			
			//if($)
			{
				//gps_status
				if(!px4State.gps_locked)
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
				Publish(porbV, publishMess);
			}

			//if($)
			{
				//ex sys state
				if(px4State.flying)
				{
					ex_sys_stateV._landed_state = mav_landed_state_in_air;
				}
				else
				{
					ex_sys_stateV._landed_state = mav_landed_state_on_ground;
				}
				publishMess.topic = extended_sys_state_topic;
				publishMess.ev = extended_sys_state;
				publishMess.payload = ex_sys_stateV;
				Publish(porbV, publishMess);
			}

			pop;
		}
	}
	
}