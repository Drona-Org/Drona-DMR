#include "TestDriver.h"

typedef struct TimerContext {
	PRT_VALUE *client;
	HANDLE timer;
	BOOL started;
} TimerContext;

char* GetMachineName(PRT_MACHINEINST *context)
{
	char* name = context->process->program->machines[context->instanceOf]->name;
	return name;
}


PRT_VALUE *P_FUN_StartTimer_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	LARGE_INTEGER liDueTime;
	PRT_VALUE *p_tmp_ret = NULL;
	BOOL success;
	PRT_FUNSTACK_INFO p_tmp_frame;

	// pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

	PRT_VALUE* timerMachineId = p_tmp_frame.locals[0];
	PRT_MACHINEINST* timerMachine = PrtGetMachine(context->process, timerMachineId);
	TimerContext *timerContext = (TimerContext *)timerMachine->extContext;

	int timeout_value = p_tmp_frame.locals[1]->valueUnion.nt;
	
	Sleep(timeout_value);

	PRT_VALUE *ev = PrtMkEventValue(P_EVENT_TIMEOUT);
	PRT_MACHINEINST* clientMachine = PrtGetMachine(context->process, timerContext->client);
	PrtSend(context, clientMachine, ev, context->id, PRT_FALSE);
	PrtFreeValue(ev);

	// free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return NULL;
}

PRT_VALUE *P_FUN_CancelTimer_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	LARGE_INTEGER liDueTime;
	PRT_VALUE *p_tmp_ret = NULL;
	BOOL success;
	PRT_VALUE *ev;
	PRT_FUNSTACK_INFO p_tmp_frame;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

	PRT_VALUE* timerMachineId = p_tmp_frame.locals[0];
	PRT_MACHINEINST* timerMachine = PrtGetMachine(context->process, timerMachineId);
	TimerContext *timerContext = (TimerContext *)timerMachine->extContext;

	timerContext->started = PRT_FALSE;
	success = CancelWaitableTimer(timerContext->timer);
	if (success) {
		ev = PrtMkEventValue(P_EVENT_CANCEL_SUCCESS);
		PrtSend(context, PrtGetMachine(context->process, timerContext->client), ev, timerMachine->id, PRT_FALSE);
	}
	else {
		ev = PrtMkEventValue(P_EVENT_CANCEL_FAILURE);
		PrtSend(context, PrtGetMachine(context->process, timerContext->client), ev, timerMachine->id, PRT_FALSE);
	}
	PrtFreeValue(ev);

	// free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);

	return NULL;
}

void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context)
{
	TimerContext *timerContext;
	timerContext = (TimerContext *)context->extContext;

	PrtFreeValue(timerContext->client);
	CloseHandle(timerContext->timer);
	PrtFree(timerContext);
}

void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
	TimerContext *timerContext = (TimerContext *)PrtMalloc(sizeof(TimerContext));
	timerContext->client = PrtCloneValue(value);
	timerContext->started = PRT_FALSE;
	context->extContext = timerContext;
}
