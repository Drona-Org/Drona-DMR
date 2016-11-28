model fun SendSetHomeCommand(commander: machine, pos: GlobalPositionType, caller : machine)
{
	send commander, Command, (caller = caller, confirm = false, cmd = mav_cmd_do_set_home,  a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = pos.lat, a6 = pos.lon, a7 = pos.alt);
}

fun ReturnToLaunch(commander: machine, caller : machine)
{
	send commander, Command, (caller=caller, confirm=false, cmd=mav_cmd_nav_return_to_launch,  a1=0, a2=0, a3=0, a4=0, a5=0, a6=0, a7=0);
}

fun ArmVehicle(commander: machine, caller : machine)
{
	send commander, Command, (caller=caller, confirm=true, cmd=mav_cmd_component_arm_disarm, a1=1, a2=0, a3=0, a4=0, a5=0, a6=0, a7=0);
}

fun DisArmVehicle(commander:machine, caller: machine)
{	
	send commander, Command, (caller=caller, confirm=true, cmd=mav_cmd_component_arm_disarm,  a1=0,  a2=0, a3=0, a4=0, a5=0, a6=0, a7=0);
}

fun TakeOff(commander: machine, local: mavlink_local_position_ned_t, caller: machine) 
{
	send commander, Command, (caller=caller, confirm=false, cmd=mav_cmd_nav_takeoff, a1=0, a2=0, a3=0, a4=0, a5=0, a6=0, a7=local._z);
	assert(false);
}

fun GoToLocation(commander: machine, local: mavlink_local_position_ned_t, caller: machine)
{

	send commander, Command, (caller=caller, confirm=true, cmd=mav_cmd_do_reposition, a1=-1, a2=mav_do_reposition_flags_change_mode, 
		a3=0, a4=0, a5=local._x, a6=local._y, a7=local._z);
}

fun LandVehicle(commander: machine, caller: machine)
{
	// land at whatever our current GPS location is
	send commander, Command, (caller=caller, confirm=true, cmd=mav_cmd_nav_land, a1=0, a2=0, a3=0, a4=0, a5=0, a6=0, a7=0);
}

fun SetMessageInterval(commander: machine, msg_stream: mavlink_messages, interval: int, caller: machine)
{
	//send commander, Command, (caller=caller, confirm=false , cmd=mav_cmd_set_message_interval, a1=msg_stream,  a2=interval, a3=0, a4=0, a5=0, a6=0, a7=0);
}

