//Type declarations
type GPSHealthType = 
(
	locked: bool,
	satellites: int,
	fix_type: int,
	precision: int
);

type HeartbeatStatusType =
(
	isAlive: bool,
	lastHeartbeat: int
);

/*******************************************************/
/*	Topic for data coming from the PX4 				   */
/*******************************************************/
//make sure that the ints here match with the enums in POrbTopics.h
enum Topics {
	//from px4
	/*heartbeat_topic,
	attitude_topic,
	global_position_topic,
	local_position_topic,
	battery_status_topic,
	gps_raw_int_topic,
	gps_status_topic,
	command_ack_topic,
	extended_sys_state_topic,
	*/
	//from monitors
	px4status_topic,
	altitude_reached_topic,
	geofence_reached_topic,
	heartbeat_status_topic,
	battery_critical_topic,
	gps_health_topic,

	// vehicle topics
	vehicle_ready_topic,
	vehicle_armed_topic,
	vehicle_disarmed_topic,
	vehicle_landed_topic,
	vehicle_loitering_topic,
	vehicle_crashed_topic
}

/*******************************************************/
/*		Events corresponding to the vehicle topics			   */
/*******************************************************/
/*
event global_position assume 100 : mavlink_global_position_int_t;
event local_position assume 100 : mavlink_local_position_ned_t;
event battery_status assume 100 : mavlink_battery_status_t;
event attitude assume 100 : mavlink_attitude_t;
event gps_status assume 100 : mavlink_gps_status_t;
event heartbeat assume 100 : mavlink_heartbeat_t;
event command_ack assume 100 : mavlink_command_ack_t;
event gps_raw_int assume 100 : mavlink_gps_raw_int_t;
event extended_sys_state assume 100 : mavlink_extended_sys_state_t;
*/
//event for distributed time period
event distributed_time_period assume 10: int;
//local position
event local_position_update assume 10: int;
/*********************************************************
	Events corresponding to monitors
*********************************************************/
event altitude_reached assume 100 : bool;
event geofence_reached assume 100 : bool;
event heartbeat_status_changed assume 100: HeartbeatStatusType;
event battery_critical assume 100 : int;
event battery_recharged assume 100 : int;
event gps_health_update assume 100: GPSHealthType;


/*********************************************************
	Events corresponding to vehicles
*********************************************************/
event vehicle_ready assume 100 : bool;
event vehicle_armed assume 100 : bool;
event vehicle_disarmed assume 100 : bool;
event vehicle_landed assume 100 : bool;
event vehicle_loitering assume 100 : bool;
event vehicle_crashed  assume 100 : bool;

model fun GetSystemTime() : int
{
	return 0;
}
