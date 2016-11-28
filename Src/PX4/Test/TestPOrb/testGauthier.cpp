#include "stdafx.h"
#include "TestPOrb.h"
#include "Commands.h"
#include "UdpSocketPort.h"
#include "SerialPort.h"
#include "PTrace.h"

PRT_PROCESS* MAIN_APPLICATION_PROCESS = NULL;
bool trace = false;


int main(int argc, char *argv[])
{
	EventLog log("trace.txt");

	if (!ParseCommandLine(argc, argv))
	{
		PrintUsage();
		return 1;
	}
	Port* port = OpenPort(isUdp, portName);
	if (port == NULL) {
		return 1;
	}
	POrbMavlink::Initialize(port);

	//remove all
	//-----------------------------
	PrtUpdatePrintFn(&MyPrint);

	PRT_GUID processGuid;
	PRT_VALUE *payload;
	processGuid.data1 = 1;
	processGuid.data2 = 0;
	processGuid.data3 = 0;
	processGuid.data4 = 0;
	MAIN_APPLICATION_PROCESS = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, Log);
	payload = PrtMkNullValue();

	//create the main machine
	PrtMkMachine(MAIN_APPLICATION_PROCESS, P_MACHINE_POrbMachine, payload);
	PrtFreeValue(payload);

	// todo: when to exit?
	while (true)
	{
		SleepEx(1000, TRUE);
	}

	PrtStopProcess(MAIN_APPLICATION_PROCESS);
}
