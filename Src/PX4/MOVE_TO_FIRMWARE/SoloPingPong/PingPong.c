
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include "PrtExecution.h"
#include "test.h"
#include "Prt.h"
#include <time.h>
#include <signal.h>
#include <execinfo.h>
#include <stdlib.h>

/* Global variables */
PRT_PROCESS* ContainerProcess = NULL;
PRT_INT64 sendMessageSeqNumber = 0;
long steps = 0;
long intervalSteps = 0;
pthread_t machineThread = 0;
int32_t intervalStart = 0;
int32_t intervalLength = (1 * 60 * 1000); // 1 minute in milliseconds.
struct timespec start;
#define STACKSIZE 4000000 

int32_t getMilliseconds()
{
    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);
    
    int32_t totalSeconds = tm.tv_sec - start.tv_sec;
    int32_t totalNanoseconds = tm.tv_nsec - start.tv_nsec;
    if (totalNanoseconds < 0) {
      totalNanoseconds += 1000000000;
      totalSeconds--;
    }
    return (totalSeconds * 1000) + (totalNanoseconds / 1000000);
}

void handler(int sig) {
  #define SIZE 100
  void *buffer[SIZE];
  char **strings;
  int nptrs;

  // get void*'s for all entries on the stack
  nptrs = backtrace(buffer, SIZE);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d, stacksize=%d\n", sig, nptrs);
  strings = backtrace_symbols(buffer, nptrs);

  if (strings == NULL) {
    perror("no symbols found");
    exit(EXIT_FAILURE);
  }
  
  for (int j = 0; j < nptrs; j++) {
    printf("%s\n", strings[j]);    
  }

  free(strings);

  exit(1);
}


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

static void PrintReport(void)
{
    int32_t milliseconds = getMilliseconds();
    int32_t millisecondsInterval = milliseconds - intervalStart;

    printf("%ld,%d,%ld,%d\n", steps, milliseconds, intervalSteps, millisecondsInterval);
}

static void PrintHeader(void)
{
    printf("TotalSteps,TotalMs,IntervalSteps,IntervalMs\n");
}


static void LogHandler(PRT_STEP step, PRT_MACHINEINST *context)
{
    //PrtPrintStep(step, context);
    //usleep(1000);
}

static void CountSteps(void)
{
    steps++;
    intervalSteps++;

    int32_t now = getMilliseconds();
    int32_t milliseconds = now - intervalStart;
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
    printf("PingPong thread starting...\n");

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

    intervalStart = getMilliseconds();
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

    int32_t milliseconds = getMilliseconds();

    printf("PingPong ran %ld steps in %d ms\n", steps, milliseconds);

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
    size_t ss;

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

    status = pthread_attr_getstacksize(&attr, &ss);
    if (status != 0)
    {
        printf("pingpong: pthread_attr_getstacksize failed, status=%d\n", status);
        goto cleanup;
    }

    //sparam.sched_priority = priority;
    //status = pthread_attr_setschedparam(&attr,&sparam);
    //if (status != OK)
    //{
    //    printf("pingpong: pthread_attr_setschedparam failed, status=%d\n", status);
    //    goto cleanup;
    //}

    status = pthread_create(&machineThread, &attr, machine_thread, arg);
    if (status != 0)
    {
        printf("pingpong: pthread_create failed, status=%d\n", status);
    }

cleanup:
    return;
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, handler);   // so we print stack trace on crashes.

    // get start time.
    clock_gettime(CLOCK_REALTIME, &start);

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
        int32_t milliseconds = getMilliseconds();
        printf("PingPong is running, so far %ld steps in %d ms\n", steps, milliseconds);
        return 0;
    }

    StartPingPong(arg);

    for (int i = 0; i < 10; i++) {
      uint32_t now = getMilliseconds();
      sleep(60);
      now = getMilliseconds(); 
    }

    return 0;
}
