// PX4.cpp : Defines the entry point for the console application.

#include "Port.h"
#include "UdpSocketPort.h"
#include "SerialPort.h"
#include "Commands.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <EventTrace.h>
#include "geo.h"
#define MAVLINK_PACKED

// for UDP we need to buffer these packets and send them as one UDP datagram.
void my_mavlink_start_send(int channel, int length);
void my_mavlink_end_send(int channel, int length);
#define MAVLINK_START_UART_SEND(chan, length) my_mavlink_start_send(chan, length)
#define MAVLINK_END_UART_SEND(chan, length) my_mavlink_end_send(chan, length);
#include "mavlink.h"
#include "mavlink_helpers.h"

static const uint8_t mavlink_message_crcs[256] = MAVLINK_MESSAGE_CRCS;
static const uint8_t mavlink_message_lengths[256] = MAVLINK_MESSAGE_LENGTHS;

Port* port;
char mydatagram[255];
int mydatagrampos = 0;
Command** cmdTable;
bool udp = 0;
std::string ipAddr;
int portNumber = 0;
const char* comPort = "";
std::string qgc;
int qgcPort;
Port* proxy;

bool ParseIpAddress(const char* ip, std::string& addr, int& portNumber)
{
	addr = ip;
	std::vector<std::string> args = split(addr, ':');
	if (args.size() > 1)
	{
		// user specified the port
		portNumber = atoi(args[1].c_str());
		if (portNumber == 0)
		{
			return false;
		}
		addr = args[0];
	}
	return true;
}

void my_mavlink_start_send(int channel, int length)
{
	mydatagrampos = 0;
}

void my_mavlink_end_send(int channel, int length)
{
	port->Write((byte*)mydatagram, length);
}

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

//void SendCommand(int cmdid, float a1, float a2, float a3, float a4, float a5, float a6, float a7)
//{
//	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, cmdid, /* confirmation */ 1,
//		/* params */ a1, a2, a3, a4, a5, a6, a7);
//}

class EventLog : EventListener
{
public:
	EventLog() {
		EventTrace::AddListener(this);
	}

	void Write(int category, int eventId, const char* msg)
	{
		OutputDebugStringA(msg);
	}
};

const char* MavSysSensorFlags[] = {
	"None",
	"MAV_SYS_STATUS_SENSOR_3D_GYRO",// = 1, /* 0x01 3D gyro | */
	"MAV_SYS_STATUS_SENSOR_3D_ACCEL",// = 2, /* 0x02 3D accelerometer | */
	"MAV_SYS_STATUS_SENSOR_3D_MAG",// = 4, /* 0x04 3D magnetometer | */
	"MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE",// = 8, /* 0x08 absolute pressure | */
	"MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE",// = 16, /* 0x10 differential pressure | */
	"MAV_SYS_STATUS_SENSOR_GPS",// = 32, /* 0x20 GPS | */
	"MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW",// = 64, /* 0x40 optical flow | */
	"MAV_SYS_STATUS_SENSOR_VISION_POSITION",// = 128, /* 0x80 computer vision position | */
	"MAV_SYS_STATUS_SENSOR_LASER_POSITION",// = 256, /* 0x100 laser based position | */
	"MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH",// = 512, /* 0x200 external ground truth (Vicon or Leica) | */
	"MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL",// = 1024, /* 0x400 3D angular rate control | */
	"MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION",// = 2048, /* 0x800 attitude stabilization | */
	"MAV_SYS_STATUS_SENSOR_YAW_POSITION",// = 4096, /* 0x1000 yaw position | */
	"MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL",// = 8192, /* 0x2000 z/altitude control | */
	"MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL",// = 16384, /* 0x4000 x/y position control | */
	"MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS",// = 32768, /* 0x8000 motor outputs / control | */
	"MAV_SYS_STATUS_SENSOR_RC_RECEIVER",// = 65536, /* 0x10000 rc receiver | */
	"MAV_SYS_STATUS_SENSOR_3D_GYRO2",// = 131072, /* 0x20000 2nd 3D gyro | */
	"MAV_SYS_STATUS_SENSOR_3D_ACCEL2",// = 262144, /* 0x40000 2nd 3D accelerometer | */
	"MAV_SYS_STATUS_SENSOR_3D_MAG2",// = 524288, /* 0x80000 2nd 3D magnetometer | */
	"MAV_SYS_STATUS_GEOFENCE",// = 1048576, /* 0x100000 geofence | */
	"MAV_SYS_STATUS_AHRS",// = 2097152, /* 0x200000 AHRS subsystem health | */
	"MAV_SYS_STATUS_TERRAIN",// = 4194304, /* 0x400000 Terrain subsystem health | */
	"MAV_SYS_STATUS_REVERSE_MOTOR",// = 8388608, /* 0x800000 Motors are reversed | */
};

void DebugPrintSensorFlags(MAV_SYS_STATUS_SENSOR status)
{
	int flags = (MAV_SYS_STATUS_SENSOR)status;
	int size = sizeof(MavSysSensorFlags) / sizeof(char*);
	bool first = true;
	for (int  i = 1; i < size; i++)
	{
		if (flags & 1)
		{
			if (!first)
			{
				EventTrace(1,1,", ");
			}
			else 
			{
				first = false;
			}
			EventTrace(1, 1, MavSysSensorFlags[i]);
		}
		flags = flags << 1;
	}
}

bool outputHeartbeat = false;

const char* AutoPilotNames[]{
	"MAV_AUTOPILOT_GENERIC, Generic autopilot, full support for everything",
	"MAV_AUTOPILOT_RESERVED, Reserved for future use.",
	"MAV_AUTOPILOT_SLUGS, SLUGS autopilot, http://slugsuav.soe.ucsc.edu",
	"MAV_AUTOPILOT_ARDUPILOTMEGA, ArduPilotMega / ArduCopter, http://diydrones.com",
	"MAV_AUTOPILOT_OPENPILOT, OpenPilot, http://openpilot.org",
	"MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY, Generic autopilot only supporting simple waypoints",
	"MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY, Generic autopilot supporting waypoints and other simple navigation commands",
	"MAV_AUTOPILOT_GENERIC_MISSION_FULL, Generic autopilot supporting the full mission command set",
	"MAV_AUTOPILOT_INVALID,  No valid autopilot, e.g. a GCS or other MAVLink component",
	"MAV_AUTOPILOT_PPZ, PPZ UAV - http://nongnu.org/paparazzi",
	"MAV_AUTOPILOT_UDB, UAV Dev Board",
	"MAV_AUTOPILOT_FP, FlexiPilot",
	"MAV_AUTOPILOT_PX4, PX4 Autopilot - http://pixhawk.ethz.ch/px4/",
	"MAV_AUTOPILOT_SMACCMPILOT, SMACCMPilot - http://smaccmpilot.org",
	"MAV_AUTOPILOT_AUTOQUAD, AutoQuad -- http://autoquad.org",
	"MAV_AUTOPILOT_ARMAZILA,  Armazila -- http://armazila.com",
	"MAV_AUTOPILOT_AEROB, Aerob -- http://aerob.ru",
	"MAV_AUTOPILOT_ASLUAV, ASLUAV autopilot -- http://www.asl.ethz.ch"
};

const char* MavTypeNames[]
{
	"MAV_TYPE_GENERIC-  Generic micro air vehicle.",
	"MAV_TYPE_FIXED_WING-  Fixed wing aircraft.",
	"MAV_TYPE_QUADROTOR-  Quadrotor",
	"MAV_TYPE_COAXIAL-  Coaxial helicopter",
	"MAV_TYPE_HELICOPTER-  Normal helicopter with tail rotor.",
	"MAV_TYPE_ANTENNA_TRACKER-  Ground installation",
	"MAV_TYPE_GCS-  Operator control unit / ground control station",
	"MAV_TYPE_AIRSHIP-  Airship, controlled",
	"MAV_TYPE_FREE_BALLOON-  Free balloon, uncontrolled",
	"MAV_TYPE_ROCKET-  Rocket",
	"MAV_TYPE_GROUND_ROVER-  Ground rover",
	"MAV_TYPE_SURFACE_BOAT-  Surface vessel, boat, ship",
	"MAV_TYPE_SUBMARINE-  Submarine",
	"MAV_TYPE_HEXAROTOR-  Hexarotor",
	"MAV_TYPE_OCTOROTOR-  Octorotor",
	"MAV_TYPE_TRICOPTER-  Octorotor",
	"MAV_TYPE_FLAPPING_WING-  Flapping wing",
	"MAV_TYPE_KITE-  Flapping wing",
	"MAV_TYPE_ONBOARD_CONTROLLER-  Onboard companion controller",
	"MAV_TYPE_VTOL_DUOROTOR-  Two-rotor VTOL using control surfaces in vertical operation in addition. Tailsitter.",
	"MAV_TYPE_VTOL_QUADROTOR-  Quad-rotor VTOL using a V-shaped quad config in vertical operation. Tailsitter.",
	"MAV_TYPE_VTOL_TILTROTOR-  Tiltrotor VTOL",
	"MAV_TYPE_VTOL_RESERVED2-  VTOL reserved 2",
	"MAV_TYPE_VTOL_RESERVED3-  VTOL reserved 3",
	"MAV_TYPE_VTOL_RESERVED4-  VTOL reserved 4",
	"MAV_TYPE_VTOL_RESERVED5-  VTOL reserved 5",
	"MAV_TYPE_GIMBAL-  Onboard gimbal",
	"MAV_TYPE_ADSB-  Onboard ADSB peripheral"
};

struct FlagName {
public:
	int Flag;
	const char* Name;
};

void PrintFlags(const FlagName* flagNames, int value) {

	for (int i = 0; ; i++)
	{
		if (flagNames[i].Name == NULL)
			break;

		if ((value & flagNames[i].Flag) != 0) {
			printf("    %s\n", flagNames[i].Name);
		}
	}
}

const FlagName ModeFlagNames[]{
	{ MAV_MODE_FLAG_TEST_ENABLED, "MAV_MODE_FLAG_TEST_ENABLED - system has a test mode enabled. This flag is intended for temporary system tests and should not be used for stable implementations." },
	{ MAV_MODE_FLAG_AUTO_ENABLED, "MAV_MODE_FLAG_AUTO_ENABLED - autonomous mode enabled, system finds its own goal positions. Guided flag can be set or not, depends on the actual implementation."},
	{ MAV_MODE_FLAG_GUIDED_ENABLED, "MAV_MODE_FLAG_GUIDED_ENABLED - guided mode enabled, system flies MISSIONs / mission items." },
	{ MAV_MODE_FLAG_STABILIZE_ENABLED, "MAV_MODE_FLAG_STABILIZE_ENABLED - system stabilizes electronically its attitude (and optionally position). It needs however further control inputs to move around."},
	{ MAV_MODE_FLAG_HIL_ENABLED, "MAV_MODE_FLAG_HIL_ENABLED - hardware in the loop simulation. All motors / actuators are blocked, but internal software is full operational." },
	{ MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, "MAV_MODE_FLAG_MANUAL_INPUT_ENABLED - remote control input is enabled." },
	{ MAV_MODE_FLAG_SAFETY_ARMED, "MAV_MODE_FLAG_SAFETY_ARMED - MAV safety set to armed. Motors are enabled / running / can start. Ready to fly." },
	{ 0, NULL }
};

const char* MavStateNames[]{
	"MAV_STATE_UNINIT - Uninitialized system, state is unknown.",
	"MAV_STATE_BOOT - System is booting up.",
	"MAV_STATE_CALIBRATING - System is calibrating and not flight-ready.",
	"MAV_STATE_STANDBY - System is grounded and on standby. It can be launched any time.",
	"MAV_STATE_ACTIVE - System is active and might be already airborne. Motors are engaged.",
	"MAV_STATE_CRITICAL - System is in a non-normal flight mode. It can however still navigate.",
	"MAV_STATE_EMERGENCY - System is in a non-normal flight mode. It lost control over parts or over the whole airframe. It is in mayday and going down.",
	"MAV_STATE_POWEROFF - System just initialized its power-down sequence, will shut down now.",
	"MAV_STATE_ENUM_END - ",
};

void HandleHeartbeat(mavlink_message_t* msg)
{
	if (!outputHeartbeat) {
		outputHeartbeat = true;

		mavlink_heartbeat_t heartbeat;
		mavlink_msg_heartbeat_decode(msg, &heartbeat);

		printf("Version=%d\n", (int)heartbeat.mavlink_version);

		if (heartbeat.type < MAV_TYPE_ENUM_END) {
			printf("Type=%s\n", MavTypeNames[heartbeat.type]);
		}

		if (heartbeat.autopilot < MAV_AUTOPILOT_ENUM_END) {
			printf("Autopilot=%s\n", AutoPilotNames[heartbeat.autopilot]);
		}

		if (heartbeat.system_status < MAV_STATE_ENUM_END) {
			printf("State=%s\n", MavStateNames[heartbeat.system_status]);
		}

		printf("Base mode:\n");
		PrintFlags(ModeFlagNames, heartbeat.base_mode);

		printf("Custom mode=%d\n", (int)heartbeat.custom_mode);

	}

	// send back a heart beat so that the PX4 thinks we are still connected (otherwise it triggers failsafe).
	mavlink_msg_heartbeat_send(MAVLINK_COMM_0,
		MAV_TYPE_GCS,            // MAV_TYPE
		MAV_AUTOPILOT_INVALID,   // MAV_AUTOPILOT
		MAV_MODE_MANUAL_ARMED,   // MAV_MODE
		0,                       // custom mode
		MAV_STATE_ACTIVE);       // MAV_STATE
}

const FlagName SensorFlagNames[]{
	{ MAV_SYS_STATUS_SENSOR_3D_GYRO, "3D gyro"},
	{ MAV_SYS_STATUS_SENSOR_3D_ACCEL, "3D accelerometer"},
	{ MAV_SYS_STATUS_SENSOR_3D_MAG, "3D magnetometer"},
	{ MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE, "absolute pressure"},
	{ MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE, "differential pressure"},
	{ MAV_SYS_STATUS_SENSOR_GPS, "GPS"},
	{ MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW, "optical flow"},
	{ MAV_SYS_STATUS_SENSOR_VISION_POSITION, "computer vision position"},
	{ MAV_SYS_STATUS_SENSOR_LASER_POSITION, "laser based position"},
	{ MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH, "external ground truth (Vicon or Leica)"},
	{ MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL, "3D angular rate control"},
	{ MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION, "attitude stabilization"},
	{ MAV_SYS_STATUS_SENSOR_YAW_POSITION, "yaw position"},
	{ MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL, "z/altitude control"},
	{ MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL, "x/y position control"},
	{ MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS, "motor outputs / control"},
	{ MAV_SYS_STATUS_SENSOR_RC_RECEIVER, "rc receiver"},
	{ MAV_SYS_STATUS_SENSOR_3D_GYRO2, "2nd 3D gyro"},
	{ MAV_SYS_STATUS_SENSOR_3D_ACCEL2, "2nd 3D accelerometer"},
	{ MAV_SYS_STATUS_SENSOR_3D_MAG2, "2nd 3D magnetometer"},
	{ MAV_SYS_STATUS_GEOFENCE, "geofence"},
	{ MAV_SYS_STATUS_AHRS, "AHRS subsystem health"},
	{ MAV_SYS_STATUS_TERRAIN, "Terrain subsystem health"},
	{ MAV_SYS_STATUS_REVERSE_MOTOR, "Motors are reversed"},
	{ MAV_SYS_STATUS_SENSOR_ENUM_END, ""},
};

bool firstSystemStatus = true;

void PrintFirstSystemStatus(mavlink_message_t* msg)
{
	if (firstSystemStatus) {
		firstSystemStatus = false;

		mavlink_sys_status_t status;

		mavlink_msg_sys_status_decode(msg, &status);
		
		printf("System status:\n");


		printf("onboard sensors present:\n");
		PrintFlags(ModeFlagNames, status.onboard_control_sensors_present);

		printf("onboard sensors enabled:\n");
		PrintFlags(ModeFlagNames, status.onboard_control_sensors_enabled);

		printf("CPU load %d\n", (int)status.load);

		printf("battery voltage %d millivolts\n", (int)status.voltage_battery);
		printf("battery current %d milliamps\n", (int)status.current_battery);
		printf("drop_rate_comm = %d\n", (int)status.drop_rate_comm);
		printf("errors_comm = %d\n", (int)status.errors_comm);
		printf("battery_remaining = %d\n", (int)status.battery_remaining);

	}
}

float homeLat = 0;
float homeLon = 0;
float homeAlt = 0;
float currentLat = 0;
float currentLon = 0;
float currentAlt = 0;
float currentHeading = 0;

int attitudeTime = 0;
int attitudeRate = 0;
int gpsTime = 0;
int gpsRate = 0;
bool receiveSignaled = false;
HANDLE receiveEvent = NULL;
Command* currentCommand = NULL;
byte proxySeq = 0;
//const uint8_t mavlink_message_crcs[256] = MAVLINK_MESSAGE_CRCS;

void SetHomePosition(float lat, float lon, float alt)
{
	//mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_DO_SET_HOME, 1, 0, 0, 0, 0, lat, lon, alt);
	//mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_GET_HOME_POSITION, 1, 0, 0, 0, 0, 0, 0, 0);

	globallocalconverter_init(lat, lon, alt, 0);
	printf("Setting home position to lat=%f, lon=%f, alt=%f\n", lat, lon, alt);

}

void SetFlightMode(MAV_MODE_FLAG mode)
{
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_DO_SET_MODE, 1, (float)mode, 0, 0, 0, 0, 0, 0);
}

int ReadPackets(LPVOID arg)
{
    mavlink_message_t msg;
    mavlink_status_t status;
    int channel = 0;

    HRESULT hr = 0;
    while (hr == 0)
    {
        int read = 0;
        byte data = 0;
        hr = port->Read(&data, 1, &read);

        if (hr == 0 && read == 1)
        {
            if (mavlink_frame_char(channel, data, &msg, &status) != MAVLINK_FRAMING_INCOMPLETE)
            {

				if (proxy != nullptr) {
					const BYTE* ptr = (const BYTE*)&msg;
					ptr += 2; // skip the initial checksum field (checksum comes at the end of the payload).
					proxy->Write(ptr, msg.len + MAVLINK_NUM_NON_PAYLOAD_BYTES);
				}

				if (currentCommand != NULL)
				{
					// let the current command take a crack at it.
					currentCommand->HandleMessage(&msg);
				}

                if (msg.msgid == (byte)MAVLINK_MSG_ID_HEARTBEAT)
                {
					HandleHeartbeat(&msg);
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_ATTITUDE)
                {
                    // computed attitude has changed
					long now = GetTickCount();
					if (attitudeTime != 0) {
						if (now == attitudeTime)
						{
							attitudeRate = 1000;
						}
						else 
						{
							attitudeRate = 1000 / (now - attitudeTime);
						}
					}
					attitudeTime = now;
					mavlink_attitude_t att;
					mavlink_msg_attitude_decode(&msg, &att);
					//PRT_VALUE* pMessage = NULL;
					//p_mavlink_msg_attitude_decode(&msg, &pMessage);
					//printf("P received attitute\n");
					//PrtPrintValue(pMessage);
					//printf("\n");
					//EventTrace(1, 1, "Received attitude, acc=[%2.2f %2.2f %2.2f]\n", att.pitch, att.roll, att.yaw);
					//PrtFreeValue(pMessage);
                }
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_GLOBAL_POSITION_INT)
				{
					// The global position changed.
					long now = GetTickCount();
					if (gpsTime != 0) {
						if (now == gpsTime)
						{
							gpsRate = 1000;
						}
						else
						{
							gpsRate = 1000 / (now - gpsTime);
						}
					}
					gpsTime = now;
					mavlink_global_position_int_t pos;
					mavlink_msg_global_position_int_decode(&msg, &pos);
					if ((int)homeLat == 0)
					{
						homeLat = (float)((float)pos.lat / 1e7);
						homeLon = (float)((float)pos.lon / 1e7);
						homeAlt = (float)((float)pos.alt / 1000);
						EventTrace(1, 1, "Home position, lat=%f, long=%fm alt=%f\n", currentLat, currentLon, currentAlt);

						SetHomePosition(homeLat, homeLon, homeAlt);
						SetFlightMode(MAV_MODE_FLAG_STABILIZE_ENABLED);
					}
				}
				else if (msg.msgid == MAVLINK_MSG_ID_RC_CHANNELS)
				{
					mavlink_rc_channels_t ch;
					mavlink_msg_rc_channels_decode(&msg, &ch);
					/*EventTrace(1, 1, "MAVLINK_MSG_ID_RC_CHANNELS channels=%d, rssi=%d, %d, %d, %d, %d\n",		
						(int)ch.chancount,
						(int)ch.rssi,
						(int)ch.chan1_raw,
						(int)ch.chan2_raw,
						(int)ch.chan3_raw,
						(int)ch.chan4_raw);*/
				}
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_SERVO_OUTPUT_RAW)
                {
                    // The RAW values of the servo outputs
					mavlink_servo_output_raw_t out;
					mavlink_msg_servo_output_raw_decode(&msg, &out);

					/*EventTrace(1, 1, "MAVLINK_MSG_ID_SERVO_OUTPUT_RAW port=%d\t%d,\t%d,\t%d,\t%d\n",	
						(int)out.port,
						(int)out.servo1_raw,
						(int)out.servo1_raw,
						(int)out.servo1_raw,
						(int)out.servo1_raw);
*/
                }

                else if (msg.msgid == (byte)MAVLINK_MSG_ID_VFR_HUD)
                {
                    // Metrics typically displayed on a HUD for fixed wing aircraft
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_HIGHRES_IMU)
                {
                    // The IMU readings in SI units in NED body frame
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_ALTITUDE)
                {
                    // The current system altitude
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_SYS_STATUS)
                {
					PrintFirstSystemStatus(&msg);
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_BATTERY_STATUS)
                {
					//PRT_VALUE* pMessage = NULL;
					//p_mavlink_msg_battery_status_decode(&msg, &pMessage);
					//int batter_remaining = PrtPrimGetInt(PrtTupleGetNC(pMessage, P_FIELD_INDEX_mavlink_battery_status_t__battery_remaining));
					/*if (batter_remaining < 60)
						printf("WARNING: Battery Low (%d\%)", batter_remaining);
					else
						printf("Battery Remaining (%d\%)", batter_remaining);
					*/
					//PrtFreeValue(pMessage);
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_ATTITUDE_TARGET)
                {
                    // Reports the current commanded attitude of the vehicle as specified by the autopilot
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_EXTENDED_SYS_STATE)
                {
                    // Provides state for additional features
                    // The general system state
					//mavlink_extended_sys_state_t status;
					//mavlink_msg_extended_sys_state_decode(&msg, &status);
					//EventTrace(1, 1, "ExtendedSysStatus: \n");
					//EventTrace(1, 1, "    landed_state=%d\n", (int)status.landed_state);
					//EventTrace(1, 1, "    vtol_state=%d\n", (int)status.vtol_state);
                }
                else if (msg.msgid == (byte)MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET)
				{
                    // temporarily commenting this one out because we receive too many of these so we can't see the other messages...
					/*mavlink_actuator_control_target_t actControl;
					PRT_VALUE* pMessage = NULL;
					mavlink_msg_actuator_control_target_decode(&msg, &actControl);
					p_mavlink_msg_actuator_control_target_decode(&msg, &pMessage);
					PrtPrintValue(pMessage);
					printf("\n");
					printf("Received actuator control [%f %f] %d %ld\n", actControl.controls[0], actControl.controls[1], (int)actControl.group_mlx, actControl.time_usec);
                    PrtFreeValue(pMessage);*/
				}
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_STATUSTEXT)
				{
					mavlink_statustext_t status;
					mavlink_msg_statustext_decode(&msg, &status);
					printf("Received status sev=%d, text, %s\n", (int)status.severity, status.text);
				}
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_MESSAGE_INTERVAL)
				{
					mavlink_message_interval_t msgInt;
					mavlink_msg_message_interval_decode(&msg, &msgInt);
					printf("Received message interval for msg=%d, interval = %d\n", (int)msgInt.message_id, msgInt.interval_us);
				}
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_COMMAND_LONG)
				{
					// command was received...
					mavlink_command_long_t cmd;
					mavlink_msg_command_long_decode(&msg, &cmd);
					printf("Received command id %d from target %d, component %d\n", (int)cmd.command, (int)cmd.target_system, (int)cmd.target_component);
				}
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_NAMED_VALUE_INT)
				{
				  //<message id="252" name="NAMED_VALUE_INT">
					 //  <description>Send a key-value pair as integer. The use of this message is discouraged for normal packets, but a quite efficient way for testing new messages and getting experimental debug output.</description>
					 //  <field type="uint32_t" name="time_boot_ms">Timestamp (milliseconds since system boot)</field>
					 //  <field type="char[10]" name="name">Name of the debug variable</field>
					 //  <field type="int32_t" name="value">Signed integer value</field>
				  //</message>
					mavlink_named_value_int_t value;
					mavlink_msg_named_value_int_decode(&msg, &value);
					printf("PARAM %s=%d\n", value.name, value.value);
				}
				else if (msg.msgid == (byte)MAVLINK_MSG_ID_HIL_CONTROLS)
				{
					mavlink_hil_controls_t value;
					mavlink_msg_hil_controls_decode(&msg, &value);
					//printf("HIL_CONTROLS %f, %f, %f, %f\n", value.pitch_elevator, value.roll_ailerons, value.throttle, value.yaw_rudder);
				}
				//printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msg.msgid, msg.seq, msg.compid, msg.sysid);
            }
        }
		

		if (!receiveSignaled)
		{
			receiveSignaled = true;
			SetEvent(receiveEvent);
		}

    }

    return 0;
}

int ProxyPackets(LPVOID arg)
{
	mavlink_message_t msg;
	mavlink_status_t status;
	int channel = 0;

	HRESULT hr = 0;
	while (hr == 0)
	{
		int read = 0;
		byte data = 0;
		hr = proxy->Read(&data, 1, &read);

		if (hr == 0 && read == 1)
		{
			if (mavlink_frame_char(channel, data, &msg, &status) != MAVLINK_FRAMING_INCOMPLETE)
			{
				if (msg.msgid != (byte)MAVLINK_MSG_ID_HEARTBEAT) {
					// send QGC message to drone.
					const BYTE* ptr = (const BYTE*)&msg;
					ptr += 2; // skip the initial checksum field (checksum comes at the end of the payload).
					proxy->Write(ptr, msg.len + MAVLINK_NUM_NON_PAYLOAD_BYTES);
				}
			}
		}
	}
	return 0;
}


void SetMessageInterval(int msgId, int frequency)
{
	float intervalMicroseconds = 1000000.0f / frequency;
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_SET_MESSAGE_INTERVAL, /* confirmation */ 1, /* params */ (float)msgId, intervalMicroseconds, 0, 0, 0, 0, 0);

	Sleep(1000);

	// now check that the interval was set by requesting the new interval.
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, MAV_CMD_GET_MESSAGE_INTERVAL, /* confirmation */ 1, /* params */ (float)msgId, 0, 0, 0, 0, 0, 0);
}

mavlink_system_t mavlink_system;

#define DEFAULT_BUFLEN 512
#define DEFAULT_MAVLINK_PORT 14550

void PrintUsage() {
	printf("Usage: PX4 [-udp ipaddr] [-com port] [-qgc ipaddr]\n");
	printf("Connects to PX4 either over udp or serial COM port\n");
	printf("The optional qgc argument causes this app to also proxy all mavlink messages from the drone to/from QGroundControl");
	printf("If no arguments it will find a COM port matching PX4\n");
}


bool ParseCommandLine(int argc, const char* argv[])
{
	// parse command line
	for (int i = 1; i < argc; i++)
	{
		const char* arg = argv[i];
		if (arg[0] == '-' || arg[0] == '/')
		{
			std::string lower(arg + 1);
			_strlwr_s((char*)lower.c_str(), lower.length() + 1);
			if (lower == "udp")
			{
				if (i + 1 < argc)
				{
					udp = true;
					if (!ParseIpAddress(argv[++i], ipAddr, portNumber)) 
					{
						printf("### Error: invalid ip address after -udp argument\n");
						return false;
					}
				}
				else
				{
					printf("### Error: missing ip address after -udp argument\n");
					return false;
				}
			}
			else if (lower == "com")
			{
				udp = false;
				if (i + 1 < argc)
				{
					ipAddr = argv[++i];
				}
			}
			else if (lower == "h" || lower == "?" || lower == "help" || lower == "-help")
			{
				return false;
			}
			else if (lower == "qgc")
			{
				if (i + 1 < argc)
				{
					udp = true;
					if (!ParseIpAddress(argv[++i], qgc, qgcPort))
					{
						printf("### Error: invalid ip address after -qgc argument\n");
						return false;
					}
				}
				else
				{
					printf("### Error: missing ip address after -qgc argument\n");
					return false;
				}
			}
			else
			{
				printf("### Error: unexpected argument: %s\n", arg);
				return false;
			}
		}
		else
		{
			printf("### Error: unexpected argument: %s\n", arg);
			return false;
		}
	}
	return true;
}

std::vector<std::string> split(std::string s, char splitChar)
{
	auto start = s.begin();
	std::vector<std::string> result;
	for (auto it = s.begin(); it != s.end(); it++)
	{
		if (*it == splitChar)
		{
			if (start < it)
			{
				result.push_back(std::string(start, it));
			}
			start = it;
			start++;
		}
		else if (*it == '"')
		{
			// treat literals as one word
			it++;
			while (*it != '"' && it != s.end())
			{
				it++;
			}
		}
	}
	if (start < s.end())
	{
		result.push_back(std::string(start, s.end()));
	}
	return result;
}

int main(int argc, const char* argv[])
{
    int baudRate = 115200;
    int dataBits = 8;
    bool dtr_enable = false;
    bool rts_enable = false;
    int readTimeout = -1;
    int write_timeout = 500;
    int readBufferSize = 16384;
    int writeBufferSize = 2048;
	const char* initString = "sh /etc/init.d/rc.usb\n";
	EventLog log;
    mavlink_system.sysid = 255;    
	mavlink_system.compid = 1;

	cmdTable = new Command*[10]{
		new ArmDisarmCommand(),
		new GetParamsCommand(),
		new TakeOffCommand(),
		new LandCommand(),
		new MissionCommand(),
		new CapabilitiesCommand(),
		new GotoCommand(),
		new RtlCommand(),
		new OrbitCommand(),
		NULL
	};

	if (!ParseCommandLine(argc, argv))
	{
		PrintUsage();
		return 1;
	}

	receiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (UdpSocketPort::Initialize() != 0)
	{
		return 1;
	}

	if (udp)
	{
		UdpSocketPort* socket = new UdpSocketPort();

		int portNumber = DEFAULT_MAVLINK_PORT;
		int hr = socket->Connect(ipAddr.c_str(), portNumber);
		if (hr != 0)
		{
			printf("Could not open the socket to %s:%d, error=%d\n", ipAddr.c_str(), portNumber, hr);
			if (hr == ERROR_ACCESS_DENIED)
			{
				printf("Error ERROR_ACCESS_DENIED, is another app using the COM port?\n");
			}
			return 1;
		}

		port = socket;
	}
	else
	{
		SerialPort * serial = new SerialPort();
		std::string name;
		int hr = serial->Find("PX4", name);
		if (hr != 0 || name.length() == 0)
		{
			printf("### Error: could not find the PX4 Serial Port");
			return 1;
		}
		else
		{
			printf("Opening PX4 SerialPort on %s\n", name.c_str());
		}

		hr = serial->Open(name.c_str(), baudRate, dataBits, Parity_None, StopBits_10, dtr_enable, rts_enable, Handshake_None, readTimeout, write_timeout, readBufferSize, writeBufferSize);
		port = serial;

		// send this right away.
		hr = port->Write((byte*)initString, (int)strlen(initString));
	}

	if (qgc.size() > 0)
	{
		UdpSocketPort* socket = new UdpSocketPort();
		int portNumber = udp ? 14560 : DEFAULT_MAVLINK_PORT;
		int hr = socket->Connect(qgc.c_str(), 0, qgcPort);
		if (hr != 0)
		{
			printf("Could not open the socket to %s:%d, error=%d\n", qgc.c_str(), qgcPort, hr);
			if (hr == ERROR_ACCESS_DENIED)
			{
				printf("Error ERROR_ACCESS_DENIED, is another app using the COM port?\n");
			}
			return 1;
		}

		proxy = socket;
	}

    DWORD threadId;
    HANDLE theadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadPackets, NULL, 0, &threadId);

	if (qgc.size() > 0) {

		DWORD threadId2;
		HANDLE theadHandle2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProxyPackets, NULL, 0, &threadId2);
	}

	printf("Waiting for heartbeat from PX4...\n");

	// wait for a heartbeat msg since this will give us the port to send commands to...
	if (WAIT_TIMEOUT == WaitForSingleObject(receiveEvent, 10000))
	{
		printf("Error no heartbeat from PX4\n");
		return 1;
	}

	printf("Ready...\n");
    std::string line;
    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        if (line.length() > 0)
        {
            _strlwr_s((char*)line.c_str(), line.length()+1);
			if (line.length() == 0)
			{
				continue;
			}
			std::vector<std::string> args = split(line, ' ');
			std::string cmd = args[0];

			currentCommand = NULL;

			if (cmd == "x")
			{
				break;
			}
			else if (cmd == "?" || cmd == "help")
			{
				for (int i = 0; ; i++)
				{
					Command* cmd = cmdTable[i];
					if (cmd == NULL)
					{
						break;
					}
					if (args.size() > 1 && args[1] == cmd->Name)
					{
						cmd->PrintHelp();
						break;
					}
					else {
						printf("%s\n", cmd->Name.c_str());
					}

				}
			}
			else {
				for (int i = 0; ; i++)
				{
					Command* cmd = cmdTable[i];
					if (cmd == NULL)
					{
						break;
					}
					if (cmd->Parse(args))
					{
						// found it!
						currentCommand = cmd;
						break;
					}
				}
				if (currentCommand != NULL)
				{
					currentCommand->Execute();
				}
				else
				{
					printf("Unknown command.  Type '?' to get list of commands\n");
				}

			}

/*
			if (cmd == "a")
            {
				if (attitudeRate == 0)
				{
					std::cout << "Fast attitude stream\n";
					SetMessageInterval(MAVLINK_MSG_ID_ATTITUDE, 10);
				}
				else if (attitudeRate > 1)
				{
					std::cout << "Slow attitude stream\n";
				    SetMessageInterval(MAVLINK_MSG_ID_ATTITUDE, 1);
				}
				else 
				{
					attitudeRate = 0;
					std::cout << "Stop attitude stream\n";
					SetMessageInterval(MAVLINK_MSG_ID_ATTITUDE, 0);
				}
            }
            else if (cmd == "g")
            {
				if (gpsRate == 0)
				{
					std::cout << "Fast gps stream\n";
					SetMessageInterval(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, 10);
				}
				else if (gpsRate > 1)
				{
					std::cout << "Slow gps stream\n";
					SetMessageInterval(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, 1);
				}
				else
				{
					gpsRate = 0;
					std::cout << "Stop gps stream\n";
					SetMessageInterval(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, 0);
				}
            }
			else if (cmd == "r")
			{
				SetMessageInterval(MAVLINK_MSG_ID_RC_CHANNELS, 10);
			}*/
        }
    }
    
    return 0;
}

