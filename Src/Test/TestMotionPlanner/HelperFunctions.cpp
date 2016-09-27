#include "TestDriver.h"
#include "Workspace.h"
#include "PlanGenerator.h"
#include "Compat.h"

PRT_VALUE *P_FUN_Sleep_IMPL(PRT_MACHINEINST *context) {
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	//create a tuple value
	time = PrtPrimGetInt(p_tmp_frame.locals[0]);
	SleepMs(time);
	//remm to free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return p_tmp_ret;
}

PRT_VALUE *P_FUN_GetNumOfRobots_IMPL(PRT_MACHINEINST *context) {
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return PrtMkIntValue(WORKSPACE_INFO->numOfRobots);
}

PRT_VALUE *P_FUN_GetRobotInfo_IMPL(PRT_MACHINEINST *context) {
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	PRT_VALUE* retVal;
	int robotId;
	retVal = PrtMkDefaultValue(P_GEND_TYPE_RobotInfoType);
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	robotId = PrtPrimGetInt(p_tmp_frame.locals[0]);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);

	PrtTupleSetEx(retVal, 0, PrtMkIntValue(WORKSPACE_INFO->robots[robotId].id), PRT_FALSE);
	PrtTupleSetEx(retVal, 1, PrtMkIntValue(WORKSPACE_INFO->robots[robotId].start_position), PRT_FALSE);
	return retVal;
}

PRT_VALUE *P_FUN_GetGoalLocations_IMPL(PRT_MACHINEINST *context) {
	PRT_VALUE* retSeq;
	PRT_TYPE* intType;
	PRT_TYPE* intSeqType;
	int counter = 0;
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);

	intType = PrtMkPrimitiveType(PRT_KIND_INT);
	intSeqType = PrtMkSeqType(intType);
	retSeq = PrtMkDefaultValue(intSeqType);
	PrtFreeType(intType); PrtFreeType(intSeqType);
	
	for (counter = 0; counter < WORKSPACE_INFO->starts.size; counter++)
	{
		PrtSeqInsertExIntIndex(retSeq, counter, PrtMkIntValue(WORKSPACE_INFO->starts.locations[counter]), PRT_FALSE);
	}
	for (counter = 0; counter < WORKSPACE_INFO->ends.size; counter++)
	{
		PrtSeqInsertExIntIndex(retSeq, counter, PrtMkIntValue(WORKSPACE_INFO->ends.locations[counter]), PRT_FALSE);
	}
	return retSeq;
}

/*
model fun PlanGenerator(s: int, g: int, avoids: seq[seq[int]]) : seq[int] {
var ret : seq[int];
ret += (0, 1);
return ret;
}
*/
PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_PlanGenerator_IMPL(PRT_MACHINEINST *context) {
	PRT_TYPE* intType;
	PRT_TYPE* intSeqType;
	int counter = 0;
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	int startLocation = PrtPrimGetInt(p_tmp_frame.locals[0]);
	int goalLocation = PrtPrimGetInt(p_tmp_frame.locals[1]);
	PRT_VALUE* avoidsList = p_tmp_frame.locals[2];
	int robotid = PrtPrimGetInt(p_tmp_frame.locals[3]);
	int sizeOfAvoids = PrtSeqSizeOf(avoidsList);
	
	int* output_seq_of_locations = (int*)malloc(1000 * sizeof(int));
	int output_size = 0;
	vector< vector<WS_Coord> > avoidsArr(sizeOfAvoids);
	for (int i = 0; i < sizeOfAvoids; i++)
	{
		avoidsArr[i] = vector<WS_Coord>();
		PRT_VALUE* avoid_p = PrtSeqGetNCIntIndex(avoidsList, i);
		for (int j = 0; j < PrtSeqSizeOf(avoid_p); j++)
		{
			avoidsArr[i].push_back(ExtractCoordFromGridLocation(PrtPrimGetInt(PrtSeqGetNCIntIndex(avoid_p, j)), WORKSPACE_INFO->dimension));
		}
	}

	printf("====================================================\n");
	printf("Robot %d\n", robotid);
	//print the obstacles list
	PrintObstaclesList(*WORKSPACE_INFO);
	GenerateMotionPlanFor(*WORKSPACE_INFO, startLocation, goalLocation, WORKSPACE_INFO->obstacles.locations, WORKSPACE_INFO->obstacles.size, avoidsArr, output_seq_of_locations, &output_size);
	
	printf("Trajectory:");
	for (int i = 0; i < output_size; i++)
	{
		printf("%d ", output_seq_of_locations[i]);
	}
	printf("\n\n");
	printf("====================================================\n");

	PRT_VALUE* retPlan;
	intType = PrtMkPrimitiveType(PRT_KIND_INT);
	intSeqType = PrtMkSeqType(intType);
	retPlan = PrtMkDefaultValue(intSeqType);
	PrtFreeType(intType); PrtFreeType(intSeqType);
	
	for (int counter = 0; counter < output_size; counter++)
	{
		PrtSeqInsertExIntIndex(retPlan, counter, PrtMkIntValue(output_seq_of_locations[counter]), PRT_FALSE);
	}

	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return retPlan;
}

#if defined(PRT_PLAT_WINUSER) || defined(USE_EMPTY)
PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context) {
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return NULL;
}

PRT_VALUE *P_FUN_RosInit_IMPL(PRT_MACHINEINST *context) {
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	int time = 0;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return NULL;
}
#endif

