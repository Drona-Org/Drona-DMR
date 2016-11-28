#include "POrb.h"
#include "EventTrace.h"
#include "EventLog.h"
#include "PFiles.h"

BOOLEAN POrb_isUDP = TRUE;
char* POrb_portAddr = nullptr;


PRT_VALUE *P_FUN_POrbMachine_InitializeListener_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

	// create model machine representing the remote PX4 device.
	POrbMavlink::PX4ModelMachine = PrtMkMachine(MAIN_APPLICATION_PROCESS, P_MACHINE_PX4Model, PrtMkNullValue());

	//initialize the dispatcher
	POrbMavlink::POrbMasterMachine = PrtGetMachine(MAIN_APPLICATION_PROCESS, p_tmp_frame.locals[0]);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return NULL;
}

void P_DTOR_POrbMachine_IMPL(PRT_MACHINEINST *context)
{
}


void P_CTOR_POrbMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}
