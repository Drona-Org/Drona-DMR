#include "Compat.h"
#include "TestDriver.h"

typedef struct TimerContext {
	PRT_VALUE *client;
	PRT_BOOLEAN started;
} TimerContext;

char* GetMachineName(PRT_MACHINEINST *context)
{
	char* name = context->process->program->machines[context->instanceOf]->name;
	return name;
}

PRT_VALUE *P_FUN_StartTimer_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;

	// pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

	PRT_VALUE* timerMachineId = p_tmp_frame.locals[0];
	PRT_MACHINEINST* timerMachine = PrtGetMachine(context->process, timerMachineId);
	TimerContext *timerContext = (TimerContext *)timerMachine->extContext;

	int timeout_value = p_tmp_frame.locals[1]->valueUnion.nt;
	
	SleepMs(timeout_value);

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
	return NULL;
}

void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context)
{
	TimerContext *timerContext;
	timerContext = (TimerContext *)context->extContext;

	PrtFreeValue(timerContext->client);
	PrtFree(timerContext);
}

void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
	TimerContext *timerContext = (TimerContext *)PrtMalloc(sizeof(TimerContext));
	timerContext->client = PrtCloneValue(value);
	timerContext->started = PRT_FALSE;
	context->extContext = timerContext;
}
