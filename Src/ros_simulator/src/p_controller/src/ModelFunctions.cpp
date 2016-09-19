#include "Workspace.h"

#ifdef __cplusplus
extern "C" {
#include "PlanExecutor.h"
#endif

WS_Dimension dim = {4, 4, 1};

void P_CTOR_PlanExecutorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}
void P_DTOR_PlanExecutorMachine_IMPL(PRT_MACHINEINST *context)
{
}

void P_CTOR_MotionPlannerMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}
void P_DTOR_MotionPlannerMachine_IMPL(PRT_MACHINEINST *context)
{
}

PRT_VALUE *P_FUN_PlanExecutorMachine_RosInit_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int robotid = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	//create a tuple value
	robotid = (int)PrtPrimGetInt(p_tmp_frame.locals[0]);
	//remm to free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return p_tmp_ret;
}

PRT_VALUE *P_FUN_PlanExecutorMachine_StartExecutingPath_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int robotid = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	//create a tuple value
	PRT_VALUE* trajSeq = p_tmp_frame.locals[0];
	for(PRT_UINT32 i = 0; i < PrtSeqSizeOf(trajSeq); i++)
	{
		int loc = (int)PrtPrimGetInt(PrtSeqGetNCIntIndex(trajSeq, i));
		WS_Coord coord = ExtractCoordFromGridLocation(loc, dim);
		printf("loc: %d %d %d\n", coord.x, coord.y, coord.z);
	}
	//remm to free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return p_tmp_ret;
}


#ifdef __cplusplus
}
#endif
