#pragma once

#ifndef P_COMMANDS_H
#define P_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif
	extern void SendCommand(int cmdid, bool confirm, float a1, float a2, float a3, float a4, float a5, float a6, float a7);
	extern void SendHeartbeat();
#ifdef __cplusplus
}
#endif
#endif