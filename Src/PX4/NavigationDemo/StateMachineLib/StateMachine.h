#pragma once

#include <PrtDist.h>


typedef void(PRT_CALL_CONV * LogHandler)(const char* message);

int Init(PRT_CHAR* logPath);
void RunSimulation(LogHandler logger);
void StopSimulation();
void RaiseEvent(int machineId, int eventId, PRT_VALUE* value);

PRT_VALUE* MakeBooleanValue(BOOL b);
PRT_VALUE* MakeIntegerValue(int i);
PRT_VALUE* MakeNullValue();