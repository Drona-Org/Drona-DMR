// Test.cpp : Defines the entry point for the console application.
//

#include "PrtDist.h"
#include "test.h"
#include "Prt.h"
#include <stdio.h>

/* Global variables */
PRT_PROCESS* ContainerProcess;
struct ClusterConfig ClusterConfiguration;
PRT_INT64 sendMessageSeqNumber = 0;

/* the Stubs */

void P_CTOR_Main_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}

void P_DTOR_Main_IMPL(PRT_MACHINEINST *context)
{
}

void ErrorHandler(PRT_STATUS status, PRT_MACHINEINST *ptr)
{
	if (status == PRT_STATUS_ASSERT)
	{
		printf("exiting with PRT_STATUS_ASSERT (assertion failure)\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_OVERFLOW)
	{
		printf("exiting with PRT_STATUS_EVENT_OVERFLOW\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_UNHANDLED)
	{
		printf("exiting with PRT_STATUS_EVENT_UNHANDLED\n");
		exit(1);
	}
	else if (status == PRT_STATUS_QUEUE_OVERFLOW)
	{
		printf("exiting with PRT_STATUS_QUEUE_OVERFLOW \n");
		exit(1);
	}
	else if (status == PRT_STATUS_ILLEGAL_SEND)
	{
		printf("exiting with PRT_STATUS_ILLEGAL_SEND \n");
		exit(1);
	}
	else
	{
		printf("unexpected PRT_STATUS in ErrorHandler: %d\n", status);
		exit(2);
	}
}

static void LogHandler(PRT_STEP step, PRT_MACHINEINST *context, PRT_MACHINEINST *sender, PRT_VALUE* event, PRT_VALUE* payload)
{
	PrtPrintStep(step, context, sender, event, payload);
}

/**
* The main function performs the following steps
* 1) If the createMain option is true then it create the main machine.
* 2) If the createMain option is false then it creates the Container machine.
* 3) It creates a RPC server to listen for messages.

Also note that the machine hosting the main machine does not host container machine.

**/

int main(int argc, char *argv[])
{
	PRT_GUID processGuid;
	processGuid.data1 = 1;
	processGuid.data2 = 1; //nodeId
	processGuid.data3 = 0;
	processGuid.data4 = 0;
	ContainerProcess = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, LogHandler);

	//create main machine 
	PRT_VALUE* payload = PrtMkNullValue();
	PrtMkMachine(ContainerProcess, P_MACHINE_Main, payload);
	PrtFreeValue(payload);

	// Wait for the timer.
	while (1) {
		SleepEx(1000, TRUE);
	}

	return 0;

}
