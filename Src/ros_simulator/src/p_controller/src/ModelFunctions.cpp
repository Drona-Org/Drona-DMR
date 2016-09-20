#include "Workspace.h"

#if defined(TEST_PLAN_EXECUTOR)
#include "StubMotionPlanner.h"
#elif defined(TEST_MOTION_PLANNER)
#include "TestDriver.h"
#else
#endif

#include <Eigen/Dense>

WS_Dimension dim = {4, 4, 1};

PRT_VALUE *P_FUN_RosInit_IMPL(PRT_MACHINEINST *context)
{
	PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
	PRT_VALUE *p_tmp_ret = NULL;
	PRT_FUNSTACK_INFO p_tmp_frame;
	PRT_VALUE *p_tmp_params;
	p_tmp_params = NULL;
	//remm to pop frame
	PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
	//create a tuple value
	int robot_id = (int)PrtPrimGetInt(p_tmp_frame.locals[0]);
	
	//remm to free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return p_tmp_ret;
}

static Eigen::Vector3i ReadVectorCoord(PRT_VALUE* trajSeq, PRT_UINT32 i)
{
	int loc = (int)PrtPrimGetInt(PrtSeqGetNCIntIndex(trajSeq, i));
	WS_Coord coord = ExtractCoordFromGridLocation(loc, dim);
	return Eigen::Vector3i(coord.x, coord.y, coord.z);
}

PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context)
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
	PRT_UINT32 count = PrtSeqSizeOf(trajSeq);
	if(count >= 2) {
		Eigen::Vector3i diff;
		PRT_UINT32 i = 1;
		Eigen::Vector3i current_step = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
		bool done = false;
		while(!done) {
			Eigen::Vector3i straight_step(0, 0, 0);
			do {
				i++;
				straight_step += current_step;
				if(i == count) {
					done = true;
					break;
				}
				diff = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
			} while (diff == current_step);
			current_step = diff;
			printf("move in (%d, %d, %d)\n", straight_step[0], straight_step[1], straight_step[2]);
		}
	}
	//remm to free the frame
	PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
	return p_tmp_ret;
}
