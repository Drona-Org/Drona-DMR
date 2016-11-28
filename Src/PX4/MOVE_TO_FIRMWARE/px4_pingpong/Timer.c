#include "test.h"
#include <time.h>
#include <stdio.h>

//bool inStart = FALSE;
//
//typedef struct TimerContext {
//    PRT_VALUE *client;
//    struct itimerspec  timer;
//    timer_t timerid;
//} TimerContext;

//todo: this is different in nuttx
//void Callback(void FAR * arg, uint32_t dwTimerLowValue, uint32_t dwTimerHighValue)
//{
//    inStart = FALSE;
//    PRT_MACHINEINST *context = (PRT_MACHINEINST *)arg;
//    TimerContext *timerContext = (TimerContext *)context->extContext;
//    PRT_VALUE *ev = PrtMkEventValue(P_EVENT_TIMEOUT);
//    PrtSend(PrtGetMachine(context->process, timerContext->client), ev, context->id);
//    PrtFreeValue(ev);
//}
//
//void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context)
//{
//    printf("Entering P_DTOR_Timer_IMPL\n");
//    TimerContext *timerContext;
//    timerContext = (TimerContext *)context->extContext;
//    PrtFreeValue(timerContext->client);
//    timer_delete(timerContext->timerid);
//    PrtFree(timerContext);
//}
//
//void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
//{
//    printf("Entering P_CTOR_Timer_IMPL\n");
//    TimerContext *timerContext = (TimerContext *)PrtMalloc(sizeof(TimerContext));
//    timerContext->client = PrtCloneValue(value);
//    //status = timer_create(CLOCK_REALTIME, &notify, &timerContext->timerid);
//    //PrtAssert(timerContext->timerid != NULL, "CreateWaitableTimer failed");
//    context->extContext = timerContext;
//}
//
//void P_SEND_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload)
//{
//    printf("Entering P_SEND_Timer_IMPL\n");
//    PRT_VALUE *ev;
//    bool success = true;
//    TimerContext *timerContext = (TimerContext *)context->extContext;
//    if (!inStart && evnt->valueUnion.ev == P_EVENT_START) {
//        printf("Timer received START\n");
//        // todo: timers on nuttx are more complicated to setup, have to use interupts and stuff...
//        //LARGE_INTEGER liDueTime;
//        //liDueTime.QuadPart = -10000 * payload->valueUnion.nt;
//        //success = SetWaitableTimer(timerContext->timer, &liDueTime, 0, Callback, context, FALSE);
//        inStart = TRUE;
//        //PrtAssert(success, "SetWaitableTimer failed");
//    }
//    else if (evnt->valueUnion.ev == P_EVENT_CANCEL) {
//        printf("Timer received CANCEL\n");
//        inStart = FALSE;
//        //success = CancelWaitableTimer(timerContext->timer);
//        if (success) {
//            ev = PrtMkEventValue(P_EVENT_CANCEL_SUCCESS);
//            PrtSend(PrtGetMachine(context->process, timerContext->client), ev, context->id);
//        }
//        else {
//            ev = PrtMkEventValue(P_EVENT_CANCEL_FAILURE);
//            PrtSend(PrtGetMachine(context->process, timerContext->client), ev, context->id);
//        }
//        PrtFreeValue(ev);
//    }
//    else {
//        PrtAssert(FALSE, "Illegal event");
//    }
//}
