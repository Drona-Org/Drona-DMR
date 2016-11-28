
// Note these must be defined before including "mavlink.h" for the first time.
void mavlink_start_send(int channel, int length);
void mavlink_end_send(int channel, int length);
#define MAVLINK_START_UART_SEND(chan, length) mavlink_start_send(chan, length)
#define MAVLINK_END_UART_SEND(chan, length) mavlink_end_send(chan, length);

#include "POrb.h"
#include "POrbMavlink.h"
//#include "PFiles.h"
#include "UdpSocketPort.h"
#include "Commands.h"
//#include "P_common_MessageTypeFunctions.h"
//#include "PTrace.h"
#include "mavlink.h"
#include "mavlink_helpers.h"
#include "mavlink_types.h"
#include <pthread.h>

#include <chrono>
#include <thread>

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

/*
Set up the mavlink macros and globals
*/

#define DEFAULT_BUFLEN 512
static mavlink_system_t mavlink_system;

static const uint8_t mavlink_message_crcs[256] = MAVLINK_MESSAGE_CRCS;
static const uint8_t mavlink_message_lengths[256] = MAVLINK_MESSAGE_LENGTHS;


/*
Set up the mavlink communication using buffering
*/
char datagram[255];
int datagrampos = 0;

void mavlink_start_send(int channel, int length)
{
	datagrampos = 0;
}

void mavlink_end_send(int channel, int length)
{
	POrbMavlink::port->Write((BYTE*)datagram, length);
}

static inline void _mavlink_send_uart(mavlink_channel_t chan, const char *buf, uint16_t len)
{
	if (len + datagrampos > 255)
	{
		printf("### Message is too big\n");
		exit(1);
	}
	::memcpy(datagram + datagrampos, buf, len);
	datagrampos += len;
}



VOID POrbMavlink::POrbSendToMaster(int *topic, int *px4_event, void* px4_payload)
{
	//EventTrace(PProgram, 0, "Publishing topic: %d with event %d\n", topic, px4_event);
	int P_EVENT_POrbPublish = 5;
	if (POrbMasterMachine != NULL)
	{
		//static void* eventName = PrtMkEventValue(P_EVENT_POrbPublish);
		/*void* ev_val = PrtMkEventValue(px4_event);
		void* topic_val = PrtMkIntValue(topic);
		void* pay_val = PrtMkDefaultValue(P_GEND_TYPE_POrbPubMsgType);
		PrtTupleSetEx(pay_val, 0, topic_val, PRT_FALSE);
		PrtTupleSetEx(pay_val, 1, ev_val, PRT_FALSE);
		PrtTupleSetEx(pay_val, 2, px4_payload, PRT_TRUE);
		PrtSend(PX4ModelMachine, POrbMasterMachine, eventName, pay_val, PRT_TRUE);

		// this allows timers to fire on this thread, otherwise the mavlink channel keeps us so busy
		// there is no time for the timers.
		SleepEx(1, TRUE);*/
	}
}
static inline void mavlink_msg_command_long_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t command, uint8_t confirmation, float param1, float param2, float param3, float param4, float param5, float param6, float param7)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_COMMAND_LONG_LEN];
	_mav_put_float(buf, 0, param1);
	_mav_put_float(buf, 4, param2);
	_mav_put_float(buf, 8, param3);
	_mav_put_float(buf, 12, param4);
	_mav_put_float(buf, 16, param5);
	_mav_put_float(buf, 20, param6);
	_mav_put_float(buf, 24, param7);
	_mav_put_uint16_t(buf, 28, command);
	_mav_put_uint8_t(buf, 30, target_system);
	_mav_put_uint8_t(buf, 31, target_component);
	_mav_put_uint8_t(buf, 32, confirmation);

    //_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_LONG, buf, MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN, MAVLINK_MSG_ID_COMMAND_LONG_LEN, MAVLINK_MSG_ID_COMMAND_LONG_CRC);
#else
	mavlink_command_long_t packet;
	packet.param1 = param1;
	packet.param2 = param2;
	packet.param3 = param3;
	packet.param4 = param4;
	packet.param5 = param5;
	packet.param6 = param6;
	packet.param7 = param7;
	packet.command = command;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.confirmation = confirmation;

   // _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_LONG, (const char *)&packet, MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN, MAVLINK_MSG_ID_COMMAND_LONG_LEN, MAVLINK_MSG_ID_COMMAND_LONG_CRC);
#endif
}


void SendCommand(int cmdid, bool confirm, float a1, float a2, float a3, float a4, float a5, float a6, float a7)
{
	//need to keep that
	mavlink_msg_command_long_send(MAVLINK_COMM_0, /*system_id*/ 1, /*component_id*/ 1, cmdid, /* confirmation */ confirm ? 1 : 0,
		/* params */ a1, a2, a3, a4, a5, a6, a7);

	/*if (cmdid == MAV_CMD_SET_MESSAGE_INTERVAL || cmdid == MAV_CMD_GET_MESSAGE_INTERVAL || cmdid == MAV_CMD_GET_HOME_POSITION ||
		cmdid == MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES || cmdid == MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN)
	{
		if (confirm) {
			EventTrace(PProgram, 0, "Confirmation request on command %d, but this command does not generate an ACK\n", cmdid);
		}
	}*/

}

//PRT_VALUE *P_FUN_SetReady_IMPL(PRT_MACHINEINST *context)
/*PRT_VALUE *P_FUN_FlightControllerMachine_FlightControllerReady_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

	POrbMavlink::ready = true;

	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return NULL;
}*/



Port* POrbMavlink::port = NULL;
int POrbMavlink::heartbeats = 0;
bool POrbMavlink::ready = false;
void* POrbMavlink::POrbMasterMachine = NULL;
void* POrbMavlink::PX4ModelMachine = NULL;

/*
Functions for POrbMavlink
*/
bool POrbMavlink::Initialize(Port* portToUse)
{
	POrbMavlink::port = portToUse;

	//initialize the ids
	mavlink_system.sysid = 255;
	mavlink_system.compid = 1;

	//create the read mavlink messages thread
	//TODO: Do some error handling here
	DWORD readThreadId;
	//HANDLE readThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DispatchMavlinkMessages, NULL, 0, &readThreadId);

	int readThread = pthread_create(&readThreadId, NULL, (void* (*)(void*)) DispatchMavlinkMessages, NULL);
	//printf("HELLO");
	if (!WaitForHeartbeat()) {
		printf("POrbMavlink::Initialize is not getting a heartbeat from the drone\n");
		return false;
	}

	return true;
}

bool POrbMavlink::WaitForHeartbeat()
{
	printf("POrbMavlink::Initialize looking for drone heartbeat...");
	//int retries = 10;
	int retries =80;
	while (retries-- > 0)
	{
		printf(".");
		if (heartbeats > 0)
		{
			printf("\n");
			return true;
		}		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//SleepEx(1000, true);
	}
	printf("\n");
	return false;
}


static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint8_t type, uint8_t autopilot, uint8_t base_mode, uint32_t custom_mode, uint8_t system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
	_mav_put_uint32_t(buf, 0, custom_mode);
	_mav_put_uint8_t(buf, 4, type);
	_mav_put_uint8_t(buf, 5, autopilot);
	_mav_put_uint8_t(buf, 6, base_mode);
	_mav_put_uint8_t(buf, 7, system_status);
	_mav_put_uint8_t(buf, 8, 3);

    //_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
	mavlink_heartbeat_t packet;
	packet.custom_mode = custom_mode;
	packet.type = type;
	packet.autopilot = autopilot;
	packet.base_mode = base_mode;
	packet.system_status = system_status;
	packet.mavlink_version = 3;

    //_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)&packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}

VOID SendHeartbeat()
{
	mavlink_msg_heartbeat_send(MAVLINK_COMM_0,
		MAV_TYPE_GCS,            // MAV_TYPE
		MAV_AUTOPILOT_INVALID,   // MAV_AUTOPILOT
		MAV_MODE_MANUAL_ARMED,   // MAV_MODE
		0,                       // custom mode
		MAV_STATE_ACTIVE);       // MAV_STATE

}

enum Topics
{
  Topics_heartbeat_topic = 0,
  Topics_attitude_topic = 1,
  Topics_global_position_topic = 2,
  Topics_local_position_topic = 3,
  Topics_battery_status_topic = 4,
  Topics_gps_raw_int_topic = 5,
  Topics_gps_status_topic = 6,
  Topics_command_ack_topic = 7,
  Topics_extended_sys_state_topic = 8,
  Topics_px4status_topic = 9,
  Topics_altitude_reached_topic = 10,
  Topics_geofence_reached_topic = 11,
  Topics_heartbeat_status_topic = 12,
  Topics_battery_critical_topic = 13,
  Topics_gps_health_topic = 14,
  Topics_vehicle_ready_topic = 15,
  Topics_vehicle_armed_topic = 16,
  Topics_vehicle_disarmed_topic = 17,
  Topics_vehicle_landed_topic = 18,
  Topics_vehicle_loitering_topic = 19,
  Topics_vehicle_crashed_topic = 20,
  _Topics_COUNT = 21
};

enum P_EVENTS
{
  _P_EVENT_NULL = 0,
  _P_EVENT_HALT = 1,
  P_EVENT_Command = 2,
  P_EVENT_CommandFailed = 3,
  P_EVENT_CommandSucceeded = 4,
  P_EVENT_POrbPublish = 5,
  P_EVENT_POrbSubscribe = 6,
  P_EVENT_SetGeofenceRadius = 7,
  P_EVENT_SetTargetAltitude = 8,
  P_EVENT_altitude_reached = 9,
  P_EVENT_amm_reached = 10,
  P_EVENT_attitude = 11,
  P_EVENT_batt_mon_init = 12,
  P_EVENT_battery_critical = 13,
  P_EVENT_battery_status = 14,
  P_EVENT_cmd_local = 15,
  P_EVENT_cmd_retry = 16,
  P_EVENT_command_ack = 17,
  P_EVENT_extended_sys_state = 18,
  P_EVENT_fc_armed = 19,
  P_EVENT_fc_disarmed = 20,
  P_EVENT_fc_emergency_landing = 21,
  P_EVENT_fc_finish_mission_goto = 22,
  P_EVENT_fc_px4_battery_critical = 23,
  P_EVENT_fc_px4_gps_locked = 24,
  P_EVENT_fc_px4_gps_lost = 25,
  P_EVENT_fc_px4_no_heartbeat = 26,
  P_EVENT_fc_ready = 27,
  P_EVENT_geofence_reached = 28,
  P_EVENT_global_position = 29,
  P_EVENT_gps_health_update = 30,
  P_EVENT_gps_raw_int = 31,
  P_EVENT_gps_status = 32,
  P_EVENT_gpshmm_init = 33,
  P_EVENT_heartbeat = 34,
  P_EVENT_heartbeat_monitor_local = 35,
  P_EVENT_heartbeat_status_changed = 36,
  P_EVENT_local_position = 37,
  P_EVENT_mission_arm = 38,
  P_EVENT_mission_disarm = 39,
  P_EVENT_mission_finished = 40,
  P_EVENT_mission_goto = 41,
  P_EVENT_mission_land = 42,
  P_EVENT_mission_loitering = 43,
  P_EVENT_mission_takeoff = 44,
  P_EVENT_porb_local = 45,
  P_EVENT_timer_cancel = 46,
  P_EVENT_timer_cancel_failure = 47,
  P_EVENT_timer_cancel_success = 48,
  P_EVENT_timer_init = 49,
  P_EVENT_timer_start = 50,
  P_EVENT_timer_timeout = 51,
  P_EVENT_vehicle_armed = 52,
  P_EVENT_vehicle_crashed = 53,
  P_EVENT_vehicle_disarmed = 54,
  P_EVENT_vehicle_landed = 55,
  P_EVENT_vehicle_loitering = 56,
  P_EVENT_vehicle_ready = 57,
  _P_EVENTS_COUNT = 58
};  




DWORD POrbMavlink::DispatchMavlinkMessages(LPVOID arg)
{	
	HRESULT readSuccess = 0;

	//Declare all variables for optimization
	void* pMessage_heartbeat = NULL;
	void* pMessage_global_position = NULL;
	void* pMessage_gps_raw = NULL;
	void* pMessage_gps_status = NULL;
	void* pMessage_attitute = NULL;
	void* pMessage_battery_status = NULL;
	void* pMessage_local_position_ned = NULL;
	void* pMessage_command_ack = NULL;
	void* pMessage_extended_sys_state = NULL;

	
	while (readSuccess == 0)
	{
		int read = 0;
		BYTE dataread = 0;
		mavlink_message_t *msg;
		mavlink_status_t status;
		uint8_t channel = 0;

		//read a byte
		printf("TEST");

		readSuccess = port->Read(&dataread, 1, &read);
		printf("HI");

		if (readSuccess == 0 && read == 1)
		{
			if (mavlink_frame_char(channel, (uint8_t) dataread.to_ulong(), msg, &status) != MAVLINK_FRAMING_INCOMPLETE) 
			{
				if (!POrbMavlink::ready)
				{
					if ((BYTE)msg->msgid == MAVLINK_MSG_ID_HEARTBEAT)
					{
						heartbeats++;
					}
					continue;
				}

				// todo: do we want to format all mavlink messages for our log?
				//EventTrace(Mavlink, msg.msgid, "\n");
				switch ((int)msg->msgid)
				{
					case MAVLINK_MSG_ID_HEARTBEAT:
						//p_mavlink_msg_heartbeat_decode(&msg, &pMessage_heartbeat);
						//POrbSendToMaster(Topics_heartbeat_topic, P_EVENT_heartbeat, pMessage_heartbeat);
						heartbeats++;
						break;
					case MAVLINK_MSG_ID_ATTITUDE:
						//p_mavlink_msg_attitude_decode(&msg, &pMessage_attitute);
						//POrbSendToMaster(Topics_attitude_topic, P_EVENT_attitude, pMessage_attitute);
						break;
					case MAVLINK_MSG_ID_ATTITUDE_TARGET:
						mavlink_attitude_target_t target;
						//mavlink_msg_attitude_target_decode(&msg, &target);
						//EventTrace(PProgram, 0, "MAVLINK_MSG_ID_ATTITUDE_TARGET: q=[%f,%f,%f,%f], body_pitch_rate=%f, body_roll_rate=%f, body_yaw_rate=%f\n", target.q[0], target.q[1], target.q[2], target.q[3],
							//target.body_pitch_rate, target.body_roll_rate, target.body_yaw_rate);
						break;
					case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:			
						mavlink_global_position_int_t global;
						//mavlink_msg_global_position_int_decode(&msg, &global);
						//EventTrace(PProgram, 0, "MAVLINK_MSG_ID_GLOBAL_POSITION_INT: lat=%f, lon=%f, alt=%f\n", (float)global.lat / 1E7, (float)global.lon / 1E7, (float)global.alt / 1E3);
						//p_mavlink_msg_global_position_int_decode(&msg, &pMessage_global_position);
						//POrbSendToMaster(Topics_global_position_topic, P_EVENT_global_position, pMessage_global_position);
						break;
					case MAVLINK_MSG_ID_GPS_RAW_INT:
						mavlink_gps_raw_int_t peek;
						//mavlink_msg_gps_raw_int_decode(&msg, &peek);
						//printf("MAVLINK_MSG_ID_GPS_RAW_INT: satellites=%d, fix_type=%d, eph=%d\n", peek.satellites_visible, peek.fix_type, peek.eph);
						//p_mavlink_msg_gps_raw_int_decode(&msg, &pMessage_gps_raw);
						//POrbSendToMaster(Topics_gps_raw_int_topic, P_EVENT_gps_raw_int, pMessage_gps_raw);
						break;
					case MAVLINK_MSG_ID_GPS_STATUS:
						mavlink_gps_status_t gpsstatus;
						//mavlink_msg_gps_status_decode(&msg, &gpsstatus);
						//printf("MAVLINK_MSG_ID_GPS_STATUS: satellites=%d\n", gpsstatus.satellites_visible);
						//p_mavlink_msg_gps_status_decode(&msg, &pMessage_gps_status);
						//POrbSendToMaster(Topics_gps_status_topic, P_EVENT_gps_status, pMessage_gps_status);
						break;
					case MAVLINK_MSG_ID_BATTERY_STATUS:					
						mavlink_battery_status_t batt;
						//mavlink_msg_battery_status_decode(&msg, &batt);
						//EventTrace(PProgram, 0, "MAVLINK_MSG_ID_BATTERY_STATUS: battery_remaining=%d\n", batt.battery_remaining);
						//p_mavlink_msg_battery_status_decode(&msg, &pMessage_battery_status);
						//POrbSendToMaster(Topics_battery_status_topic, P_EVENT_battery_status, pMessage_battery_status);
						break;
					case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
						mavlink_local_position_ned_t local_pos;
						//mavlink_msg_local_position_ned_decode(&msg, &local_pos);
						//EventTrace(PProgram, 0, "MAVLINK_MSG_ID_LOCAL_POSITION_NED: x=%f, y=%f, z=%f\n", local_pos.x, local_pos.y, local_pos.z);
						//p_mavlink_msg_local_position_ned_decode(&msg, &pMessage_local_position_ned);
						//{
							// reverse the z units so positive numbers go upwards.
						//	void* zAxis = PrtTupleGetNC(pMessage_local_position_ned, 3);
						//	float zValue = PrtGetFloat32(zAxis);
						//	PrtSetFloat32(zAxis, -zValue);
						//}
						//POrbSendToMaster(Topics_local_position_topic, P_EVENT_local_position, pMessage_local_position_ned);
						break;
					case MAVLINK_MSG_ID_COMMAND_ACK:
						mavlink_command_ack_t ack;
						//mavlink_msg_command_ack_decode(&msg, &ack);
						//EventTrace(PProgram, 0, "Received command ack %d for command %d\n", ack.result, ack.command);
						//p_mavlink_msg_command_ack_decode(&msg, &pMessage_command_ack);
						//POrbSendToMaster(Topics_command_ack_topic, P_EVENT_command_ack, pMessage_command_ack);
						break;
					case MAVLINK_MSG_ID_EXTENDED_SYS_STATE:
						mavlink_extended_sys_state_t ext;
						//mavlink_msg_extended_sys_state_decode(&msg, &ext);
						//p_mavlink_msg_extended_sys_state_decode(&msg, &pMessage_extended_sys_state);
						//POrbSendToMaster(Topics_extended_sys_state_topic, P_EVENT_extended_sys_state, pMessage_extended_sys_state);
						break;
					case MAVLINK_MSG_ID_STATUSTEXT:
						mavlink_statustext_t stext;
						//mavlink_msg_statustext_decode(&msg, &stext);
						printf("MAVLINK_MSG_ID_STATUSTEXT: severity=%d, text=%s\n", (int)stext.severity, &stext.text[0]);
						break;
					}

			}
		}
	}

	//free all the prt values
	/*if (pMessage_heartbeat != nullptr) PrtFreeValue(pMessage_heartbeat);
	if (pMessage_global_position != nullptr) PrtFreeValue(pMessage_global_position);
	if (pMessage_attitute != nullptr) PrtFreeValue(pMessage_attitute);
	if (pMessage_battery_status != nullptr) PrtFreeValue(pMessage_battery_status);
	if (pMessage_local_position_ned != nullptr) PrtFreeValue(pMessage_local_position_ned);
	if (pMessage_command_ack != nullptr) PrtFreeValue(pMessage_command_ack);
	if (pMessage_gps_status != nullptr)  PrtFreeValue(pMessage_gps_status);
	if (pMessage_gps_raw != nullptr) PrtFreeValue(pMessage_gps_raw);
	if (pMessage_extended_sys_state != nullptr) PrtFreeValue(pMessage_extended_sys_state);*/
	return 0;
}


