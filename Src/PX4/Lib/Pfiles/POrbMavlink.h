#ifndef  _PORB_MAVLINK_HELPERS_H_
#define  _PORB_MAVLINK_HELPERS_H_

//#include "Float32.h"
#include "float.h"
//#include "Port.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "../Communication/Src/Port.h"
#define MAVLINK_PACKED

typedef unsigned long DWORD;
typedef void* LPVOID;
typedef void VOID;

/*
POrb Mavlink Class
*/
class POrbMavlink {
public:
	//initialize the port we use for the mavlink connection
	static bool Initialize(Port* portToUse);
	static DWORD DispatchMavlinkMessages(LPVOID arg);
	static VOID POrbSendToMaster(int *topic, int *px4_event, void* px4_payload);
	static bool WaitForHeartbeat();
	static void SendCommand(int cmdid, bool confirm, float a1, float a2, float a3, float a4, float a5, float a6, float a7);

	// internal use only
	static Port* port;
	static void* POrbMasterMachine;
	static void* PX4ModelMachine;
	static int heartbeats;
	static bool ready;
};

#endif
