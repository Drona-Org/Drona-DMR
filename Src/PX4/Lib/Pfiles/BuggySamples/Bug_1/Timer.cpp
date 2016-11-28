#include "PFiles.h"
#include "EventTrace.h"
#include "PTrace.h"

typedef struct TimerContext {
	PRT_VALUE *client;
	HANDLE timer;
	BOOL started;	
} TimerContext;

char* GetMachineName(PRT_MACHINEINST *context)
{
	char* name = (context->isModel) ?
		context->process->program->modelImpls[context->instanceOf].name :
		context->process->program->machines[context->instanceOf].name;
	return name;
}

VOID CALLBACK Callback(LPVOID arg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	//printf("Entering Timer Callback\n");	
	PRT_MACHINEINST *context = (PRT_MACHINEINST *)arg;
	TimerContext *timerContext = (TimerContext *)context->extContext;

	//EventTrace(PProgram, 0, "Timer %d timed out in context %s\n", (int)timerContext->timer, GetMachineName(context));

	PRT_VALUE *ev = PrtMkEventValue(P_EVENT_timer_timeout);
	PRT_MACHINEINST* clientMachine = PrtGetMachine(context->process, timerContext->client);
	PrtSend(context, clientMachine, ev, context->id, PRT_FALSE);
	PrtFreeValue(ev);
}

void P_DTOR_TimerMachine_IMPL(PRT_MACHINEINST *context)
{
	TimerContext *timerContext;
	timerContext = (TimerContext *)context->extContext;
	
	//EventTrace(PProgram, 0, "Destroying timer %d in context %s\n", (int)timerContext->timer,  GetMachineName(context));

	PrtFreeValue(timerContext->client);
	CloseHandle(timerContext->timer);
	PrtFree(timerContext);
}

void P_CTOR_TimerMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
	TimerContext *timerContext = (TimerContext *)PrtMalloc(sizeof(TimerContext));
	timerContext->client = value;
	timerContext->started = FALSE;
	timerContext->timer = CreateWaitableTimer(NULL, TRUE, NULL);


	//EventTrace(PProgram, 0, "Creating timer %d in context %s\n", (int)timerContext->timer, GetMachineName(context));

	PrtAssert(timerContext->timer != NULL, "CreateWaitableTimer failed");
	context->extContext = timerContext;
}

void P_SEND_TimerMachine_IMPL(PRT_MACHINEINST *sender, PRT_MACHINEINST *receiver, PRT_VALUE *evnt, PRT_VALUE *payload, PRT_BOOLEAN doTransfer)
{
	PrtAssert(doTransfer == PRT_FALSE, "Ownership must stay with caller");
	//printf("Entering P_SEND_Timer_IMPL\n");
	PRT_VALUE *ev;
	BOOL success;
	TimerContext *timerContext = (TimerContext *)receiver->extContext;
	if (evnt->valueUnion.ev == P_EVENT_timer_start) {

		//EventTrace(PProgram, 0, "Timer %d started by %s\n", (int)timerContext->timer, GetMachineName(sender));

		if (!timerContext->started) {
			LARGE_INTEGER liDueTime;
			int timeout_value = PrtPrimGetInt(payload);
			liDueTime.QuadPart = -10000 * timeout_value;
			success = SetWaitableTimer(timerContext->timer, &liDueTime, 0, Callback, receiver, FALSE);
			timerContext->started = TRUE;
			PrtAssert(success, "SetWaitableTimer failed");
		}
		else
		{
			PrtAssert(FALSE, "Timer already started");
		}
	}
	else if (evnt->valueUnion.ev == P_EVENT_timer_cancel) {

		//EventTrace(PProgram, 0, "Timer %d cancelled by %s\n", timerContext->timer, GetMachineName(sender));

		timerContext->started = FALSE;
		success = CancelWaitableTimer(timerContext->timer);
		if (success) {
			ev = PrtMkEventValue(P_EVENT_timer_cancel_success);
			PrtSend(receiver, PrtGetMachine(receiver->process, timerContext->client), ev, receiver->id, PRT_FALSE);
		}
		else {
			ev = PrtMkEventValue(P_EVENT_timer_cancel_failure);
			PrtSend(receiver, PrtGetMachine(receiver->process, timerContext->client), ev, receiver->id, PRT_FALSE);
		}
		PrtFreeValue(ev);
	}
	else {
		PrtAssert(FALSE, "Unexpected event for timer");
	}
}
