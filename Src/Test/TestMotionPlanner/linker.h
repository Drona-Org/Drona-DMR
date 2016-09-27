
  #ifndef P_LINKER_H
    #define P_LINKER_H
    #include "PrtUser.h"
    #include "PrtExecution.h"
    #ifdef __cplusplus
      extern "C"{
    #endif
    enum P_EVENTS
    {
      _P_EVENT_NULL = 0,
      _P_EVENT_HALT = 1,
      P_EVENT_CANCEL = 2,
      P_EVENT_CANCEL_FAILURE = 3,
      P_EVENT_CANCEL_SUCCESS = 4,
      P_EVENT_START = 5,
      P_EVENT_TIMEOUT = 6,
      P_EVENT_UNIT = 7,
      P_EVENT_eAllRobots = 8,
      P_EVENT_eCurrTimePeriod = 9,
      P_EVENT_eCurrentTraj = 10,
      P_EVENT_eDistMotionPlanMachine = 11,
      P_EVENT_eGetTimePeriod = 12,
      P_EVENT_eNewTask = 13,
      P_EVENT_ePlanCompletion = 14,
      P_EVENT_ePlanExecutorMachine = 15,
      P_EVENT_eRequestCurrentTraj = 16,
      P_EVENT_eStartExecutingPlan = 17,
      P_EVENT_eTask_completed = 18,
      P_EVENT_eTimeSyncId = 19,
      _P_EVENTS_COUNT = 20
    };

    enum P_EVENTSET
    {
      P_GEND_EVENTSET_ = 0,
      P_GEND_EVENTSET_CANCELSTART = 1,
      P_GEND_EVENTSET_CANCELnull = 2,
      P_GEND_EVENTSET_START = 3,
      P_GEND_EVENTSET_TIMEOUTeGetTimePeriod = 4,
      P_GEND_EVENTSET_UNIT = 5,
      P_GEND_EVENTSET_eAllRobotseDistMotionPlanMachineeNewTask = 6,
      P_GEND_EVENTSET_eCurrTimePeriod = 7,
      P_GEND_EVENTSET_eCurrentTrajeRequestCurrentTraj = 8,
      P_GEND_EVENTSET_eDistMotionPlanMachine = 9,
      P_GEND_EVENTSET_eNewTask = 10,
      P_GEND_EVENTSET_eNewTaskePlanCompletion = 11,
      P_GEND_EVENTSET_eNewTaskeRequestCurrentTraj = 12,
      P_GEND_EVENTSET_ePlanCompletioneRequestCurrentTraj = 13,
      P_GEND_EVENTSET_ePlanExecutorMachine = 14,
      P_GEND_EVENTSET_eRequestCurrentTraj = 15,
      P_GEND_EVENTSET_eStartExecutingPlan = 16,
      P_GEND_EVENTSET_eTask_completed = 17,
      P_GEND_EVENTSET_eTimeSyncId = 18,
      P_GEND_EVENTSET_null = 19,
      _P_EVENTSETS_COUNT = 20
    };

    enum P_FIELD_INDEX_RobotInfoType
    {
      P_FIELD_INDEX_RobotInfoType_robotid = 0,
      P_FIELD_INDEX_RobotInfoType_startpos = 1,
      _P_FIELD_INDEX_RobotInfoType_COUNT = 2
    };

    enum P_FIELD_INDEX_TaskType
    {
      P_FIELD_INDEX_TaskType_taskid = 0,
      P_FIELD_INDEX_TaskType_g = 1,
      P_FIELD_INDEX_TaskType_source = 2,
      _P_FIELD_INDEX_TaskType_COUNT = 3
    };

    enum P_FORGN_TYPES
    {
      _P_FORGN_TYPES_COUNT = 0
    };

    enum P_MACHINES
    {
      P_MACHINE_DistributedMotionPlannerMachine = 0,
      P_MACHINE_DistributedTimeSyncMachine = 1,
      P_MACHINE_Main = 2,
      P_MACHINE_PlanExecutorMachine = 3,
      P_MACHINE_RobotMachine = 4,
      P_MACHINE_Timer = 5,
      _P_MACHINES_COUNT = 6
    };

    extern PRT_MACHINEDECL P_MACHINE_STRUCT_DistributedMotionPlannerMachine;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_DistributedTimeSyncMachine;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_Main;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_PlanExecutorMachine;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_RobotMachine;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_Timer;
    extern PRT_PROGRAMDECL P_GEND_PROGRAM;
    extern PRT_TYPE *P_GEND_TYPE_RobotInfoType;
    extern PRT_TYPE *P_GEND_TYPE_TaskType;
    extern PRT_TYPE *P_GEND_TYPE_TimedTrajType;
    #ifdef __cplusplus
      }
    #endif
  #endif
  