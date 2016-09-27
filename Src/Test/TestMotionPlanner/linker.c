
  #include "linker.h"
  PRT_TYPE P_GEND_TYPE_0 = 
  {
    PRT_KIND_ANY,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_1 = 
  {
    PRT_KIND_BOOL,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_2 = 
  {
    PRT_KIND_EVENT,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_3 = 
  {
    PRT_KIND_INT,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_4 = 
  {
    PRT_KIND_MACHINE,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_5 = 
  {
    PRT_KIND_NULL,
    
    {
        NULL
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_6[] = 
  {
    "robot"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_6[] = 
  {
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_6 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_6,
    P_GEND_TYPE_NMDTUP_TARR_6
  };
  PRT_TYPE P_GEND_TYPE_6 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_6
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_7[] = 
  {
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_7[] = 
  {
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_7 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_7,
    P_GEND_TYPE_NMDTUP_TARR_7
  };
  PRT_TYPE P_GEND_TYPE_7 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_7
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_8[] = 
  {
    "startpos"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_8[] = 
  {
    &P_GEND_TYPE_3
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_8 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_8,
    P_GEND_TYPE_NMDTUP_TARR_8
  };
  PRT_TYPE P_GEND_TYPE_8 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_8
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_9[] = 
  {
    "timesync"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_9[] = 
  {
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_9 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_9,
    P_GEND_TYPE_NMDTUP_TARR_9
  };
  PRT_TYPE P_GEND_TYPE_9 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_9
    }
  };
  PRT_SEQTYPE P_GEND_TYPE_SEQ_10 = 
  {
    &P_GEND_TYPE_4
  };
  PRT_TYPE P_GEND_TYPE_10 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_10
    }
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_11[] = 
  {
    &P_GEND_TYPE_3
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_11 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_11
  };
  PRT_TYPE P_GEND_TYPE_11 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_11
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_12[] = 
  {
    "g",
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_12[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_12 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_12,
    P_GEND_TYPE_NMDTUP_TARR_12
  };
  PRT_TYPE P_GEND_TYPE_12 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_12
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_13[] = 
  {
    "priority",
    "robot"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_13[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_13 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_13,
    P_GEND_TYPE_NMDTUP_TARR_13
  };
  PRT_TYPE P_GEND_TYPE_13 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_13
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_14[] = 
  {
    "robotid",
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_14[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_14 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_14,
    P_GEND_TYPE_NMDTUP_TARR_14
  };
  PRT_TYPE P_GEND_TYPE_14 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_14
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_15[] = 
  {
    "robotid",
    "startpos"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_15[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_15 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_15,
    P_GEND_TYPE_NMDTUP_TARR_15
  };
  PRT_TYPE P_GEND_TYPE_15 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_15
    }
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_16[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_16 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_16
  };
  PRT_TYPE P_GEND_TYPE_16 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_16
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_17[] = 
  {
    "allrobots",
    "timesync"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_17[] = 
  {
    &P_GEND_TYPE_10,
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_17 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_17,
    P_GEND_TYPE_NMDTUP_TARR_17
  };
  PRT_TYPE P_GEND_TYPE_17 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_17
    }
  };
  PRT_SEQTYPE P_GEND_TYPE_SEQ_18 = 
  {
    &P_GEND_TYPE_16
  };
  PRT_TYPE P_GEND_TYPE_18 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_18
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_19[] = 
  {
    "currTraj"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_19[] = 
  {
    &P_GEND_TYPE_18
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_19 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_19,
    P_GEND_TYPE_NMDTUP_TARR_19
  };
  PRT_TYPE P_GEND_TYPE_19 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_19
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_20[] = 
  {
    "robot",
    "currTraj"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_20[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_18
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_20 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_20,
    P_GEND_TYPE_NMDTUP_TARR_20
  };
  PRT_TYPE P_GEND_TYPE_20 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_20
    }
  };
  PRT_TYPE *P_GEND_TYPE_RobotInfoType = &P_GEND_TYPE_15;
  PRT_TYPE *P_GEND_TYPE_TaskType = &P_GEND_TYPE_12;
  PRT_TYPE *P_GEND_TYPE_TimedTrajType = &P_GEND_TYPE_18;
  PRT_EVENTDECL P_GEND_EVENTS[] = 
  {
    
    {
        _P_EVENT_NULL,
        "null",
        0U,
        &P_GEND_TYPE_5,
        0U,
        NULL
    },
    
    {
        _P_EVENT_HALT,
        "halt",
        4294967295U,
        &P_GEND_TYPE_0,
        0U,
        NULL
    },
    
    {
        P_EVENT_CANCEL,
        "CANCEL",
        4294967295U,
        &P_GEND_TYPE_5,
        0U,
        NULL
    },
    
    {
        P_EVENT_CANCEL_FAILURE,
        "CANCEL_FAILURE",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_CANCEL_SUCCESS,
        "CANCEL_SUCCESS",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_START,
        "START",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_TIMEOUT,
        "TIMEOUT",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_UNIT,
        "UNIT",
        4294967295U,
        &P_GEND_TYPE_5,
        0U,
        NULL
    },
    
    {
        P_EVENT_eAllRobots,
        "eAllRobots",
        4294967295U,
        &P_GEND_TYPE_17,
        0U,
        NULL
    },
    
    {
        P_EVENT_eCurrTimePeriod,
        "eCurrTimePeriod",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_eCurrentTraj,
        "eCurrentTraj",
        4294967295U,
        &P_GEND_TYPE_20,
        0U,
        NULL
    },
    
    {
        P_EVENT_eDistMotionPlanMachine,
        "eDistMotionPlanMachine",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_eGetTimePeriod,
        "eGetTimePeriod",
        4294967295U,
        &P_GEND_TYPE_14,
        0U,
        NULL
    },
    
    {
        P_EVENT_eNewTask,
        "eNewTask",
        4294967295U,
        &P_GEND_TYPE_12,
        0U,
        NULL
    },
    
    {
        P_EVENT_ePlanCompletion,
        "ePlanCompletion",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_ePlanExecutorMachine,
        "ePlanExecutorMachine",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_eRequestCurrentTraj,
        "eRequestCurrentTraj",
        4294967295U,
        &P_GEND_TYPE_13,
        0U,
        NULL
    },
    
    {
        P_EVENT_eStartExecutingPlan,
        "eStartExecutingPlan",
        4294967295U,
        &P_GEND_TYPE_18,
        0U,
        NULL
    },
    
    {
        P_EVENT_eTask_completed,
        "eTask_completed",
        4294967295U,
        &P_GEND_TYPE_5,
        0U,
        NULL
    },
    
    {
        P_EVENT_eTimeSyncId,
        "eTimeSyncId",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_UINT32 P_GEND_EVENTSET_0[] = 
  {
    0x0U
  };
  PRT_UINT32 P_GEND_EVENTSET_1[] = 
  {
    0x24U
  };
  PRT_UINT32 P_GEND_EVENTSET_10[] = 
  {
    0x2000U
  };
  PRT_UINT32 P_GEND_EVENTSET_11[] = 
  {
    0x6000U
  };
  PRT_UINT32 P_GEND_EVENTSET_12[] = 
  {
    0x12000U
  };
  PRT_UINT32 P_GEND_EVENTSET_13[] = 
  {
    0x14000U
  };
  PRT_UINT32 P_GEND_EVENTSET_14[] = 
  {
    0x08000U
  };
  PRT_UINT32 P_GEND_EVENTSET_15[] = 
  {
    0x10000U
  };
  PRT_UINT32 P_GEND_EVENTSET_16[] = 
  {
    0x20000U
  };
  PRT_UINT32 P_GEND_EVENTSET_17[] = 
  {
    0x40000U
  };
  PRT_UINT32 P_GEND_EVENTSET_18[] = 
  {
    0x080000U
  };
  PRT_UINT32 P_GEND_EVENTSET_19[] = 
  {
    0x1U
  };
  PRT_UINT32 P_GEND_EVENTSET_2[] = 
  {
    0x5U
  };
  PRT_UINT32 P_GEND_EVENTSET_3[] = 
  {
    0x20U
  };
  PRT_UINT32 P_GEND_EVENTSET_4[] = 
  {
    0x1040U
  };
  PRT_UINT32 P_GEND_EVENTSET_5[] = 
  {
    0x080U
  };
  PRT_UINT32 P_GEND_EVENTSET_6[] = 
  {
    0x2900U
  };
  PRT_UINT32 P_GEND_EVENTSET_7[] = 
  {
    0x200U
  };
  PRT_UINT32 P_GEND_EVENTSET_8[] = 
  {
    0x10400U
  };
  PRT_UINT32 P_GEND_EVENTSET_9[] = 
  {
    0x0800U
  };
  PRT_EVENTSETDECL P_GEND_EVENTSETS[] = 
  {
    
    {
        0,
        P_GEND_EVENTSET_0
    },
    
    {
        1,
        P_GEND_EVENTSET_1
    },
    
    {
        2,
        P_GEND_EVENTSET_2
    },
    
    {
        3,
        P_GEND_EVENTSET_3
    },
    
    {
        4,
        P_GEND_EVENTSET_4
    },
    
    {
        5,
        P_GEND_EVENTSET_5
    },
    
    {
        6,
        P_GEND_EVENTSET_6
    },
    
    {
        7,
        P_GEND_EVENTSET_7
    },
    
    {
        8,
        P_GEND_EVENTSET_8
    },
    
    {
        9,
        P_GEND_EVENTSET_9
    },
    
    {
        10,
        P_GEND_EVENTSET_10
    },
    
    {
        11,
        P_GEND_EVENTSET_11
    },
    
    {
        12,
        P_GEND_EVENTSET_12
    },
    
    {
        13,
        P_GEND_EVENTSET_13
    },
    
    {
        14,
        P_GEND_EVENTSET_14
    },
    
    {
        15,
        P_GEND_EVENTSET_15
    },
    
    {
        16,
        P_GEND_EVENTSET_16
    },
    
    {
        17,
        P_GEND_EVENTSET_17
    },
    
    {
        18,
        P_GEND_EVENTSET_18
    },
    
    {
        19,
        P_GEND_EVENTSET_19
    }
  };
  PRT_MACHINEDECL *P_GEND_MACHINES[] = 
  {
    &P_MACHINE_STRUCT_DistributedMotionPlannerMachine,
    &P_MACHINE_STRUCT_DistributedTimeSyncMachine,
    &P_MACHINE_STRUCT_Main,
    &P_MACHINE_STRUCT_PlanExecutorMachine,
    &P_MACHINE_STRUCT_RobotMachine,
    &P_MACHINE_STRUCT_Timer
  };
  PRT_PROGRAMDECL P_GEND_PROGRAM = 
  {
    20U,
    20U,
    6U,
    0U,
    P_GEND_EVENTS,
    P_GEND_EVENTSETS,
    P_GEND_MACHINES,
    NULL,
    0U,
    NULL
  };
  