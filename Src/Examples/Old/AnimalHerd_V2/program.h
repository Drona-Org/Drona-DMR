
  #ifndef P_PROGRAM_H
    #define P_PROGRAM_H
    #include "PrtWinUser.h"
    #include "PrtExecution.h"
    enum P_EVENTS
    {
      _P_EVENT_NULL = 0,
      _P_EVENT_HALT = 1,
      P_EVENT_BatteryLow = 2,
      P_EVENT_CANCEL = 3,
      P_EVENT_CANCEL_FAILURE = 4,
      P_EVENT_CANCEL_SUCCESS = 5,
      P_EVENT_CancelOperation = 6,
      P_EVENT_CancelPlan = 7,
      P_EVENT_CancelSucess = 8,
      P_EVENT_CurrentState = 9,
      P_EVENT_EnvEventDetected = 10,
      P_EVENT_EnvState = 11,
      P_EVENT_ExecutePlan = 12,
      P_EVENT_FailureExecuting = 13,
      P_EVENT_FailureToComputePlan = 14,
      P_EVENT_GeneratePlanFor = 15,
      P_EVENT_GetEnv = 16,
      P_EVENT_GetRobotState = 17,
      P_EVENT_M_hCat = 18,
      P_EVENT_M_hDog = 19,
      P_EVENT_M_hMice = 20,
      P_EVENT_M_rCat = 21,
      P_EVENT_M_rDog = 22,
      P_EVENT_M_rMice = 23,
      P_EVENT_M_sCat = 24,
      P_EVENT_M_sDog = 25,
      P_EVENT_M_sMice = 26,
      P_EVENT_MotionPlanFor = 27,
      P_EVENT_ReDo = 28,
      P_EVENT_ReachedDestination = 29,
      P_EVENT_START = 30,
      P_EVENT_SetEnv = 31,
      P_EVENT_TIMEOUT = 32,
      P_EVENT_UNIT = 33,
      P_EVENT_UpdateRobotState = 34,
      P_EVENT_continueCurrentHerding = 35,
      P_EVENT_doScanning = 36,
      P_EVENT_done = 37,
      P_EVENT_infer = 38,
      P_EVENT_initial_setup = 39,
      P_EVENT_local = 40,
      P_EVENT_newPlan = 41,
      P_EVENT_startNewHerding = 42,
      P_EVENT_success = 43,
      _P_EVENTS_COUNT = 44
    };

    enum P_FUNS_DriverMachine
    {
      _P_FUN_DriverMachine_PUSH_OR_IGN = 0,
      _P_FUNS_DriverMachine_COUNT = 3,
      P_FUN_DriverMachine_ANON0 = 24,
      P_FUN_DriverMachine_ANON1 = 25
    };

    enum P_FUNS_MotionPlanExecutor
    {
      _P_FUN_MotionPlanExecutor_PUSH_OR_IGN = 0,
      _P_FUNS_MotionPlanExecutor_COUNT = 8,
      P_FUN_MotionPlanExecutor_ANON0 = 24,
      P_FUN_MotionPlanExecutor_ANON1 = 25,
      P_FUN_MotionPlanExecutor_ANON2 = 26,
      P_FUN_MotionPlanExecutor_ANON3 = 27,
      P_FUN_MotionPlanExecutor_ANON4 = 28,
      P_FUN_MotionPlanExecutor_ANON5 = 29,
      P_FUN_MotionPlanExecutor_GotoLocation = 30
    };

    enum P_FUNS_MotionPlanner
    {
      _P_FUN_MotionPlanner_PUSH_OR_IGN = 0,
      _P_FUNS_MotionPlanner_COUNT = 6,
      P_FUN_MotionPlanner_ANON0 = 24,
      P_FUN_MotionPlanner_ANON1 = 25,
      P_FUN_MotionPlanner_ComputeMotionPlanAndSend = 26,
      P_FUN_MotionPlanner_GetMotionPlan = 27,
      P_FUN_MotionPlanner_KillMotionPlanner = 28
    };

    enum P_FUNS_RobotStateManager
    {
      _P_FUN_RobotStateManager_PUSH_OR_IGN = 0,
      _P_FUNS_RobotStateManager_COUNT = 7,
      P_FUN_RobotStateManager_ANON0 = 24,
      P_FUN_RobotStateManager_ANON1 = 25,
      P_FUN_RobotStateManager_ANON2 = 26,
      P_FUN_RobotStateManager_ANON3 = 27,
      P_FUN_RobotStateManager_ANON4 = 28,
      P_FUN_RobotStateManager_ANON5 = 29
    };

    enum P_FUNS_RobotTaskPlanner
    {
      _P_FUN_RobotTaskPlanner_PUSH_OR_IGN = 0,
      _P_FUNS_RobotTaskPlanner_COUNT = 16,
      P_FUN_RobotTaskPlanner_ANON0 = 24,
      P_FUN_RobotTaskPlanner_ANON1 = 25,
      P_FUN_RobotTaskPlanner_ANON2 = 26,
      P_FUN_RobotTaskPlanner_ANON3 = 27,
      P_FUN_RobotTaskPlanner_ANON4 = 28,
      P_FUN_RobotTaskPlanner_ANON5 = 29,
      P_FUN_RobotTaskPlanner_ANON6 = 30,
      P_FUN_RobotTaskPlanner_ANON7 = 31,
      P_FUN_RobotTaskPlanner_ANON8 = 32,
      P_FUN_RobotTaskPlanner_ANON9 = 33,
      P_FUN_RobotTaskPlanner_ANON10 = 34,
      P_FUN_RobotTaskPlanner_ANON11 = 35,
      P_FUN_RobotTaskPlanner_CancelCurrentExecution = 36,
      P_FUN_RobotTaskPlanner_GetNextScanLocation = 37,
      P_FUN_RobotTaskPlanner_UpdateCurrentRobotState = 38
    };

    enum P_FUNS_SenseAndInfer
    {
      _P_FUN_SenseAndInfer_PUSH_OR_IGN = 0,
      _P_FUNS_SenseAndInfer_COUNT = 7,
      P_FUN_SenseAndInfer_ANON0 = 24,
      P_FUN_SenseAndInfer_ANON1 = 25,
      P_FUN_SenseAndInfer_ANON2 = 26,
      P_FUN_SenseAndInfer_ANON3 = 27,
      P_FUN_SenseAndInfer_ANON4 = 28,
      P_FUN_SenseAndInfer_InferCurrentStateAndInformTPorMP = 29
    };

    enum P_MACHINES
    {
      P_MACHINE_DriverMachine = 0,
      _P_MACHINE_MAIN = 0,
      P_MACHINE_MotionPlanExecutor = 1,
      P_MACHINE_MotionPlanner = 2,
      P_MACHINE_RobotStateManager = 3,
      P_MACHINE_RobotTaskPlanner = 4,
      P_MACHINE_SenseAndInfer = 5,
      _P_MACHINES_COUNT = 6
    };

    enum P_MODELS
    {
      P_MODEL_Environment = 0,
      P_MODEL_Timer = 1,
      _P_MODELS_COUNT = 2
    };

    enum P_STATES_DriverMachine
    {
      P_STATE_DriverMachine_Init = 0,
      _P_STATES_DriverMachine_COUNT = 1
    };

    enum P_STATES_Environment
    {
      _P_STATES_Environment_COUNT = 2
    };

    enum P_STATES_MotionPlanExecutor
    {
      P_STATE_MotionPlanExecutor_Init = 0,
      P_STATE_MotionPlanExecutor_StartExecutingPlan = 1,
      P_STATE_MotionPlanExecutor_WaitForCommands = 2,
      _P_STATES_MotionPlanExecutor_COUNT = 3
    };

    enum P_STATES_MotionPlanner
    {
      P_STATE_MotionPlanner_Init = 0,
      P_STATE_MotionPlanner_WaitForCommands = 1,
      _P_STATES_MotionPlanner_COUNT = 2
    };

    enum P_STATES_Prop_1
    {
      _P_STATES_Prop_1_COUNT = 1
    };

    enum P_STATES_Prop_10a
    {
      _P_STATES_Prop_10a_COUNT = 3
    };

    enum P_STATES_Prop_10b
    {
      _P_STATES_Prop_10b_COUNT = 3
    };

    enum P_STATES_Prop_10c
    {
      _P_STATES_Prop_10c_COUNT = 3
    };

    enum P_STATES_Prop_2
    {
      _P_STATES_Prop_2_COUNT = 1
    };

    enum P_STATES_Prop_3
    {
      _P_STATES_Prop_3_COUNT = 3
    };

    enum P_STATES_Prop_6
    {
      _P_STATES_Prop_6_COUNT = 3
    };

    enum P_STATES_Prop_7
    {
      _P_STATES_Prop_7_COUNT = 4
    };

    enum P_STATES_Prop_8
    {
      _P_STATES_Prop_8_COUNT = 4
    };

    enum P_STATES_Prop_9
    {
      _P_STATES_Prop_9_COUNT = 3
    };

    enum P_STATES_RobotStateManager
    {
      P_STATE_RobotStateManager_GetStateFromEnvMachine = 0,
      P_STATE_RobotStateManager_Init = 1,
      P_STATE_RobotStateManager_WaitForCommands = 2,
      _P_STATES_RobotStateManager_COUNT = 3
    };

    enum P_STATES_RobotTaskPlanner
    {
      P_STATE_RobotTaskPlanner_ExecutePlan = 0,
      P_STATE_RobotTaskPlanner_Init = 1,
      P_STATE_RobotTaskPlanner_LowBatteryDetected = 2,
      P_STATE_RobotTaskPlanner_ScanningModeOfOperation = 3,
      P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan = 4,
      P_STATE_RobotTaskPlanner_SetUpSystem = 5,
      P_STATE_RobotTaskPlanner_TakeActionOnEnvEventDetected = 6,
      _P_STATES_RobotTaskPlanner_COUNT = 7
    };

    enum P_STATES_SenseAndInfer
    {
      P_STATE_SenseAndInfer_Init = 0,
      P_STATE_SenseAndInfer_PeriodicallySenseUpdate = 1,
      P_STATE_SenseAndInfer_SenseEnvironment = 2,
      _P_STATES_SenseAndInfer_COUNT = 3
    };

    enum P_STATES_Timer
    {
      _P_STATES_Timer_COUNT = 3
    };

    enum P_VARS_DriverMachine
    {
      P_VAR_DriverMachine_envMachine = 0,
      P_VAR_DriverMachine_robot = 1,
      P_VAR_DriverMachine_robotStMng = 2,
      _P_VARS_DriverMachine_COUNT = 3
    };

    enum P_VARS_Environment
    {
      _P_VARS_Environment_COUNT = 1
    };

    enum P_VARS_MotionPlanExecutor
    {
      P_VAR_MotionPlanExecutor_RState = 0,
      P_VAR_MotionPlanExecutor_RobotTP = 1,
      P_VAR_MotionPlanExecutor_currentLocation = 2,
      P_VAR_MotionPlanExecutor_currentPlan = 3,
      _P_VARS_MotionPlanExecutor_COUNT = 4
    };

    enum P_VARS_MotionPlanner
    {
      P_VAR_MotionPlanner_AllMotionPlans = 0,
      P_VAR_MotionPlanner_Obstacles = 1,
      P_VAR_MotionPlanner_RobotTP = 2,
      _P_VARS_MotionPlanner_COUNT = 3
    };

    enum P_VARS_Prop_1
    {
      _P_VARS_Prop_1_COUNT = 2
    };

    enum P_VARS_Prop_10a
    {
      _P_VARS_Prop_10a_COUNT = 0
    };

    enum P_VARS_Prop_10b
    {
      _P_VARS_Prop_10b_COUNT = 0
    };

    enum P_VARS_Prop_10c
    {
      _P_VARS_Prop_10c_COUNT = 0
    };

    enum P_VARS_Prop_2
    {
      _P_VARS_Prop_2_COUNT = 2
    };

    enum P_VARS_Prop_3
    {
      _P_VARS_Prop_3_COUNT = 1
    };

    enum P_VARS_Prop_6
    {
      _P_VARS_Prop_6_COUNT = 1
    };

    enum P_VARS_Prop_7
    {
      _P_VARS_Prop_7_COUNT = 0
    };

    enum P_VARS_Prop_8
    {
      _P_VARS_Prop_8_COUNT = 0
    };

    enum P_VARS_Prop_9
    {
      _P_VARS_Prop_9_COUNT = 2
    };

    enum P_VARS_RobotStateManager
    {
      P_VAR_RobotStateManager_EnvMachine = 0,
      P_VAR_RobotStateManager_batteryLevel = 1,
      P_VAR_RobotStateManager_currentLocation = 2,
      P_VAR_RobotStateManager_sensingMachine = 3,
      _P_VARS_RobotStateManager_COUNT = 4
    };

    enum P_VARS_RobotTaskPlanner
    {
      P_VAR_RobotTaskPlanner_currentRobotState = 0,
      P_VAR_RobotTaskPlanner_currentSensorState = 1,
      P_VAR_RobotTaskPlanner_envMachine = 2,
      P_VAR_RobotTaskPlanner_herdingState = 3,
      P_VAR_RobotTaskPlanner_herdingTogether = 4,
      P_VAR_RobotTaskPlanner_motionPlanEx = 5,
      P_VAR_RobotTaskPlanner_motionPlanner = 6,
      P_VAR_RobotTaskPlanner_nextLocation = 7,
      P_VAR_RobotTaskPlanner_robotStMng = 8,
      P_VAR_RobotTaskPlanner_scanLocations = 9,
      P_VAR_RobotTaskPlanner_senseInfer = 10,
      _P_VARS_RobotTaskPlanner_COUNT = 11
    };

    enum P_VARS_SenseAndInfer
    {
      P_VAR_SenseAndInfer_currentRobotState = 0,
      P_VAR_SenseAndInfer_robotStManager = 1,
      P_VAR_SenseAndInfer_robotTP = 2,
      _P_VARS_SenseAndInfer_COUNT = 3
    };

    enum P_VARS_Timer
    {
      _P_VARS_Timer_COUNT = 1
    };

    PRT_VALUE *P_FUN_AddObstacle_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_GetPath_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_InitializeMotionPlanning_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_InitializeObstacles_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_InvokeMotionPlanner_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_MotionPlanExecutor_GotoLocation_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_MotionPlanner_GetMotionPlan_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_MotionPlanner_KillMotionPlanner_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_PRINT_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_ResetObstacle_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_Seal_IMPL(PRT_MACHINEINST *context);

    PRT_VALUE *P_FUN_Unseal_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_DriverMachine_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_MotionPlanExecutor_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_MotionPlanner_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_RobotStateManager_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_RobotTaskPlanner_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_SenseAndInfer_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_DriverMachine_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_MotionPlanExecutor_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_MotionPlanner_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_RobotStateManager_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_RobotTaskPlanner_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_SenseAndInfer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_DTOR_Environment_IMPL(PRT_MACHINEINST *context);

    void P_DTOR_Timer_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_Environment_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_CTOR_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    void P_SEND_Environment_IMPL(PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload);

    void P_SEND_Timer_IMPL(PRT_MACHINEINST *context, PRT_VALUE *evnt, PRT_VALUE *payload);

    PRT_PROGRAMDECL P_GEND_PROGRAM;
  #endif
  