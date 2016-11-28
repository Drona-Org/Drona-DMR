#include "Commands.h"

#define MAVLINK_PACKED
// for UDP we need to buffer these packets and send them as one UDP datagram.
void my_mavlink_start_send(int channel, int length);
void my_mavlink_end_send(int channel, int length);
#define MAVLINK_START_UART_SEND(chan, length) my_mavlink_start_send(chan, length)
#define MAVLINK_END_UART_SEND(chan, length) my_mavlink_end_send(chan, length);

#include "mavlink.h"
#include "mavlink_helpers.h"
#include "geo.h"

extern char mydatagram[255];
extern int mydatagrampos;

extern float homeLat;
extern float homeLon;
extern float homeAlt;
extern float currentLat;
extern float currentLon;
extern float currentAlt;
extern float currentHeading;

MAVLINK_HELPER void _mavlink_send_uart(mavlink_channel_t chan, const char *buf, uint16_t len)
{
	if (len + mydatagrampos > 255)
	{
		printf("### Message is too big\n");
		exit(1);
	}
	::memcpy(mydatagram + mydatagrampos, buf, len);
	mydatagrampos += len;
}

Command::Command()
{
}


Command::~Command()
{
}

void Command::HandleMessage(void* payload) 
{
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_COMMAND_ACK)
	{
		mavlink_command_ack_t ack;
		mavlink_msg_command_ack_decode(msg, &ack);
		MAV_RESULT result = (MAV_RESULT)ack.result;

		static const char* resultStrings[] = {
			"MAV_RESULT_ACCEPTED - Command ACCEPTED and EXECUTED",
			"MAV_RESULT_TEMPORARILY_REJECTED -  Command TEMPORARY REJECTED/DENIED",
			"MAV_RESULT_DENIED - Command PERMANENTLY DENIED",
			"MAV_RESULT_UNSUPPORTED - Command UNKNOWN/UNSUPPORTED",
			"MAV_RESULT_FAILED - Command executed, but failed"
		};
		if (result < MAV_RESULT_ENUM_END)
		{
			printf("Command ACK for command %d, result is: %s\n", (int)ack.command, resultStrings[(int)result]);
		}
	}
}

void ArmDisarmCommand::Execute() {
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_COMPONENT_ARM_DISARM, 1, arm, 0, 0, 0, 0, 0, 0);
}

void GetParamsCommand::Execute() {
	//MAVLINK_MSG_ID_PARAM_REQUEST_LIST
	mavlink_msg_param_request_list_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1);
}

void GetParamsCommand::HandleMessage(void* payload ) {
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_PARAM_VALUE)
	{
		mavlink_param_value_t value;
		mavlink_msg_param_value_decode(msg, &value);
		char name[17];
		::memset(name, 0, 17);
		strncpy_s(name, 17, value.param_id, 16);
		float fvalue;
		int ivalue;
		bool real = false;

		switch (value.param_type)
		{
		case MAV_PARAM_TYPE_UINT8:
			ivalue = *(uint8_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_INT8:
			ivalue = *(int8_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_UINT16:
			ivalue = *(uint16_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_INT16:
			ivalue = *(int16_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_UINT32:
			ivalue = *(uint32_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_INT32:
			ivalue = *(int32_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_UINT64:
			// we only have 4 bytes for the value in mavlink_param_value_t, so how does this one work?
			ivalue = *(uint32_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_INT64:
			// we only have 4 bytes for the value in mavlink_param_value_t, so how does this one work?
			ivalue = *(int32_t*)&value.param_value;
			break;
		case MAV_PARAM_TYPE_REAL32:
			real = true;
			fvalue = value.param_value;
			break;
		case MAV_PARAM_TYPE_REAL64:
			// we only have 4 bytes for the value in mavlink_param_value_t, so how does this one work?
			real = true;
			fvalue = value.param_value;
			break;
		default:
			break;
		}
		FILE* out = (ptr == NULL) ? stdout : ptr;
		if (real)
		{
			fprintf(out, "%s  : %.4f\n", name, fvalue);
		}
		else
		{
			fprintf(out, "%s  : %d\n", name, ivalue);
		}

		if (value.param_index == value.param_count - 1)
		{
			printf("PARAMS complete\n");
			Close();
		}
	}
}

void TakeOffCommand::Execute() {

	printf("take off to alt=%f\n", altitude);

	// request gps info
	targetAlt = homeAlt + altitude;
	reached = false;
	offground = false;

	/*
	<entry value="22" name="MAV_CMD_NAV_TAKEOFF">
		<description>Takeoff from ground / hand</description>
		<param index="1">Minimum pitch (if airspeed sensor present), desired pitch without sensor</param>
		<param index="2">Empty</param>
		<param index="3">Empty</param>
		<param index="4">Yaw angle (if magnetometer present), ignored without magnetometer</param>
		<param index="5">Latitude</param>
		<param index="6">Longitude</param>
		<param index="7">Altitude</param>
	</entry>
	*/
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_NAV_TAKEOFF, 1, 0, 0, 0, currentHeading, homeLat * 1e7f, homeLon * 1e7f, (float)targetAlt);
}

void TakeOffCommand::HandleMessage(void *payload) {
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_GPS_RAW_INT)
	{
		// The global position, as returned by the Global Positioning System (GPS).
		mavlink_gps_raw_int_t rawGps;
		mavlink_msg_gps_raw_int_decode(msg, &rawGps);
		float lat = (float)((float)rawGps.lat / 1e7);
		float lon = (float)((float)rawGps.lon / 1e7);
		float alt = (float)((float)rawGps.alt / 1000);
		if (!reached && alt >= targetAlt - delta && alt <= targetAlt + delta)
		{			
			reached = true;
			printf("Target altitude reached at lat=%f, long=%f, alt=%f\n", lat, lon, alt);
		}
	}
	else if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_EXTENDED_SYS_STATE)
	{
		// Provides state for additional features
		// The general system state
		mavlink_extended_sys_state_t status;
		mavlink_msg_extended_sys_state_decode(msg, &status);
		if (!offground && (int)status.landed_state == 0)
		{
			printf("Drone has left the ground\n");
			offground = true;
		}
	}
}


void LandCommand::Execute() {

	printf("landing drone...\n");
	landed = false;
	// request gps info
	// MAV_CMD_NAV_LAND=21, /* Land at location |Abort Alt| Empty| Empty| Desired yaw angle| Latitude| Longitude| Altitude|  */
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_NAV_LAND, 1, 0, 0, 0, currentHeading, (float)(homeLat * 1e7), (float)(homeLon * 1e7), homeAlt);
}

void LandCommand::HandleMessage(void *payload)
{
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_EXTENDED_SYS_STATE)
	{
		// Provides state for additional features
		// The general system state
		mavlink_extended_sys_state_t status;
		mavlink_msg_extended_sys_state_decode(msg, &status);
		if (!landed && (int)status.landed_state == 1)
		{
			printf("Drone has landed\n");
			landed = true;
		}
	}
}

void RtlCommand::Execute() {

	printf("Returning back to launch point...\n");

	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_NAV_RETURN_TO_LAUNCH, 0, 0, 0, 0, 0, 0, 0, 0);
}

void RtlCommand::HandleMessage(void *payload)
{
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_EXTENDED_SYS_STATE)
	{
		// Provides state for additional features
		// The general system state
		mavlink_extended_sys_state_t status;
		mavlink_msg_extended_sys_state_decode(msg, &status);
		if (!landed && (int)status.landed_state == 1)
		{
			printf("Drone has landed\n");
			landed = true;
		}
	}
}


void MissionCommand::Execute() {

	printf("Executing preprogrammed mission (if there is one)...\n");

	/*
	<entry value="176" name="MAV_CMD_DO_SET_MODE">
		<description>Set system mode.</description>
		<param index="1">Mode, as defined by ENUM MAV_MODE</param>
		<param index="2">Custom mode - this is system specific, please refer to the individual autopilot specifications for details.</param>
		<param index="3">Custom sub mode - this is system specific, please refer to the individual autopilot specifications for details.</param>
		<param index="4">Empty</param>
		<param index="5">Empty</param>
		<param index="6">Empty</param>
		<param index="7">Empty</param>
	</entry>
	*/
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_DO_SET_MODE, 1, MAV_MODE_FLAG_AUTO_ENABLED, 0, 0, 0, 0, 0, 0);
}

void MissionCommand::HandleMessage(void *payload)
{
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_EXTENDED_SYS_STATE)
	{
		// Provides state for additional features
		// The general system state
		mavlink_extended_sys_state_t status;
		mavlink_msg_extended_sys_state_decode(msg, &status);
		if (!landed && (int)status.landed_state == 1)
		{
			printf("Drone has landed\n");
			landed = true;
		}
	}
}

void CapabilitiesCommand::Execute() {

	// request capabilities, it will respond with AUTOPILOT_VERSION.
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES, 0, 0, 0, 0, 0, 0, 0, 0);

}

void CapabilitiesCommand::HandleMessage(void *payload)
{
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_AUTOPILOT_VERSION)
	{
		mavlink_autopilot_version_t ver;
		mavlink_msg_autopilot_version_decode(msg, &ver);
		printf("AUTOPILOT_VERSION: \n");
		printf("    capabilities: %lx\n", (long)ver.capabilities);

		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_PARAM_FLOAT) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_PARAM_FLOAT\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_MISSION_INT) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_MISSION_INT\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_PARAM_UNION) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_PARAM_UNION\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_FTP) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_FTP\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_SET_ATTITUDE_TARGET) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_SET_ATTITUDE_TARGET\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_LOCAL_NED) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_LOCAL_NED\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_GLOBAL_INT) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_GLOBAL_INT\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_TERRAIN) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_TERRAIN\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_SET_ACTUATOR_TARGET) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_SET_ACTUATOR_TARGET\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_FLIGHT_TERMINATION) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_FLIGHT_TERMINATION\n");
		}
		if ((ver.capabilities & MAV_PROTOCOL_CAPABILITY_COMPASS_CALIBRATION) != 0) {
			printf("      MAV_PROTOCOL_CAPABILITY_COMPASS_CALIBRATION\n");
		}

		printf("    flight_sw_version: %d\n", ver.flight_sw_version);
		printf("    middleware_sw_version: %d\n", ver.middleware_sw_version);
		printf("    os_sw_version: %d\n", ver.os_sw_version);
		printf("    board_version: %d\n", ver.board_version);
		printf("    vendor_id: %d\n", (int)ver.vendor_id);
		printf("    product_id: %d\n", (int)ver.product_id);
		printf("    product_id: %ld\n", (long)ver.uid);
	}
}

void GotoCommand::Execute() {

	printf("moving to position %f,%f,%f\n", (float)tx, (float)ty, (float)tz);
	WaitForLocalPosition();
}

void GotoCommand::WaitForLocalPosition()
{
	// wait till we have a local position.
	hasLocalPos = false;
	targetReached = false;
}

void GotoCommand::HandleMessage(void *payload)
{
	Command::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_LOCAL_POSITION_NED)
	{
		// The filtered local position
		mavlink_local_position_ned_t localPos;
		mavlink_msg_local_position_ned_decode(msg, &localPos);

		this->vx = localPos.vx;
		this->vy = localPos.vy;
		this->vz = -localPos.vz;
		this->x = localPos.x;
		this->y = localPos.y;
		this->z = -localPos.z;

		//printf("%f,%f,%f", x, y, z);

		if (!hasLocalPos) {
			hasLocalPos = true;
			HasLocalPosition();
		}
		else 
		{
			if (!targetReached && fabsf(x - tx) < nearDelta && fabsf(y - ty) < nearDelta)
			{
				targetReached = true;
				TargetReached();
			}
		}
	}
}

void GotoCommand::HasLocalPosition() {
	Goto(tx, ty, tz, -1, 0);
}

void GotoCommand::Goto(float x, float y, float z, float speed, float heading) {

	double lat = 0;
	double lon = 0;
	float alt = 0;
	tx = x;
	ty = y;
	tz = z;

	globallocalconverter_toglobal(tx, ty, -tz, &lat, &lon, &alt);

	/*
	<entry value="192" name="MAV_CMD_DO_REPOSITION">
	<description>Reposition the vehicle to a specific WGS84 global position.</description>
	<param index="1">Ground speed, less than 0 (-1) for default</param>
	<param index="2">Bitmask of option flags, see the MAV_DO_REPOSITION_FLAGS enum.</param>
	<param index="3">Reserved</param>
	<param index="4">Yaw heading, NaN for unchanged. For planes indicates loiter direction (0: clockwise, 1: counter clockwise)</param>
	<param index="5">Latitude (deg * 1E7)</param>
	<param index="6">Longitude (deg * 1E7)</param>
	<param index="7">Altitude (meters)</param>
	</entry>
	*/
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, 
		MAV_CMD_DO_REPOSITION, 
		1, // request ACK
		speed, 
		MAV_DO_REPOSITION_FLAGS_CHANGE_MODE,
		0,
		heading,
		lat,
		lon,
		alt);
}

void GotoCommand::TargetReached()
{
	targetReached = true;
}


void OrbitCommand::Execute() {

	printf("orbit current position at radius %f\n", (float)radius);
	orbiting = false;
	WaitForLocalPosition();
}

void OrbitCommand::HasLocalPosition() {
	// fly to radius
	flyingToRadius = true;
	cx = x;
	cy = y;
	cz = z;
	Goto(x + radius, y, z, -1, 0);
}

void OrbitCommand::TargetReached()
{
	flyingToRadius = false;
	orbiting = true;
	lastGotoTime = std::chrono::system_clock::now();
}

void OrbitCommand::HandleMessage(void *payload)
{
	GotoCommand::HandleMessage(payload);
	mavlink_message_t* msg = (mavlink_message_t*)payload;
	if (msg->msgid == (uint8_t)MAVLINK_MSG_ID_LOCAL_POSITION_NED)
	{		
		if (orbiting)
		{
			auto now = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = now - lastGotoTime;
			if (elapsed_seconds.count() >= 1)
			{
				// heading points to center of circle.
				float dx = x - cx;
				float dy = y - cy;
				float angle = atan2(dy, dx);

				float degrees = (angle * 180 / M_PI);
				float heading = degrees + 180; // point the camera towards the center of the circle.

				// compute next location on the circle.
				float delta = 0;
				while (true) {
					tx = radius * cosf(angle + delta);
					ty = radius * sinf(angle + delta);
					float distance = sqrtf((tx - x)*(tx - x) + (ty - y)*(ty - y));
					// let's look 4 meters ahead on the circle.
					if (distance > 4) {
						break;
					}
					delta += (M_PI / 180.0); // 1 degree increments
				}

				float targetDegrees = ((angle + delta) * 180 / M_PI);

				//printf("Flying from angle %f to angle %f with heading %f\n", degrees, targetDegrees, heading);

				// extend the vector out 10 meters so it doesn't try and start/stop/start/stop on each segment.
				double vx = (tx - x);
				double vy = (ty - y);
				double distance = sqrtf(vx*vx+ vy*vy);
				vx *= (10 / distance);
				vy *= (10 / distance);
				tx = x + vx;
				ty = y + vy;

				Goto(tx, ty, cz, 0.5, heading);
				lastGotoTime = now;
			}
		}
	}
}
