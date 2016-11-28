
  #include "test.h"
  #define P_SEQ
  #define P_STMT_1(s, x1, f1, x0, f0) P_SEQ(p_tmp_stmt_0 = (x0), p_tmp_stmt_1 = (x1), (s), ((f0) ? PrtFreeValue(p_tmp_stmt_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_stmt_1) : 0U))
  #define P_STMT_2(s, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_stmt_0 = (x0), p_tmp_stmt_1 = (x1), p_tmp_stmt_2 = (x2), (s), ((f0) ? PrtFreeValue(p_tmp_stmt_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_stmt_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_stmt_2) : 0U))
  #define P_BOOL_EXPR(x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_bool = PrtPrimGetBool(p_tmp_expr_0), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), p_tmp_bool)
  #define P_EXPR_0(x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_0)
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
    PRT_KIND_NULL,
    
    {
        NULL
    }
  };
  PRT_TYPE P_GEND_TYPE_5 = 
  {
    PRT_KIND_MACHINE,
    
    {
        NULL
    }
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_6[] = 
  {
    "_payload_0"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_6[] = 
  {
    &P_GEND_TYPE_0
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
    "_payload_1"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_7[] = 
  {
    &P_GEND_TYPE_0
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
    "_payload_2"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_8[] = 
  {
    &P_GEND_TYPE_0
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
    "_payload_skip"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_9[] = 
  {
    &P_GEND_TYPE_0
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
  PRT_VALUE P_GEND_VALUE_0 = 
  {
    PRT_VALKIND_EVENT,
    
    {
        P_EVENT_PING
    }
  };
  PRT_VALUE P_GEND_VALUE_1 = 
  {
    PRT_VALKIND_EVENT,
    
    {
        P_EVENT_PONG
    }
  };
  PRT_VALUE P_GEND_VALUE_2 = 
  {
    PRT_VALKIND_EVENT,
    
    {
        P_EVENT_SUCCESS
    }
  };
  PRT_VALUE P_GEND_VALUE_3 = 
  {
    PRT_VALKIND_EVENT,
    
    {
        PRT_SPECIAL_EVENT_HALT
    }
  };
  PRT_VALUE P_GEND_VALUE_4 = 
  {
    PRT_VALKIND_NULL,
    
    {
        PRT_SPECIAL_EVENT_NULL
    }
  };
  PRT_EVENTDECL P_GEND_EVENTS[] = 
  {
    
    {
        _P_EVENT_NULL,
        "null",
        0U,
        &P_GEND_TYPE_4,
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
        P_EVENT_PING,
        "PING",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_PONG,
        "PONG",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_EVENT_SUCCESS,
        "SUCCESS",
        4294967295U,
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Client_Init[] = 
  {
    
    {
        0,
        P_STATE_Client_Init,
        P_MACHINE_Client,
        P_EVENT_SUCCESS,
        P_STATE_Client_SendPing,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Client_SendPing[] = 
  {
    
    {
        0,
        P_STATE_Client_SendPing,
        P_MACHINE_Client,
        P_EVENT_SUCCESS,
        P_STATE_Client_WaitPing,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Client_SendPong[] = 
  {
    
    {
        0,
        P_STATE_Client_SendPong,
        P_MACHINE_Client,
        P_EVENT_SUCCESS,
        P_STATE_Client_WaitPong,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Client_WaitPing[] = 
  {
    
    {
        0,
        P_STATE_Client_WaitPing,
        P_MACHINE_Client,
        P_EVENT_PING,
        P_STATE_Client_SendPong,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Client_WaitPong[] = 
  {
    
    {
        0,
        P_STATE_Client_WaitPong,
        P_MACHINE_Client,
        P_EVENT_PONG,
        P_STATE_Client_SendPing,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  static PRT_VALUE *P_FUN_Client_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_ret;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Client_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    #line 9 "file:///e:/px4/src/firmware/src/examples/px4_pingpong/test.p"
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      #line 9
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      #line 9
      p_tmp_ret = NULL;
      #line 9
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      #line 10
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_4, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_2, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      #line 11
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      #line 11
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Client_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    #line 15 "file:///e:/px4/src/firmware/src/examples/px4_pingpong/test.p"
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      #line 15
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      #line 15
      p_tmp_ret = NULL;
      #line 15
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      #line 16
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), &P_GEND_VALUE_4, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_0, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE);
      #line 17
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_4, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_2, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      #line 18
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      #line 18
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Client_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    #line 25 "file:///e:/px4/src/firmware/src/examples/px4_pingpong/test.p"
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      #line 25
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      #line 25
      p_tmp_ret = NULL;
      #line 25
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      #line 26
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), &P_GEND_VALUE_4, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_1, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE);
      #line 27
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_4, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_2, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      #line 28
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      #line 28
      return p_tmp_ret;
    }
  }

  PRT_UINT32 P_GEND_EVENTSET_0[] = 
  {
    0x0U
  };
  PRT_UINT32 P_GEND_EVENTSET_1[] = 
  {
    0x4U
  };
  PRT_UINT32 P_GEND_EVENTSET_2[] = 
  {
    0x08U
  };
  PRT_UINT32 P_GEND_EVENTSET_3[] = 
  {
    0x10U
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
    }
  };
  PRT_FUNDECL P_GEND_FUNS_Client[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_Client,
        NULL,
        NULL,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Client_ANON0,
        P_MACHINE_Client,
        NULL,
        &P_FUN_Client_ANON0_IMPL,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Client_ANON1,
        P_MACHINE_Client,
        NULL,
        &P_FUN_Client_ANON1_IMPL,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Client_ANON2,
        P_MACHINE_Client,
        NULL,
        &P_FUN_Client_ANON2_IMPL,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Client_ANON3,
        P_MACHINE_Client,
        NULL,
        &P_FUN_Client_ANON3_IMPL,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_Client[] = 
  {
    
    {
        P_STATE_Client_Init,
        P_MACHINE_Client,
        "Init",
        1,
        0,
        0,
        3,
        0,
        P_GEND_TRANS_Client_Init,
        NULL,
        P_FUN_Client_ANON1,
        P_FUN_Client_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_Client_SendPing,
        P_MACHINE_Client,
        "SendPing",
        1,
        0,
        0,
        3,
        0,
        P_GEND_TRANS_Client_SendPing,
        NULL,
        P_FUN_Client_ANON2,
        P_FUN_Client_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_Client_SendPong,
        P_MACHINE_Client,
        "SendPong",
        1,
        0,
        0,
        3,
        0,
        P_GEND_TRANS_Client_SendPong,
        NULL,
        P_FUN_Client_ANON3,
        P_FUN_Client_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_Client_WaitPing,
        P_MACHINE_Client,
        "WaitPing",
        1,
        0,
        0,
        1,
        0,
        P_GEND_TRANS_Client_WaitPing,
        NULL,
        P_FUN_Client_ANON0,
        P_FUN_Client_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_Client_WaitPong,
        P_MACHINE_Client,
        "WaitPong",
        1,
        0,
        0,
        2,
        0,
        P_GEND_TRANS_Client_WaitPong,
        NULL,
        P_FUN_Client_ANON0,
        P_FUN_Client_ANON0,
        0U,
        NULL
    }
  };
  PRT_MACHINEDECL P_GEND_MACHINES[] = 
  {
    
    {
        P_MACHINE_Client,
        "Client",
        0,
        5,
        5,
        4294967295,
        P_STATE_Client_Init,
        NULL,
        P_GEND_STATES_Client,
        P_GEND_FUNS_Client,
        &P_CTOR_Client_IMPL,
        &P_DTOR_Client_IMPL,
        0U,
        NULL
    }
  };
  PRT_PROGRAMDECL P_GEND_PROGRAM = 
  {
    5U,
    4U,
    1U,
    0U,
    0U,
    P_GEND_EVENTS,
    P_GEND_EVENTSETS,
    P_GEND_MACHINES,
    NULL,
    NULL,
    0U,
    NULL
  };
  