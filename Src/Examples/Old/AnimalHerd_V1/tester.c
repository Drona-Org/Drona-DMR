#include "program.h"

void ErrorHandler(PRT_STATUS status, PRT_MACHINEINST *ptr) 
{
	if (status == PRT_STATUS_ASSERT)
	{
		fprintf_s(stdout, "exiting with PRT_STATUS_ASSERT (assertion failure)\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_OVERFLOW)
	{
		fprintf_s(stdout, "exiting with PRT_STATUS_EVENT_OVERFLOW\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_UNHANDLED)
	{
		fprintf_s(stdout, "exiting with PRT_STATUS_EVENT_UNHANDLED\n");
		exit(1);
	}
	else if (status == PRT_STATUS_QUEUE_OVERFLOW)
	{
		fprintf_s(stdout, "exiting with PRT_STATUS_QUEUE_OVERFLOW \n");
		exit(1);
	}
	else if (status == PRT_STATUS_ILLEGAL_SEND)
	{
		fprintf_s(stdout, "exiting with PRT_STATUS_ILLEGAL_SEND \n");
		exit(1);
	}
	else
	{
		fprintf_s(stdout, "unexpected PRT_STATUS in ErrorHandler: %d\n", status);
		exit(2);
	}
	
	
}

void Log(PRT_STEP step, PRT_MACHINEINST *context) { PrtPrintStep(step, context);  }

int main(int argc, char *argv[])
{
	PRT_DBG_START_MEM_BALANCED_REGION
	{
		PRT_PROCESS *process;
		PRT_GUID processGuid;
		PRT_VALUE *payload;
		processGuid.data1 = 1;
		processGuid.data2 = 0;
		processGuid.data3 = 0;
		processGuid.data4 = 0;
		process = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, Log);
		payload = PrtMkNullValue();
		PrtMkMachine(process, _P_MACHINE_MAIN, payload);
		PrtFreeValue(payload);
		PrtStopProcess(process);
	}
	PRT_DBG_END_MEM_BALANCED_REGION
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
}

/*

PRT_VALUE *P_FUN_Executor_GetSeqFromComplan_IMPL(PRT_MACHINEINST *context, PRT_UINT32 funIndex, PRT_VALUE *value)
{
PRT_TYPE * intType = PrtMkPrimitiveType(PRT_KIND_INT);
PRT_TYPE* intSeq = PrtMkSeqType(intType);
PRT_VALUE * seqRetValu = PrtMkDefaultValue(intSeq);
PRT_VALUE* currLocation = PrtTupleGetNC(value, 0);
PRT_VALUE* destLocation = PrtTupleGetNC(value, 1);
int obs[1] = { 0 };
PRT_INT32 output[100];
PRT_INT32 outputSize = 0;
int iter = 0;
if ((destLocation->valueUnion.nt == currLocation->valueUnion.nt + 1) || (currLocation->valueUnion.nt + 1 == 16 && destLocation->valueUnion.nt == 1))
{
PRT_VALUE* index = PrtMkIntValue(0);
PrtSeqInsert(seqRetValu, index, destLocation);
PrtSeqInsert(seqRetValu, index, currLocation);

}
else
{
GenerateMotionPlanFor(currLocation->valueUnion.nt, destLocation->valueUnion.nt, obs, 0, output, &outputSize);
for (iter = 0; iter < outputSize; iter++)
{
PRT_VALUE* index = PrtMkIntValue(iter);
PRT_VALUE* val = PrtMkIntValue(output[iter]);
PrtSeqInsert(seqRetValu, index, val);
PrtFreeValue(index);
PrtFreeValue(val);
}
}
return seqRetValu;
}
*/
