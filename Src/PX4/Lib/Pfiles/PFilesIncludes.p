#include "FlightController.p"
#include "Timer.p"
#include "Mission_1.p"
#include "PX4Model.p"
#include "POrbTopics.p"
#include "POrb.p"
#include "FlightController.p"
#include "HeartbeatMonitor.p"
#include "GPSHealthMonitor.p"
#include "BatteryMonitor.p"
#include "AltitudeMonitor.p"
#include "GeofenceMonitor.p"
#include "Commands.p"
#include "..\PFloat32\Float32.p"
#include "POrbTopics.p"
#include "..\PMavlinkMsgs\PFiles\P_common_Enums.p"
#include "..\PMavlinkMsgs\PFiles\P_common_MessageTypes.p"
#include "PX4_API.p"

fun sealwithRTC()
//[invokescheduler = sealRTC]
{}

fun unsealwithRTC()
//[invokescheduler = unsealRTC]
{}

fun sealwithRR()
//[invokescheduler = sealRR]
{}

fun unsealwithRR()
//[invokescheduler = unsealRR]
{}