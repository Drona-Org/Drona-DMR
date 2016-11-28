
  #ifndef P_PROGRAM_H
    #define P_PROGRAM_H
    #include "linker.h"
    #ifdef __cplusplus
      extern "C"{
    #endif
    enum P_FUNS_AltitudeMonitorMachine
    {
      P_FUN_AltitudeMonitorMachine_ANON0 = 46,
      P_FUN_AltitudeMonitorMachine_ANON1 = 47,
      P_FUN_AltitudeMonitorMachine_ANON2 = 48,
      P_FUN_AltitudeMonitorMachine_ANON3 = 49,
      P_FUN_AltitudeMonitorMachine_ANON4 = 50,
      _P_FUNS_AltitudeMonitorMachine_COUNT = 51
    };

    enum P_FUNS_BatteryMonitorMachine
    {
      P_FUN_BatteryMonitorMachine_ANON0 = 46,
      P_FUN_BatteryMonitorMachine_ANON1 = 47,
      P_FUN_BatteryMonitorMachine_ANON2 = 48,
      _P_FUNS_BatteryMonitorMachine_COUNT = 49
    };

    enum P_FUNS_CommanderMachine
    {
      P_FUN_CommanderMachine_ANON0 = 46,
      P_FUN_CommanderMachine_ANON1 = 47,
      P_FUN_CommanderMachine_ANON2 = 48,
      P_FUN_CommanderMachine_ANON3 = 49,
      P_FUN_CommanderMachine_ANON4 = 50,
      P_FUN_CommanderMachine_ANON5 = 51,
      P_FUN_CommanderMachine_SendCommandToPx4 = 52,
      P_FUN_CommanderMachine_SendWithRetry = 53,
      _P_FUNS_CommanderMachine_COUNT = 54
    };

    enum P_FUNS_FlightControllerMachine
    {
      P_FUN_FlightControllerMachine_ANON0 = 46,
      P_FUN_FlightControllerMachine_ANON1 = 47,
      P_FUN_FlightControllerMachine_ANON2 = 48,
      P_FUN_FlightControllerMachine_ANON3 = 49,
      P_FUN_FlightControllerMachine_ANON4 = 50,
      P_FUN_FlightControllerMachine_ANON5 = 51,
      P_FUN_FlightControllerMachine_ANON6 = 52,
      P_FUN_FlightControllerMachine_ANON7 = 53,
      P_FUN_FlightControllerMachine_ANON8 = 54,
      P_FUN_FlightControllerMachine_ANON9 = 55,
      P_FUN_FlightControllerMachine_ANON10 = 56,
      P_FUN_FlightControllerMachine_ANON11 = 57,
      P_FUN_FlightControllerMachine_ANON12 = 58,
      P_FUN_FlightControllerMachine_ANON13 = 59,
      P_FUN_FlightControllerMachine_ANON14 = 60,
      P_FUN_FlightControllerMachine_ANON15 = 61,
      P_FUN_FlightControllerMachine_ANON16 = 62,
      P_FUN_FlightControllerMachine_ANON17 = 63,
      P_FUN_FlightControllerMachine_ANON18 = 64,
      P_FUN_FlightControllerMachine_ANON19 = 65,
      P_FUN_FlightControllerMachine_ANON20 = 66,
      P_FUN_FlightControllerMachine_ANON21 = 67,
      P_FUN_FlightControllerMachine_ANON22 = 68,
      P_FUN_FlightControllerMachine_ANON23 = 69,
      P_FUN_FlightControllerMachine_ANON24 = 70,
      P_FUN_FlightControllerMachine_ANON25 = 71,
      P_FUN_FlightControllerMachine_ANON26 = 72,
      P_FUN_FlightControllerMachine_ANON27 = 73,
      P_FUN_FlightControllerMachine_ANON28 = 74,
      P_FUN_FlightControllerMachine_ANON29 = 75,
      P_FUN_FlightControllerMachine_ANON30 = 76,
      P_FUN_FlightControllerMachine_ANON31 = 77,
      P_FUN_FlightControllerMachine_ANON32 = 78,
      P_FUN_FlightControllerMachine_ANON33 = 79,
      P_FUN_FlightControllerMachine_ANON34 = 80,
      P_FUN_FlightControllerMachine_ANON35 = 81,
      P_FUN_FlightControllerMachine_ANON36 = 82,
      P_FUN_FlightControllerMachine_ANON37 = 83,
      P_FUN_FlightControllerMachine_ANON38 = 84,
      P_FUN_FlightControllerMachine_CheckHome = 85,
      P_FUN_FlightControllerMachine_CheckReady = 86,
      P_FUN_FlightControllerMachine_FlightControllerReady = 87,
      P_FUN_FlightControllerMachine_InitializeFlightController = 88,
      P_FUN_FlightControllerMachine_IsBatteryCharged = 89,
      P_FUN_FlightControllerMachine_IsGPSLocked = 90,
      P_FUN_FlightControllerMachine_IsGlobalPositionKnown = 91,
      P_FUN_FlightControllerMachine_IsHomeSet = 92,
      P_FUN_FlightControllerMachine_IsLocalSet = 93,
      P_FUN_FlightControllerMachine_IsPX4Alive = 94,
      P_FUN_FlightControllerMachine_IsReady = 95,
      _P_FUNS_FlightControllerMachine_COUNT = 96
    };

    enum P_FUNS_GLOBAL
    {
      _P_FUN_PUSH_OR_IGN = 0,
      P_FUN_ANON0 = 1,
      P_FUN_ANON1 = 2,
      P_FUN_AbsFloat32 = 3,
      P_FUN_AddFloat32 = 4,
      P_FUN_ArmVehicle = 5,
      P_FUN_AssignFloat32 = 6,
      P_FUN_CancelTimer = 7,
      P_FUN_CancelTimerAndHandleResponse = 8,
      P_FUN_CreateTimer = 9,
      P_FUN_DisArmVehicle = 10,
      P_FUN_DivFloat32 = 11,
      P_FUN_GetSystemTime = 12,
      P_FUN_GoToLocation = 13,
      P_FUN_IntToFloat32 = 14,
      P_FUN_IsEqFloat32 = 15,
      P_FUN_IsFiniteFloat32 = 16,
      P_FUN_IsGeFloat32 = 17,
      P_FUN_IsGtFloat32 = 18,
      P_FUN_IsInftyFloat32 = 19,
      P_FUN_IsLeFloat32 = 20,
      P_FUN_IsLtFloat32 = 21,
      P_FUN_IsNEqFloat32 = 22,
      P_FUN_IsNaNFloat32 = 23,
      P_FUN_IsNearFloat32 = 24,
      P_FUN_IsNegInftyFloat32 = 25,
      P_FUN_IsPosInftyFloat32 = 26,
      P_FUN_LandVehicle = 27,
      P_FUN_LocalToGlobal = 28,
      P_FUN_MulFloat32 = 29,
      P_FUN_NaNFloat32 = 30,
      P_FUN_NegFloat32 = 31,
      P_FUN_Publish = 32,
      P_FUN_ReturnToLaunch = 33,
      P_FUN_ScientificToFloat32 = 34,
      P_FUN_SendHeartbeat = 35,
      P_FUN_SendSetHomeCommand = 36,
      P_FUN_SetMessageInterval = 37,
      P_FUN_StartTimer = 38,
      P_FUN_SubFloat32 = 39,
      P_FUN_Subscribe = 40,
      P_FUN_TakeOff = 41,
      P_FUN_sealwithRR = 42,
      P_FUN_sealwithRTC = 43,
      P_FUN_unsealwithRR = 44,
      P_FUN_unsealwithRTC = 45
    };

    enum P_FUNS_GPSHealthMonitorMachine
    {
      P_FUN_GPSHealthMonitorMachine_ANON0 = 46,
      P_FUN_GPSHealthMonitorMachine_ANON1 = 47,
      P_FUN_GPSHealthMonitorMachine_ANON2 = 48,
      P_FUN_GPSHealthMonitorMachine_ANON3 = 49,
      P_FUN_GPSHealthMonitorMachine_ANON4 = 50,
      _P_FUNS_GPSHealthMonitorMachine_COUNT = 51
    };

    enum P_FUNS_GeofenceMonitorMachine
    {
      P_FUN_GeofenceMonitorMachine_ANON0 = 46,
      P_FUN_GeofenceMonitorMachine_ANON1 = 47,
      P_FUN_GeofenceMonitorMachine_ANON2 = 48,
      P_FUN_GeofenceMonitorMachine_ANON3 = 49,
      _P_FUNS_GeofenceMonitorMachine_COUNT = 50
    };

    enum P_FUNS_HeartbeatMonitorMachine
    {
      P_FUN_HeartbeatMonitorMachine_ANON0 = 46,
      P_FUN_HeartbeatMonitorMachine_ANON1 = 47,
      P_FUN_HeartbeatMonitorMachine_ANON2 = 48,
      P_FUN_HeartbeatMonitorMachine_ANON3 = 49,
      _P_FUNS_HeartbeatMonitorMachine_COUNT = 50
    };

    enum P_FUNS_Main
    {
      P_FUN_Main_ANON0 = 46,
      P_FUN_Main_ANON1 = 47,
      _P_FUNS_Main_COUNT = 48
    };

    enum P_FUNS_MissionPlannerMachine
    {
      P_FUN_MissionPlannerMachine_ANON0 = 46,
      P_FUN_MissionPlannerMachine_ANON1 = 47,
      P_FUN_MissionPlannerMachine_ANON2 = 48,
      P_FUN_MissionPlannerMachine_ANON3 = 49,
      P_FUN_MissionPlannerMachine_ANON4 = 50,
      P_FUN_MissionPlannerMachine_ANON5 = 51,
      P_FUN_MissionPlannerMachine_ANON6 = 52,
      P_FUN_MissionPlannerMachine_ANON7 = 53,
      P_FUN_MissionPlannerMachine_ANON8 = 54,
      P_FUN_MissionPlannerMachine_ANON9 = 55,
      P_FUN_MissionPlannerMachine_NextPathSegment = 56,
      _P_FUNS_MissionPlannerMachine_COUNT = 57
    };

    enum P_FUNS_POrbMachine
    {
      P_FUN_POrbMachine_ANON0 = 46,
      P_FUN_POrbMachine_ANON1 = 47,
      P_FUN_POrbMachine_ANON2 = 48,
      P_FUN_POrbMachine_ANON3 = 49,
      P_FUN_POrbMachine_Broadcast = 50,
      P_FUN_POrbMachine_InitializeListener = 51,
      P_FUN_POrbMachine_IsSubscribed = 52,
      _P_FUNS_POrbMachine_COUNT = 53
    };

    enum P_FUNS_PX4Model
    {
      P_FUN_PX4Model_ANON0 = 46,
      _P_FUNS_PX4Model_COUNT = 47
    };

    enum P_FUNS_Timer
    {
      P_FUN_Timer_ANON0 = 46,
      P_FUN_Timer_ANON1 = 47,
      P_FUN_Timer_ANON2 = 48,
      P_FUN_Timer_ANON3 = 49,
      P_FUN_Timer_ANON4 = 50,
      _P_FUNS_Timer_COUNT = 51
    };

    enum P_STATES_AltitudeMonitorMachine
    {
      P_STATE_AltitudeMonitorMachine_Init = 0,
      P_STATE_AltitudeMonitorMachine_MonitorAltitude = 1,
      _P_STATES_AltitudeMonitorMachine_COUNT = 2
    };

    enum P_STATES_BatteryMonitorMachine
    {
      P_STATE_BatteryMonitorMachine_Init = 0,
      P_STATE_BatteryMonitorMachine_MonitorBatteryLevel = 1,
      _P_STATES_BatteryMonitorMachine_COUNT = 2
    };

    enum P_STATES_CommanderMachine
    {
      P_STATE_CommanderMachine_Init = 0,
      P_STATE_CommanderMachine_ProcessCommands = 1,
      P_STATE_CommanderMachine_SendCommand = 2,
      _P_STATES_CommanderMachine_COUNT = 3
    };

    enum P_STATES_FlightControllerMachine
    {
      P_STATE_FlightControllerMachine_Armed = 0,
      P_STATE_FlightControllerMachine_Disarming = 1,
      P_STATE_FlightControllerMachine_GeofenceBreached = 2,
      P_STATE_FlightControllerMachine_GoingSomeplace = 3,
      P_STATE_FlightControllerMachine_Init = 4,
      P_STATE_FlightControllerMachine_Landing = 5,
      P_STATE_FlightControllerMachine_Loitering = 6,
      P_STATE_FlightControllerMachine_LowBattery = 7,
      P_STATE_FlightControllerMachine_NoGPS = 8,
      P_STATE_FlightControllerMachine_StandBy = 9,
      P_STATE_FlightControllerMachine_TakingOff = 10,
      _P_STATES_FlightControllerMachine_COUNT = 11
    };

    enum P_STATES_GPSHealthMonitorMachine
    {
      P_STATE_GPSHealthMonitorMachine_Init = 0,
      P_STATE_GPSHealthMonitorMachine_MonitorGPSLock = 1,
      _P_STATES_GPSHealthMonitorMachine_COUNT = 2
    };

    enum P_STATES_GeofenceMonitorMachine
    {
      P_STATE_GeofenceMonitorMachine_Init = 0,
      P_STATE_GeofenceMonitorMachine_MonitorGeofence = 1,
      _P_STATES_GeofenceMonitorMachine_COUNT = 2
    };

    enum P_STATES_HeartbeatMonitorMachine
    {
      P_STATE_HeartbeatMonitorMachine_Init = 0,
      P_STATE_HeartbeatMonitorMachine_MonitorHeartbeat = 1,
      _P_STATES_HeartbeatMonitorMachine_COUNT = 2
    };

    enum P_STATES_Main
    {
      P_STATE_Main_Init = 0,
      _P_STATES_Main_COUNT = 1
    };

    enum P_STATES_MissionPlannerMachine
    {
      P_STATE_MissionPlannerMachine_FollowPath = 0,
      P_STATE_MissionPlannerMachine_Init = 1,
      P_STATE_MissionPlannerMachine_MissionComplete = 2,
      P_STATE_MissionPlannerMachine_StartMission = 3,
      _P_STATES_MissionPlannerMachine_COUNT = 4
    };

    enum P_STATES_POrbMachine
    {
      P_STATE_POrbMachine_Init = 0,
      P_STATE_POrbMachine_ReadMessagesAndPublish = 1,
      _P_STATES_POrbMachine_COUNT = 2
    };

    enum P_STATES_PX4Model
    {
      P_STATE_PX4Model_Init = 0,
      _P_STATES_PX4Model_COUNT = 1
    };

    enum P_STATES_Timer
    {
      P_STATE_Timer_Init = 0,
      P_STATE_Timer_WaitForCancel = 1,
      P_STATE_Timer_WaitForReq = 2,
      _P_STATES_Timer_COUNT = 3
    };

    enum P_VARS_AltitudeMonitorMachine
    {
      P_VAR_AltitudeMonitorMachine_commander = 0,
      P_VAR_AltitudeMonitorMachine_currentAlt = 1,
      P_VAR_AltitudeMonitorMachine_delta = 2,
      P_VAR_AltitudeMonitorMachine_isActive = 3,
      P_VAR_AltitudeMonitorMachine_isFlying = 4,
      P_VAR_AltitudeMonitorMachine_isLanding = 5,
      P_VAR_AltitudeMonitorMachine_orb = 6,
      P_VAR_AltitudeMonitorMachine_targetAlt = 7,
      _P_VARS_AltitudeMonitorMachine_COUNT = 8
    };

    enum P_VARS_BatteryMonitorMachine
    {
      P_VAR_BatteryMonitorMachine_batteryDischarged = 0,
      P_VAR_BatteryMonitorMachine_commander = 1,
      P_VAR_BatteryMonitorMachine_orb = 2,
      _P_VARS_BatteryMonitorMachine_COUNT = 3
    };

    enum P_VARS_CommanderMachine
    {
      P_VAR_CommanderMachine_currCmd = 0,
      P_VAR_CommanderMachine_retries = 1,
      P_VAR_CommanderMachine_timer = 2,
      _P_VARS_CommanderMachine_COUNT = 3
    };

    enum P_VARS_FlightControllerMachine
    {
      P_VAR_FlightControllerMachine_altitudeMonitor = 0,
      P_VAR_FlightControllerMachine_commander = 1,
      P_VAR_FlightControllerMachine_geofenceMonitor = 2,
      P_VAR_FlightControllerMachine_orb = 3,
      P_VAR_FlightControllerMachine_targetLocation = 4,
      P_VAR_FlightControllerMachine_vStatus = 5,
      _P_VARS_FlightControllerMachine_COUNT = 6
    };

    enum P_VARS_GPSHealthMonitorMachine
    {
      P_VAR_GPSHealthMonitorMachine_commander = 0,
      P_VAR_GPSHealthMonitorMachine_orb = 1,
      P_VAR_GPSHealthMonitorMachine_status = 2,
      _P_VARS_GPSHealthMonitorMachine_COUNT = 3
    };

    enum P_VARS_GeofenceMonitorMachine
    {
      P_VAR_GeofenceMonitorMachine_commander = 0,
      P_VAR_GeofenceMonitorMachine_home = 1,
      P_VAR_GeofenceMonitorMachine_orb = 2,
      P_VAR_GeofenceMonitorMachine_radius = 3,
      _P_VARS_GeofenceMonitorMachine_COUNT = 4
    };

    enum P_VARS_HeartbeatMonitorMachine
    {
      P_VAR_HeartbeatMonitorMachine_commander = 0,
      P_VAR_HeartbeatMonitorMachine_heartbeatTimerV = 1,
      P_VAR_HeartbeatMonitorMachine_orb = 2,
      P_VAR_HeartbeatMonitorMachine_status = 3,
      _P_VARS_HeartbeatMonitorMachine_COUNT = 4
    };

    enum P_VARS_Main
    {
      _P_VARS_Main_COUNT = 0
    };

    enum P_VARS_MissionPlannerMachine
    {
      P_VAR_MissionPlannerMachine_commander = 0,
      P_VAR_MissionPlannerMachine_controller = 1,
      P_VAR_MissionPlannerMachine_landed = 2,
      P_VAR_MissionPlannerMachine_landing = 3,
      P_VAR_MissionPlannerMachine_orb = 4,
      P_VAR_MissionPlannerMachine_path = 5,
      P_VAR_MissionPlannerMachine_pathPos = 6,
      P_VAR_MissionPlannerMachine_target = 7,
      P_VAR_MissionPlannerMachine_timer = 8,
      P_VAR_MissionPlannerMachine_tracking = 9,
      _P_VARS_MissionPlannerMachine_COUNT = 10
    };

    enum P_VARS_POrbMachine
    {
      P_VAR_POrbMachine_topicSubscribers = 0,
      _P_VARS_POrbMachine_COUNT = 1
    };

    enum P_VARS_PX4Model
    {
      _P_VARS_PX4Model_COUNT = 0
    };

    enum P_VARS_Timer
    {
      P_VAR_Timer_client = 0,
      _P_VARS_Timer_COUNT = 1
    };

    void P_DTOR_AltitudeMonitorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_BatteryMonitorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_CommanderMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_FlightControllerMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_GPSHealthMonitorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_GeofenceMonitorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_HeartbeatMonitorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_Main_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_MissionPlannerMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_POrbMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_PX4Model_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_AltitudeMonitorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_BatteryMonitorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_CommanderMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_FlightControllerMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_GPSHealthMonitorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_GeofenceMonitorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_HeartbeatMonitorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_Main_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_MissionPlannerMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_POrbMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_PX4Model_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    PRT_VALUE *P_FUN_AbsFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_AddFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_AssignFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_CancelTimer_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_CommanderMachine_SendCommandToPx4_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_DivFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_FlightControllerMachine_FlightControllerReady_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_GetSystemTime_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IntToFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsEqFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsFiniteFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsGeFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsGtFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsInftyFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsLeFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsLtFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsNEqFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsNaNFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsNearFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsNegInftyFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_IsPosInftyFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_LocalToGlobal_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_MulFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_NaNFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_NegFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_POrbMachine_InitializeListener_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_ScientificToFloat32_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_SendHeartbeat_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_SendSetHomeCommand_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_StartTimer_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_SubFloat32_IMPL(PRT_MACHINEINST *context);

    #ifdef __cplusplus
      }
    #endif
  #endif
  