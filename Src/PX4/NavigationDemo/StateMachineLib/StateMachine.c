// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrtDist.h"
#include "Test.h"
#include "PrtExecution.h"
#include <stdio.h>
#include <StateMachine.h>

/* Global variables */
PRT_PROCESS* ContainerProcess = NULL;
struct ClusterConfig ClusterConfiguration;
PRT_INT64 sendMessageSeqNumber = 0;
BOOL running = FALSE;
static LogHandler s_logger = NULL;

/* the Stubs */

typedef struct GpsContext {
    PRT_VALUE *client;
} GpsContext;

typedef struct AltimeterContext {
    PRT_VALUE *client;
} AltimeterContext;

typedef struct FlightControllerContext {
    PRT_VALUE *client;
} FlightControllerContext;

typedef struct RemoteControlContext {
    PRT_VALUE *client;
} RemoteControlContext;

void P_CTOR_GpsSensor_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_GpsSensor_IMPL\n");
    GpsContext *clientContext = (GpsContext *)PrtCalloc(1, sizeof(GpsContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}

void P_DTOR_GpsSensor_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_GpsSensor_IMPL\n");
    GpsContext *clientContext = (GpsContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_CTOR_Altimeter_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering _P_CTOR_Altimeter_IMPL\n");
    AltimeterContext *clientContext = (AltimeterContext *)PrtCalloc(1, sizeof(AltimeterContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}
void P_DTOR_Altimeter_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering _P_DTOR_Altimeter_IMPL\n");
    AltimeterContext *clientContext = (AltimeterContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_CTOR_FlightController_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_FlightController_IMPL\n");
    FlightControllerContext *serverContext = (FlightControllerContext *)PrtCalloc(1, sizeof(FlightControllerContext));
    serverContext->client = PrtCloneValue(value);
    context->extContext = serverContext;
}

void P_DTOR_FlightController_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_FlightController_IMPL\n");
    FlightControllerContext *serverContext = (FlightControllerContext *)context->extContext;
    PrtFreeValue(serverContext->client);
    PrtFree(serverContext);
}

void P_CTOR_RemoteControl_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_RemoteControl_IMPL\n");
    RemoteControlContext *remoteContext = (RemoteControlContext *)PrtCalloc(1, sizeof(RemoteControlContext));
    remoteContext->client = PrtCloneValue(value);
    context->extContext = remoteContext;
}

void P_DTOR_RemoteControl_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_RemoteControl_IMPL\n");
    RemoteControlContext *remoteContext = (RemoteControlContext *)context->extContext;
    PrtFreeValue(remoteContext->client);
    PrtFree(remoteContext);
}


void P_DTOR_dummy_IMPL(PRT_MACHINEINST *context)
{
}


void P_CTOR_dummy_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}

void LogEvent(PRT_MACHINEINST *machine, PRT_VALUE *evnt, PRT_VALUE *payload)
{
    char *buffer = PrtCalloc(1000, sizeof(char));
    PRT_MACHINEINST_PRIV * c = (PRT_MACHINEINST_PRIV *)machine;
    PRT_STRING machineName = machine->isModel ? c->process->program->modelImpls[c->instanceOf].name : c->process->program->machines[c->instanceOf].name;
    PRT_UINT32 machineId = c->id->valueUnion.mid->machineId;
    PRT_UINT32 eventIndex = evnt->valueUnion.ev;
    PRT_STRING eventName;
    eventName = c->process->program->events[eventIndex].name;

    sprintf_s(buffer, 1000, "<EnqueueLog> Enqueued event %s with payload %d on Machine %s\n",
        eventName, (int)payload->discriminator, machineName);

    OutputDebugStringA(buffer);

    PrtFree(buffer);
}

void P_SEND_RemoteControl_IMPL(PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{
    LogEvent(context, evnt, payload);
}

/**serverContext
* The main function performs the following steps
* 1) If the createMain option is true then it create the main machine.
* 2) If the createMain option is false then it creates the Container machine.
* 3) It creates a RPC server to listen for messages.

Also note that the machine hosting the main machine does not host container machine.

**/

int Init(PRT_CHAR* logPath)
{
    PrtOpenLogFile((PRT_CHAR*)logPath);
    return 0;
}

void MyLogHandler(PRT_STEP step, PRT_MACHINEINST *context, PRT_MACHINEINST *sender, PRT_VALUE *eventid, PRT_VALUE *payload)
{
    PRT_MACHINEINST_PRIV *c = (PRT_MACHINEINST_PRIV*)context;
    PrtLockMutex(((PRT_PROCESS_PRIV*)ContainerProcess)->processLock);

    PRT_STRING log = NULL;
    if (step == PRT_STEP_COUNT) //special logging
    {
    }
    else
    {
        log = PrtToStringStep(step, context, sender, eventid, payload);
        OutputDebugStringA(log);
        if (s_logger)
        {
            s_logger(log);
        }
    }
    PrtFree(log);
    PrtUnlockMutex(((PRT_PROCESS_PRIV*)ContainerProcess)->processLock);
}


void
PrtDistWinRTExceptionHandler(
    __in PRT_STATUS exception,
    __in void* vcontext
    )
{

    PRT_MACHINEINST *context = (PRT_MACHINEINST*)vcontext;
    PRT_STRING MachineName = context->process->program->machines[context->instanceOf].name;
    PRT_UINT32 MachineId = context->id->valueUnion.mid->machineId;

    PRT_MACHINEINST_PRIV *c = (PRT_MACHINEINST_PRIV*)vcontext;

    PrtLockMutex(((PRT_PROCESS_PRIV*)c->process)->processLock);

    PRT_CHAR log[MAX_LOG_SIZE];

    switch (exception)
    {
    case PRT_STATUS_EVENT_UNHANDLED:
        sprintf_s(log,
            MAX_LOG_SIZE,
            "<EXCEPTION> Machine %s(%d) : Unhandled Event Exception\n",
            MachineName,
            MachineId);
        break;
    case PRT_STATUS_EVENT_OVERFLOW:
        sprintf_s(log,
            MAX_LOG_SIZE,
            "<EXCEPTION> Machine %s(%d) : MaxInstance of Event Exceeded Exception\n",
            MachineName,
            MachineId);
        break;
    case PRT_STATUS_QUEUE_OVERFLOW:
        sprintf_s(log,
            MAX_LOG_SIZE,
            "<EXCEPTION> Queue Size Exceeded Max Limits in Machine %s(%d)\n",
            MachineName,
            MachineId);
        break;
    case PRT_STATUS_ILLEGAL_SEND:
        sprintf_s(log,
            MAX_LOG_SIZE,
            "<EXCEPTION> Machine %s(%d) : Illegal use of send for sending message across process (source and target machines are in different process) ",
            MachineName,
            MachineId);
        break;
    default:
        sprintf_s(log,
            MAX_LOG_SIZE,
            "<EXCEPTION> Machine %s(%d) : Unknown Exception\n",
            MachineName,
            MachineId);
        break;
    }

    PrtDistLog(log);

    PrtUnlockMutex(((PRT_PROCESS_PRIV*)c->process)->processLock);

    exit(-1);
}

PRT_MACHINEINST *remoteControl = NULL;

void RunSimulation(LogHandler handler)
{
    s_logger = handler;

    PRT_GUID processGuid;
    processGuid.data1 = 1;
    processGuid.data2 = 1; //nodeId
    processGuid.data3 = 0;
    processGuid.data4 = 0;
    ContainerProcess = PrtStartProcess(processGuid, &P_GEND_PROGRAM, PrtDistWinRTExceptionHandler, MyLogHandler);

    //create remote control model 
    PRT_VALUE* payload = PrtMkNullValue();
    remoteControl = PrtMkModel(ContainerProcess, P_MODEL_RemoteControl, payload);
    PrtFreeValue(payload);

    //create the flight controller machine passing the model as parameter.
    PRT_MACHINEINST *flightController = PrtMkMachine(ContainerProcess, P_MACHINE_FlightController, remoteControl->id);

    running = TRUE;

    // Wait for the timer.
    while (running) {
        SleepEx(1000, TRUE);
    }
}

void StopSimulation()
{
    running = FALSE;
}

PRT_VALUE* MakeBooleanValue(BOOL b)
{
    return PrtMkBoolValue(b ? PRT_TRUE : PRT_FALSE);
}

PRT_VALUE* MakeIntegerValue(int i)
{
    return PrtMkIntValue(i);
}

PRT_VALUE* MakeNullValue() {
    return PrtMkNullValue();
}

void RaiseEvent(int machineId, int eventId, PRT_VALUE* value)
{
    PRT_GUID processGuid;
    processGuid.data1 = 1;
    processGuid.data2 = 1; //nodeId
    processGuid.data3 = 0;
    processGuid.data4 = 0;

    if (machineId < 0 || machineId >= _P_MACHINES_COUNT)
    {
        PrtDistLog("Error: MachineId is out of range");
        return;
    }


    PRT_PROCESS_PRIV* privateProcess = (PRT_PROCESS_PRIV*)ContainerProcess;

    PRT_VALUE *ev = PrtMkEventValue(eventId);
    PRT_MACHINEINST* machine = NULL;

    // The internal machine id depends on the order in which the machines are created, it is not based on the enum values.
    for (PRT_UINT32 i = 0; i < privateProcess->numMachines; i++)
    {
        PRT_MACHINEINST* temp = privateProcess->machines[i];
        if (temp->instanceOf == machineId && !temp->isModel)
        {
            machine = temp;
            break;
        }
    }

    if (machine == NULL)
    {
        PrtDistLog("Error: Machine has not been created yet");
        return;
    }


    PrtSend(remoteControl, machine, ev, value, PRT_FALSE);
    PrtFreeValue(ev);
}