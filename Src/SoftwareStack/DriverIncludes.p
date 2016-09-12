/* We are testing:
 1) flight controller
 2) GeofenceMonitor
 3) POrb
 4) POrbTopics
 5) Timer
 6) BatteryMonitor
 7) AltitudeMonitor
 8) GPSHealthMonitor
*/
#include "FlightController.p"
#include "Timer.p"
#include "POrbTopics.p"
#include "POrb.p"
#include "FlightController.p"
#include "BatteryMonitor.p"
#include "AltitudeMonitor.p"
#include "GeofenceMonitor.p"
#include "GPSHealthMonitor.p"
#include "..\PFloat32\Float32.p"
#include "..\PMavlinkMsgs\PFiles\P_common_Enums.p"
#include "..\PMavlinkMsgs\PFiles\P_common_MessageTypes.p"

/* 
Replacing the following with stubs:
1) MissionPlanner: Random mission planner that pumps in events
2) Commands: Command servicing engine that immediately sends the ack back and sends a message to PX4 model to upate state
3) Heartbeatmonitor: Currently only one implementation that always keeps PX4 alive.
*/
include "Driver_MissionPlanner.p"
include "Driver_Commands.p"
include "Driver_HeartbeatMonitor.p"
include "Driver_PX4Model.p"
include "Driver_PX4_API.p"


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