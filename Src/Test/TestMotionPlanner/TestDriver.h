
  #ifndef P_PROGRAM_H
    #define P_PROGRAM_H
    #include "linker.h"
    #ifdef __cplusplus
      extern "C"{
    #endif
    enum P_FUNS_DistributedMotionPlannerMachine
    {
      P_FUN_DistributedMotionPlannerMachine_ANON0 = 13,
      P_FUN_DistributedMotionPlannerMachine_ANON1 = 14,
      P_FUN_DistributedMotionPlannerMachine_ANON2 = 15,
      P_FUN_DistributedMotionPlannerMachine_ANON3 = 16,
      P_FUN_DistributedMotionPlannerMachine_ANON4 = 17,
      P_FUN_DistributedMotionPlannerMachine_ANON5 = 18,
      P_FUN_DistributedMotionPlannerMachine_ANON6 = 19,
      P_FUN_DistributedMotionPlannerMachine_ANON7 = 20,
      P_FUN_DistributedMotionPlannerMachine_ANON8 = 21,
      P_FUN_DistributedMotionPlannerMachine_ANON9 = 22,
      P_FUN_DistributedMotionPlannerMachine_ANON10 = 23,
      P_FUN_DistributedMotionPlannerMachine_ANON11 = 24,
      P_FUN_DistributedMotionPlannerMachine_ANON12 = 25,
      P_FUN_DistributedMotionPlannerMachine_ANON13 = 26,
      P_FUN_DistributedMotionPlannerMachine_ComputeTimedTraj = 27,
      P_FUN_DistributedMotionPlannerMachine_ConvertTimedTrajToTraj = 28,
      P_FUN_DistributedMotionPlannerMachine_PlanGenerator = 29,
      P_FUN_DistributedMotionPlannerMachine_allTrajsReceived = 30,
      _P_FUNS_DistributedMotionPlannerMachine_COUNT = 31
    };

    enum P_FUNS_DistributedTimeSyncMachine
    {
      P_FUN_DistributedTimeSyncMachine_ANON0 = 13,
      P_FUN_DistributedTimeSyncMachine_ANON1 = 14,
      P_FUN_DistributedTimeSyncMachine_ANON2 = 15,
      P_FUN_DistributedTimeSyncMachine_ANON3 = 16,
      _P_FUNS_DistributedTimeSyncMachine_COUNT = 17
    };

    enum P_FUNS_GLOBAL
    {
      _P_FUN_PUSH_OR_IGN = 0,
      P_FUN_ANON0 = 1,
      P_FUN_BROADCAST = 2,
      P_FUN_CancelTimer = 3,
      P_FUN_CreateTimer = 4,
      P_FUN_GetCurrentTimePeriod = 5,
      P_FUN_GetGoalLocations = 6,
      P_FUN_GetNumOfRobots = 7,
      P_FUN_GetRobotInfo = 8,
      P_FUN_MotionPrimitiveTimePeriod = 9,
      P_FUN_Sleep = 10,
      P_FUN_StartExecutingPath = 11,
      P_FUN_StartTimer = 12
    };

    enum P_FUNS_Main
    {
      P_FUN_Main_ANON0 = 13,
      P_FUN_Main_ANON1 = 14,
      P_FUN_Main_ANON2 = 15,
      P_FUN_Main_InitializeSystem = 16,
      _P_FUNS_Main_COUNT = 17
    };

    enum P_FUNS_PlanExecutorMachine
    {
      P_FUN_PlanExecutorMachine_ANON0 = 13,
      P_FUN_PlanExecutorMachine_ANON1 = 14,
      P_FUN_PlanExecutorMachine_ANON2 = 15,
      P_FUN_PlanExecutorMachine_ANON3 = 16,
      _P_FUNS_PlanExecutorMachine_COUNT = 17
    };

    enum P_FUNS_RobotMachine
    {
      P_FUN_RobotMachine_ANON0 = 13,
      P_FUN_RobotMachine_ANON1 = 14,
      P_FUN_RobotMachine_ANON2 = 15,
      P_FUN_RobotMachine_ANON3 = 16,
      P_FUN_RobotMachine_ANON4 = 17,
      _P_FUNS_RobotMachine_COUNT = 18
    };

    enum P_FUNS_Timer
    {
      P_FUN_Timer_ANON0 = 13,
      P_FUN_Timer_ANON1 = 14,
      P_FUN_Timer_ANON2 = 15,
      P_FUN_Timer_ANON3 = 16,
      P_FUN_Timer_ANON4 = 17,
      _P_FUNS_Timer_COUNT = 18
    };

    enum P_STATES_DistributedMotionPlannerMachine
    {
      P_STATE_DistributedMotionPlannerMachine_ComputeTrajState = 0,
      P_STATE_DistributedMotionPlannerMachine_GetAllDistMotionPlanners = 1,
      P_STATE_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots = 2,
      P_STATE_DistributedMotionPlannerMachine_Init = 3,
      P_STATE_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation = 4,
      P_STATE_DistributedMotionPlannerMachine_WaitForRequests = 5,
      _P_STATES_DistributedMotionPlannerMachine_COUNT = 6
    };

    enum P_STATES_DistributedTimeSyncMachine
    {
      P_STATE_DistributedTimeSyncMachine_Init = 0,
      P_STATE_DistributedTimeSyncMachine_WaitForGetTimeRequest = 1,
      _P_STATES_DistributedTimeSyncMachine_COUNT = 2
    };

    enum P_STATES_Main
    {
      P_STATE_Main_Init = 0,
      P_STATE_Main_StartSendingTaskRequest = 1,
      _P_STATES_Main_COUNT = 2
    };

    enum P_STATES_PlanExecutorMachine
    {
      P_STATE_PlanExecutorMachine_Init = 0,
      P_STATE_PlanExecutorMachine_WaitForPathToExecute = 1,
      _P_STATES_PlanExecutorMachine_COUNT = 2
    };

    enum P_STATES_RobotMachine
    {
      P_STATE_RobotMachine_Init = 0,
      _P_STATES_RobotMachine_COUNT = 1
    };

    enum P_STATES_Timer
    {
      P_STATE_Timer_Init = 0,
      P_STATE_Timer_WaitForCancel = 1,
      P_STATE_Timer_WaitForReq = 2,
      _P_STATES_Timer_COUNT = 3
    };

    enum P_VARS_DistributedMotionPlannerMachine
    {
      P_VAR_DistributedMotionPlannerMachine_allAvoidsV = 0,
      P_VAR_DistributedMotionPlannerMachine_allRobotsMPV = 1,
      P_VAR_DistributedMotionPlannerMachine_currTaskV = 2,
      P_VAR_DistributedMotionPlannerMachine_currentLocationV = 3,
      P_VAR_DistributedMotionPlannerMachine_currentTrajV = 4,
      P_VAR_DistributedMotionPlannerMachine_localTimeV = 5,
      P_VAR_DistributedMotionPlannerMachine_myIdV = 6,
      P_VAR_DistributedMotionPlannerMachine_pendingRequestsV = 7,
      P_VAR_DistributedMotionPlannerMachine_planExecutorV = 8,
      P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV = 9,
      _P_VARS_DistributedMotionPlannerMachine_COUNT = 10
    };

    enum P_VARS_DistributedTimeSyncMachine
    {
      P_VAR_DistributedTimeSyncMachine_noOfRobots = 0,
      P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV = 1,
      P_VAR_DistributedTimeSyncMachine_timerV = 2,
      _P_VARS_DistributedTimeSyncMachine_COUNT = 3
    };

    enum P_VARS_Main
    {
      P_VAR_Main_allRobotsV = 0,
      P_VAR_Main_timeSyncV = 1,
      _P_VARS_Main_COUNT = 2
    };

    enum P_VARS_PlanExecutorMachine
    {
      P_VAR_PlanExecutorMachine_localTimeV = 0,
      P_VAR_PlanExecutorMachine_motionplanner = 1,
      P_VAR_PlanExecutorMachine_robotId = 2,
      _P_VARS_PlanExecutorMachine_COUNT = 3
    };

    enum P_VARS_RobotMachine
    {
      P_VAR_RobotMachine_allRobots = 0,
      P_VAR_RobotMachine_currentLocation = 1,
      P_VAR_RobotMachine_motionplanner = 2,
      P_VAR_RobotMachine_planexecutor = 3,
      P_VAR_RobotMachine_robotid = 4,
      _P_VARS_RobotMachine_COUNT = 5
    };

    enum P_VARS_Timer
    {
      P_VAR_Timer_client = 0,
      _P_VARS_Timer_COUNT = 1
    };

    void P_DTOR_DistributedMotionPlannerMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_DistributedTimeSyncMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_Main_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_PlanExecutorMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_RobotMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_DistributedMotionPlannerMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_DistributedTimeSyncMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_Main_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_PlanExecutorMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_RobotMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    PRT_VALUE *P_FUN_CancelTimer_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_PlanGenerator_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_GetGoalLocations_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_GetNumOfRobots_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_GetRobotInfo_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_Sleep_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_StartTimer_IMPL(PRT_MACHINEINST *context);

    #ifdef __cplusplus
      }
    #endif
  #endif
  