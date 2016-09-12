#include "PFiles.h"
#include "Float32.h"
#include "Commands.h"
#include "PTrace.h"
#include <malloc.h>
#include "PrtUser.h"
#include "PrtWinUserConfig.h"

extern "C"
{
	const char* FormatMessageBuffer(const char* format, ...)
	{
		char* buffer = (char*)malloc(5000);
		if (buffer == NULL) {
			EventTrace(PProgram, 0, "Out of memory");
			PrtAssert(PRT_FALSE, "Out of memory");
		}
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, 5000, format, args);
		va_end(args);
		return buffer;
	}

	void P_DTOR_CommanderMachine_IMPL(PRT_MACHINEINST *context)
	{
	}

	void P_CTOR_CommanderMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
	{
	}

	PRT_VALUE *P_FUN_GetSystemTime_IMPL(PRT_MACHINEINST *context)
	{
		PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
		PRT_FUNSTACK_INFO p_tmp_frame;
		PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

		int ms = GetTickCount();

		PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
		return PrtMkIntValue(ms);
	}

	PRT_VALUE *P_FUN_CommanderMachine_SendCommandToPx4_IMPL(PRT_MACHINEINST *context)
	{
		PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
		PRT_FUNSTACK_INFO p_tmp_frame;
		PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);

		PRT_VALUE* caller = p_tmp_frame.locals[0];

		PRT_VALUE* cmdId = p_tmp_frame.locals[2];
		int cmd = 0;
		if (cmdId->discriminator == PRT_VALUE_KIND_INT)
		{
			cmd = PrtPrimGetInt(cmdId);
		}

		PRT_VALUE* confirmValue = p_tmp_frame.locals[1];
		bool confirm = false;
		if (confirmValue->discriminator == PRT_VALUE_KIND_BOOL)
		{
			confirm = (PrtPrimGetBool(confirmValue) == PRT_TRUE);
		}

		float floats[7] = { 0,0,0,0,0,0,0 };

		// gray the remaining 7 arguments and convert them to float values.
		for (int i = 3; i < 3 + 7; i++)
		{
			PRT_VALUE* arg = p_tmp_frame.locals[i];
			float value = PrtGetFloat32(arg);
			floats[i - 3] = value;
		}

		EventTrace(PProgram, 0, "Sending command: %d, with args (%f,%f,%f,%f,%f,%f,%f)\n", cmd, floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6]);

		SendCommand(cmd, confirm, floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6]);

		PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
		return NULL;
	}

}
