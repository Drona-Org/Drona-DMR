#ifndef  _PORB_MAVLINK_HELPERS_H_
#define  _PORB_MAVLINK_HELPERS_H_

#include "Float32.h"
#include "Port.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Port.h"
#define MAVLINK_PACKED

/*
POrb Mavlink Class
*/
class POrbMavlink {
public:
	//initialize the port we use for the mavlink connection
	static bool Initialize(Port* portToUse);
	static DWORD DispatchMavlinkMessages(LPVOID arg);
	static VOID POrbSendToMaster(PRT_INT32 topic, PRT_INT32 px4_event, PRT_VALUE* px4_payload);
	static bool WaitForHeartbeat();

	// internal use only
	static Port* port;
	static PRT_MACHINEINST* POrbMasterMachine;
	static PRT_MACHINEINST* PX4ModelMachine;
	static int heartbeats;
	static bool ready;
};

#endif
