// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrtDist.h"
#include "test.h"
#include "PrtExecution.h"
#include <stdio.h>

/* Global variables */
PRT_PROCESS* ContainerProcess = NULL;
struct ClusterConfig ClusterConfiguration;
PRT_INT64 sendMessageSeqNumber = 0;
BOOL running = FALSE;

/* the Stubs */

typedef struct TestDriverContext {
    PRT_VALUE *client;
} TestDriverContext;

typedef struct Mpu6000DriverContext {
    PRT_VALUE *client;
} Mpu6000DriverContext;

typedef struct Mpu6000SensorContext {
    PRT_VALUE *client;
} Mpu6000SensorContext;

typedef struct Mpu6000ClientContext {
    PRT_VALUE *client;
} Mpu6000ClientContext;

void P_CTOR_MPU6000Client_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_MPU6000Client_IMPL\n");
    Mpu6000ClientContext *clientContext = (Mpu6000ClientContext *)PrtCalloc(1, sizeof(Mpu6000ClientContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}

void P_DTOR_MPU6000Client_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_MPU6000Client_IMPL\n");
    Mpu6000ClientContext *clientContext = (Mpu6000ClientContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_CTOR_TestDriver_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_TestDriver_IMPL\n");
    TestDriverContext *clientContext = (TestDriverContext *)PrtCalloc(1, sizeof(TestDriverContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}

void P_DTOR_TestDriver_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_TestDriver_IMPL\n");
    TestDriverContext *clientContext = (TestDriverContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_DTOR_MPU6000Driver_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_GpsSensor_IMPL\n");
    Mpu6000DriverContext *clientContext = (Mpu6000DriverContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_CTOR_MPU6000Driver_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_DTOR_MPU6000Driver_IMPL\n");
    Mpu6000DriverContext *clientContext = (Mpu6000DriverContext *)PrtCalloc(1, sizeof(Mpu6000DriverContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}

void P_DTOR_MPU6000Sensor_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_MPU6000Sensor_IMPL\n");
    Mpu6000SensorContext *clientContext = (Mpu6000SensorContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}

void P_CTOR_MPU6000Sensor_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_MPU6000Sensor_IMPL\n");
    Mpu6000SensorContext *clientContext = (Mpu6000SensorContext *)PrtCalloc(1, sizeof(Mpu6000SensorContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}


void LogEvent(PRT_MACHINEINST *machine, PRT_VALUE *evnt, PRT_VALUE *payload)
{
    char *buffer = PrtCalloc(1000, sizeof(char));
    PRT_MACHINEINST_PRIV * c = (PRT_MACHINEINST_PRIV *)machine;
    PRT_STRING machineName = c->process->program->machines[c->instanceOf]->name;
    PRT_UINT32 machineId = c->id->valueUnion.mid->machineId;
    PRT_UINT32 eventIndex = evnt->valueUnion.ev;
    PRT_STRING eventName;
    eventName = c->process->program->events[eventIndex].name;

    sprintf_s(buffer, 1000, "<EnqueueLog> Enqueued event %s with payload %d on Machine %s\n",
        eventName, (int)payload->discriminator, machineName);

    OutputDebugStringA(buffer);

    PrtFree(buffer);
}

void P_SEND_RemoteControl_IMPL(PRT_MACHINEINST *machine, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{
    LogEvent(machine, evnt, payload);
}

PRT_VALUE* driverMachine = NULL;
void P_SEND_MPU6000Sensor_IMPL(PRT_MACHINEINST *sender, PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{
    switch (evnt->valueUnion.ev)
    {
    case P_EVENT_ATTACH_DRIVER:
        driverMachine = PrtCloneValue(payload);
        break;
    }
}

PRT_VALUE *P_FUN_MPU6000Driver_CheckAccelLimits_IMPL(PRT_MACHINEINST *context)
{
    // todo: this is where we do some floating point path on behalf of the p program since p doesn't support float.
    return PrtMkNullValue();
}

PRT_VALUE *P_FUN_MPU6000Driver_CheckGyroLimits_IMPL(PRT_MACHINEINST *context)
{
    // todo: this is where we do some floating point path on behalf of the p program since p doesn't support float.
    return PrtMkNullValue();
}

PRT_VALUE *P_FUN_MPU6000Driver_GetMeasurement_IMPL(PRT_MACHINEINST *context)
{
    // todo: this is where we do some floating point path on behalf of the p program since p doesn't support float.
    return PrtMkNullValue();
}

PRT_VALUE *P_FUN_MPU6000Driver_ReadRegister_IMPL(PRT_MACHINEINST *context)
{
    // todo: this is where we do some floating point path on behalf of the p program since p doesn't support float.
    return PrtMkNullValue();
}

PRT_VALUE *P_FUN_MPU6000Driver_WriteRegister_IMPL(PRT_MACHINEINST *context)
{
    // todo: this is where we do some floating point path on behalf of the p program since p doesn't support float.
    return PrtMkNullValue();
}

void P_SEND_MPU6000Client_IMPL(PRT_MACHINEINST *sender, PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{

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

void LogHandler(PRT_STEP step, PRT_MACHINEINST *context, PRT_MACHINEINST *sender, PRT_VALUE* event, PRT_VALUE* payload)
{
    PRT_MACHINEINST_PRIV *c = (PRT_MACHINEINST_PRIV*)context;
    PrtLockMutex(((PRT_PROCESS_PRIV*)ContainerProcess)->processLock);

    PRT_STRING log = NULL;
    if (step == PRT_STEP_COUNT) //special logging
    {
    }
    else
    {
        log = PrtToStringStep(step, context, sender, event, payload);
        OutputDebugStringA(log);
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
    PRT_STRING MachineName = context->process->program->machines[context->instanceOf]->name;
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

PRT_MACHINEINST *client = NULL;

void RunSimulation()
{
    PRT_GUID processGuid;
    processGuid.data1 = 1;
    processGuid.data2 = 1; //nodeId
    processGuid.data3 = 0;
    processGuid.data4 = 0;
    ContainerProcess = PrtStartProcess(processGuid, &P_GEND_PROGRAM, PrtDistWinRTExceptionHandler, LogHandler);

    //create remote control model 
    PRT_VALUE* payload = PrtMkNullValue();
    PRT_MACHINEINST *sensor = PrtMkMachine(ContainerProcess, P_MACHINE_MPU6000Sensor, payload);
    PrtFreeValue(payload);

    //create the client model 
    payload = PrtMkNullValue();
    client = PrtMkMachine(ContainerProcess, P_MACHINE_MPU6000Client, payload);
    PrtFreeValue(payload);

    //create the flight controller machine passing the model as parameter.
    PRT_TYPE* machineType = PrtMkPrimitiveType(PRT_KIND_MACHINE);

    PRT_TYPE* pairType = PrtMkTupType(2);
    pairType->typeUnion.tuple->fieldTypes[0] = machineType;
    pairType->typeUnion.tuple->fieldTypes[1] = machineType;
    PRT_VALUE* tuple = PrtMkDefaultValue(pairType);
    PrtTupleSet(tuple, 0, sensor->id);
    PrtTupleSet(tuple, 1, client->id);
    
    PRT_MACHINEINST *driver = PrtMkMachine(ContainerProcess, P_MACHINE_MPU6000Driver, tuple);

    running = TRUE;

    // Wait for the timer.
    while (running) {
        SleepEx(1000, TRUE);
    }

    // todo: free everything..
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
        if (temp->instanceOf == machineId)
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


    PrtSend(client, machine, ev, value, PRT_FALSE);
    PrtFreeValue(ev);
}