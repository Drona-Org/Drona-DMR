#ifndef  _PORB_MAVLINK_HELPERS_H_
#define  _PORB_MAVLINK_HELPERS_H_

//#include "Float32.h"
#include "float.h"
#include "Port.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Port.h"
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

	// internal use only
	static Port* port;
	static void* POrbMasterMachine;
	static void* PX4ModelMachine;
	static int heartbeats;
	static bool ready;
};

#endif
