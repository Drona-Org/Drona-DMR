#include "test.h"

BOOL inStart = FALSE;

typedef struct TimerContext {
    PRT_VALUE *client;
    HANDLE timer;
} TimerContext;

VOID CALLBACK Callback(LPVOID arg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
    inStart = FALSE;
    PRT_MACHINEINST *context = (PRT_MACHINEINST *)arg;
    TimerContext *timerContext = (TimerContext *)context->extContext;
    PRT_VALUE *ev = PrtMkEventValue(P_EVENT_TIMEOUT);
	// technically we need a model machine for the timer as the sender...
    PrtSend(context, PrtGetMachine(context->process, timerContext->client), ev, context->id, PRT_FALSE);
    PrtFreeValue(ev);
}

void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context)
{
    printf("Entering P_DTOR_Timer_IMPL\n");
    TimerContext *timerContext;
    timerContext = (TimerContext *)context->extContext;
    PrtFreeValue(timerContext->client);
    CloseHandle(timerContext->timer);
    free(timerContext);
}

void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
    printf("Entering P_CTOR_Timer_IMPL\n");
    TimerContext *timerContext = (TimerContext *)malloc(sizeof(TimerContext));
    timerContext->client = PrtCloneValue(value);
    timerContext->timer = CreateWaitableTimer(NULL, TRUE, NULL);
    PrtAssert(timerContext->timer != NULL, "CreateWaitableTimer failed");
    context->extContext = timerContext;
}

void P_SEND_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{
    printf("Entering P_SEND_Timer_IMPL\n");
    PRT_VALUE *ev;
    BOOL success;
    TimerContext *timerContext = (TimerContext *)context->extContext;
    if (!inStart && evnt->valueUnion.ev == P_EVENT_START) {
        printf("Timer received START\n");
        LARGE_INTEGER liDueTime;
        liDueTime.QuadPart = -10000 * payload->valueUnion.nt;
        success = SetWaitableTimer(timerContext->timer, &liDueTime, 0, Callback, context, FALSE);
        inStart = TRUE;
        PrtAssert(success, "SetWaitableTimer failed");
    }
    else if (evnt->valueUnion.ev == P_EVENT_CANCEL) {
        printf("Timer received CANCEL\n");
        inStart = FALSE;
        success = CancelWaitableTimer(timerContext->timer);
        if (success) {
            ev = PrtMkEventValue(P_EVENT_CANCEL_SUCCESS);
            PrtSend(context, PrtGetMachine(context->process, timerContext->client), ev, context->id, PRT_FALSE);
        }
        else {
            ev = PrtMkEventValue(P_EVENT_CANCEL_FAILURE);
            PrtSend(context, PrtGetMachine(context->process, timerContext->client), ev, context->id, PRT_FALSE);
        }
        PrtFreeValue(ev);
    }
    else {
        PrtAssert(FALSE, "Illegal event");
    }
}
