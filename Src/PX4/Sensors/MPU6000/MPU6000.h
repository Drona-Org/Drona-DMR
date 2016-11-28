#pragma once

#include <PrtDist.h>

int Init(PRT_CHAR* logPath);
void RunSimulation();
void StopSimulation();
void RaiseEvent(int machineId, int eventId, PRT_VALUE* value);

PRT_VALUE* MakeBooleanValue(BOOL b);
PRT_VALUE* MakeIntegerValue(int i);
PRT_VALUE* MakeNullValue();