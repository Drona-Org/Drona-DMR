/****************************************************************************
 *
 *   Copyright (c) Microsoft Corporation. All rights reserved.
 *
 ****************************************************************************/

/**
 * @file px4_pingpong.c
 * Minimal application P example for PX4 
 *
 */

#include <nuttx/config.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <uORB/uORB.h>
#include <sched.h>
#include <nuttx/clock.h>
#include <nuttx/wqueue.h>

#include "PrtExecution.h"
#include "test.h"
#include "Prt.h"
#include "ostest.h"

/* Global variables */
PRT_PROCESS* ContainerProcess = NULL;
PRT_INT64 sendMessageSeqNumber = 0;
long steps = 0;
long intervalSteps = 0;
pthread_t machineThread = 0;
int32_t start = 0;
int32_t intervalStart = 0;
int32_t intervalLength = (1 * 60 * 1000); // 15 minutes in milliseconds.

#include <systemlib/cpuload.h>
#include <systemlib/printload.h>
#include <drivers/drv_hrt.h>

extern struct system_load_s system_load;

/* the Stubs */


typedef struct ClientContext {
    PRT_VALUE *client;
} ClientContext;

typedef struct ServerContext {
    PRT_VALUE *client;
} ServerContext;

void P_CTOR_Client_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    ClientContext *clientContext = (ClientContext *)PrtMalloc(sizeof(ClientContext));
    clientContext->client = PrtCloneValue(value);
    context->extContext = clientContext;
}

void P_DTOR_Client_IMPL(PRT_MACHINEINST *context)
{
    ClientContext *clientContext = (ClientContext *)context->extContext;
    PrtFreeValue(clientContext->client);
    PrtFree(clientContext);
}


/**
* The main function performs the following steps
* 1) If the createMain option is true then it create the main machine.
* 2) If the createMain option is false then it creates the Container machine.
* 3) It creates a RPC server to listen for messages.

Also note that the machine hosting the main machine does not host container machine.

**/

static void ErrorHandler(PRT_STATUS status, PRT_MACHINEINST *ptr)
{
    printf("Error: %d\n", (int)status );
}

static uint64_t lastCpuTime = 0;

static uint64_t GetMyCpuUsage(void)
{
    uint64_t previous = lastCpuTime;
    uint64_t current = system_load.tasks[machineThread].total_runtime;
    uint64_t result = 0;
    if (previous != 0 && current > previous)
    {
        result = current - previous;
    }
    else
    {
        // initial state or long integer might have wrapped around...
    }
    lastCpuTime = current;
    return result;
}

static void PrintReport(void)
{
    int32_t elapsed = clock_systimer() - start;
    int32_t milliseconds = elapsed / (TICK_PER_SEC / 1000);

    int32_t elapsedInterval = clock_systimer() - intervalStart;
    int32_t millisecondsInterval = elapsedInterval / (TICK_PER_SEC / 1000);

    struct mallinfo mem = mallinfo();

    uint64_t usage = GetMyCpuUsage();

    printf("PingPong, %d, %d, %d, %d, %d, %d, %d, %d, %ld\n", steps, milliseconds, intervalSteps, millisecondsInterval,
                    mem.arena, mem.uordblks, mem.fordblks, mem.mxordblk, usage);
}

static void PrintHeader(void)
{
    printf("App,Steps,Ms,IntervalSteps,IntervalMs,total,used,free,largest,CpuTicks\n");
}


static void LogHandler(PRT_STEP step, PRT_MACHINEINST *context)
{
    //PrtPrintStep(step, context);
    //usleep(1000);
}

/*
static void UnitTestTypes(void)
{
    int i = 0;
    PRT_TYPE* test;

    for (i = 0; i < 12; i++) {
        test = PrtMkPrimitiveType(i);
        if (test == NULL)
        {
            printf("PingPong creating type %d failed\n", i);
        }
        else
        {
            printf("PingPong creating type %d succeeded\n", i);
            PrtFree(test);
        }
    }
}
*/

static void CountSteps(void)
{
    steps++;
    intervalSteps++;

    int32_t now = clock_systimer();
    int32_t elapsed = now - intervalStart;
    int32_t milliseconds = elapsed / (TICK_PER_SEC / 1000);
    if (milliseconds > intervalLength)
    {
        PrintReport();
        intervalStart = now;
        intervalSteps = 0;
    }

}

static void *machine_thread(void *arg)
{
    int maxSteps = 0;
    printf("PingPong starting...\n");

    lastCpuTime = 0;

    PrintHeader();

    if (arg != NULL)
    {
        char* ptr = (char*)arg;
        maxSteps = atoi(ptr);
    }

    PRT_GUID processGuid;
    processGuid.data1 = 1;
    processGuid.data2 = 1;
    processGuid.data3 = 0;
    processGuid.data4 = 0;
    ContainerProcess = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, LogHandler);

    PrtSetSchedulingPolicy(ContainerProcess, PRT_SCHEDULINGPOLICY_COOPERATIVE);

    //create main machine
    PRT_VALUE* payload = PrtMkNullValue();
    PrtMkMachine(ContainerProcess, _P_MACHINE_MAIN, payload);
    PrtFreeValue(payload);

    start = clock_systimer();
    intervalStart = start;
    steps = 0;
    intervalSteps = 0;

    // push the state machines while yielding the CPU to other higher priority tasks.
    PRT_PROCESS_PRIV* privateProcess = (PRT_PROCESS_PRIV*)ContainerProcess;
    while (privateProcess->terminating == PRT_FALSE && (maxSteps == 0 || steps < maxSteps))
    {
        PRT_STEP_RESULT result = PrtStepProcess(ContainerProcess);
        switch (result) {
        case PRT_STEP_TERMINATING:
            break;
        case PRT_STEP_IDLE:
            PrtWaitForWork(ContainerProcess);
            break;
        case PRT_STEP_MORE:
            PrtYieldThread();
            break;
        }
        CountSteps();
    }

    int32_t elapsed = clock_systimer() - start;
    int32_t milliseconds = elapsed / (TICK_PER_SEC / 1000);

    printf("PingPong ran %d steps in %d ms\n", steps, milliseconds);

    if (maxSteps != 0)
    {
        // cleanup the memory for the process
        PrtStopProcess(ContainerProcess);
        ContainerProcess = NULL;
    }
    return NULL;
}

static void StartPingPong(void *arg)
{
    pthread_attr_t attr;
    struct sched_param sparam;
    int priority;
    int status;

    // start the thread that runs the state machine.
    status = pthread_attr_init(&attr);
    priority = sched_get_priority_min(SCHED_FIFO);
    if (status != 0)
    {
        printf("pingpong: pthread_attr_init failed, status=%d\n", status);
        goto cleanup;
    }

    status = pthread_attr_setstacksize(&attr, STACKSIZE);
    if (status != 0)
    {
        printf("pingpong: pthread_attr_setstacksize failed, status=%d\n", status);
        goto cleanup;
    }

    sparam.sched_priority = priority;
    status = pthread_attr_setschedparam(&attr,&sparam);
    if (status != OK)
    {
        printf("pingpong: pthread_attr_setschedparam failed, status=%d\n", status);
        goto cleanup;
    }

    status = pthread_create(&machineThread, &attr, machine_thread, (pthread_addr_t)arg);
    if (status != 0)
    {
        printf("pingpong: pthread_create failed, status=%d\n", status);
    }

cleanup:
    printf("pingpong: returning\n");
}

struct work_s _work;

__EXPORT int pingpong_main(int argc, char *argv[]);

int pingpong_main(int argc, char *argv[])
{
    char* arg = NULL;
    if (argc >= 1)
    {
        arg = argv[1];
        if (arg != NULL)
        {
            // make a copy, because nuttxshell will delete this memory as soon as we return
            if (strcmp(arg, "stop") == 0 && ContainerProcess != NULL)
            {
                PrtStopProcess(ContainerProcess);
                ContainerProcess = NULL;
                return 0;
            }
            else
            {
                int len = strlen(arg);
                if (len > 0)
                {
                    char* copy = malloc(len+1);
                    strcpy(copy, arg);
                    arg = copy;
                } else {
                    arg = NULL;
                }
            }
        }
    }

    if (ContainerProcess != NULL)
    {
        int32_t elapsed = clock_systimer() - start;
        int32_t milliseconds = elapsed / (TICK_PER_SEC / 1000);
        printf("PingPong is running, so far %d steps in %d ms\n", steps, milliseconds);
        return 0;
    }

    // start the pingpong thread from the worker thread and not from
    // this thread.  This way we allow NuttxShell to continue processing
    // input (since NuttxShell has a waitpid() call waiting for this task to complete
    // so if we start the pingpong thread then this task will not be considered complete
    // even if this method returns because it still has a child thread that is alive
    // running the state machine.
    steps = 0;
    work_queue(LPWORK, &_work, (worker_t)StartPingPong, arg, 1);
    return 0;
}
