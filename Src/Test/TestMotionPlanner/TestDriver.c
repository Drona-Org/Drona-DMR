
  #include "TestDriver.h"
  #define P_SEQ
  #define P_STMT_0(s, x0, f0) P_SEQ(p_tmp_stmt_0 = (x0), (s), ((f0) ? PrtFreeValue(p_tmp_stmt_0) : 0U))
  #define P_STMT_1(s, x1, f1, x0, f0) P_SEQ(p_tmp_stmt_0 = (x0), p_tmp_stmt_1 = (x1), (s), ((f0) ? PrtFreeValue(p_tmp_stmt_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_stmt_1) : 0U))
  #define P_STMT_2(s, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_stmt_0 = (x0), p_tmp_stmt_1 = (x1), p_tmp_stmt_2 = (x2), (s), ((f0) ? PrtFreeValue(p_tmp_stmt_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_stmt_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_stmt_2) : 0U))
  #define P_BOOL_EXPR(x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_bool = PrtPrimGetBool(p_tmp_expr_0), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), p_tmp_bool)
  #define P_EXPR_0(x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_0)
  #define P_EXPR_1(x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), p_tmp_expr_1)
  #define P_EXPR_2(x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), p_tmp_expr_2)
  #define P_EXPR_3(x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), p_tmp_expr_3)
  #define P_EXPR_4(x4, f4, x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), p_tmp_expr_4 = (x4), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), ((f3) ? PrtFreeValue(p_tmp_expr_3) : 0U), p_tmp_expr_4)
  #define P_EXPR_5(x5, f5, x4, f4, x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), p_tmp_expr_4 = (x4), p_tmp_expr_5 = (x5), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), ((f3) ? PrtFreeValue(p_tmp_expr_3) : 0U), ((f4) ? PrtFreeValue(p_tmp_expr_4) : 0U), p_tmp_expr_5)
  #define P_EXPR_6(x6, f6, x5, f5, x4, f4, x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), p_tmp_expr_4 = (x4), p_tmp_expr_5 = (x5), p_tmp_expr_6 = (x6), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), ((f3) ? PrtFreeValue(p_tmp_expr_3) : 0U), ((f4) ? PrtFreeValue(p_tmp_expr_4) : 0U), ((f5) ? PrtFreeValue(p_tmp_expr_5) : 0U), p_tmp_expr_6)
  #define P_EXPR_7(x7, f7, x6, f6, x5, f5, x4, f4, x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), p_tmp_expr_4 = (x4), p_tmp_expr_5 = (x5), p_tmp_expr_6 = (x6), p_tmp_expr_7 = (x7), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), ((f3) ? PrtFreeValue(p_tmp_expr_3) : 0U), ((f4) ? PrtFreeValue(p_tmp_expr_4) : 0U), ((f5) ? PrtFreeValue(p_tmp_expr_5) : 0U), ((f6) ? PrtFreeValue(p_tmp_expr_6) : 0U), p_tmp_expr_7)
  #define P_TUPLE_0(t, x0) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), p_tmp_tuple)
  #define P_TUPLE_1(t, x0, x1) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), PrtTupleSet(p_tmp_tuple, 1U, (x1)), p_tmp_tuple)
  #define P_TUPLE_2(t, x0, x1, x2) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), PrtTupleSet(p_tmp_tuple, 1U, (x1)), PrtTupleSet(p_tmp_tuple, 2U, (x2)), p_tmp_tuple)
  #define P_TUPLE_3(t, x0, x1, x2, x3) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), PrtTupleSet(p_tmp_tuple, 1U, (x1)), PrtTupleSet(p_tmp_tuple, 2U, (x2)), PrtTupleSet(p_tmp_tuple, 3U, (x3)), p_tmp_tuple)
  static PRT_TYPE P_GEND_TYPE_0 = 
  {
    PRT_KIND_ANY,
    
    {
        NULL
    }
  };
  static PRT_TYPE P_GEND_TYPE_1 = 
  {
    PRT_KIND_BOOL,
    
    {
        NULL
    }
  };
  static PRT_TYPE P_GEND_TYPE_2 = 
  {
    PRT_KIND_EVENT,
    
    {
        NULL
    }
  };
  static PRT_TYPE P_GEND_TYPE_3 = 
  {
    PRT_KIND_INT,
    
    {
        NULL
    }
  };
  static PRT_TYPE P_GEND_TYPE_4 = 
  {
    PRT_KIND_MACHINE,
    
    {
        NULL
    }
  };
  static PRT_TYPE P_GEND_TYPE_5 = 
  {
    PRT_KIND_NULL,
    
    {
        NULL
    }
  };
  static PRT_MAPTYPE P_GEND_TYPE_MAP_6 = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_TYPE P_GEND_TYPE_6 = 
  {
    PRT_KIND_MAP,
    
    {
        &P_GEND_TYPE_MAP_6
    }
  };
  static PRT_MAPTYPE P_GEND_TYPE_MAP_7 = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_1
  };
  static PRT_TYPE P_GEND_TYPE_7 = 
  {
    PRT_KIND_MAP,
    
    {
        &P_GEND_TYPE_MAP_7
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_8[] = 
  {
    "_payload_0"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_8[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_8 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_8,
    P_GEND_TYPE_NMDTUP_TARR_8
  };
  static PRT_TYPE P_GEND_TYPE_8 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_8
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_9[] = 
  {
    "_payload_1"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_9[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_9 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_9,
    P_GEND_TYPE_NMDTUP_TARR_9
  };
  static PRT_TYPE P_GEND_TYPE_9 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_9
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_10[] = 
  {
    "_payload_2"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_10[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_10 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_10,
    P_GEND_TYPE_NMDTUP_TARR_10
  };
  static PRT_TYPE P_GEND_TYPE_10 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_10
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_11[] = 
  {
    "_payload_3"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_11[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_11 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_11,
    P_GEND_TYPE_NMDTUP_TARR_11
  };
  static PRT_TYPE P_GEND_TYPE_11 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_11
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_12[] = 
  {
    "_payload_skip"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_12[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_12 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_12,
    P_GEND_TYPE_NMDTUP_TARR_12
  };
  static PRT_TYPE P_GEND_TYPE_12 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_12
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_13[] = 
  {
    "expectedEndTime"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_13[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_13 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_13,
    P_GEND_TYPE_NMDTUP_TARR_13
  };
  static PRT_TYPE P_GEND_TYPE_13 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_13
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_14[] = 
  {
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_14[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_14 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_14,
    P_GEND_TYPE_NMDTUP_TARR_14
  };
  static PRT_TYPE P_GEND_TYPE_14 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_14
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_15[] = 
  {
    "nextRobot"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_15[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_15 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_15,
    P_GEND_TYPE_NMDTUP_TARR_15
  };
  static PRT_TYPE P_GEND_TYPE_15 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_15
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_16[] = 
  {
    "noOfRobots"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_16[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_16 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_16,
    P_GEND_TYPE_NMDTUP_TARR_16
  };
  static PRT_TYPE P_GEND_TYPE_16 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_16
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_17[] = 
  {
    "owner"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_17[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_17 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_17,
    P_GEND_TYPE_NMDTUP_TARR_17
  };
  static PRT_TYPE P_GEND_TYPE_17 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_17
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_18[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_18[] = 
  {
    &P_GEND_TYPE_0
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_18 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_18,
    P_GEND_TYPE_NMDTUP_TARR_18
  };
  static PRT_TYPE P_GEND_TYPE_18 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_18
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_19[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_19[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_19 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_19,
    P_GEND_TYPE_NMDTUP_TARR_19
  };
  static PRT_TYPE P_GEND_TYPE_19 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_19
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_20[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_20[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_20 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_20,
    P_GEND_TYPE_NMDTUP_TARR_20
  };
  static PRT_TYPE P_GEND_TYPE_20 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_20
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_21[] = 
  {
    "retVal"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_21[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_21 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_21,
    P_GEND_TYPE_NMDTUP_TARR_21
  };
  static PRT_TYPE P_GEND_TYPE_21 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_21
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_22[] = 
  {
    "rid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_22[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_22 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_22,
    P_GEND_TYPE_NMDTUP_TARR_22
  };
  static PRT_TYPE P_GEND_TYPE_22 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_22
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_23[] = 
  {
    "robot"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_23[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_23 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_23,
    P_GEND_TYPE_NMDTUP_TARR_23
  };
  static PRT_TYPE P_GEND_TYPE_23 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_23
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_24[] = 
  {
    "robotId"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_24[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_24 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_24,
    P_GEND_TYPE_NMDTUP_TARR_24
  };
  static PRT_TYPE P_GEND_TYPE_24 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_24
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_25[] = 
  {
    "robotid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_25[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_25 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_25,
    P_GEND_TYPE_NMDTUP_TARR_25
  };
  static PRT_TYPE P_GEND_TYPE_25 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_25
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_26[] = 
  {
    "s"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_26[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_26 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_26,
    P_GEND_TYPE_NMDTUP_TARR_26
  };
  static PRT_TYPE P_GEND_TYPE_26 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_26
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_27[] = 
  {
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_27[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_27 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_27,
    P_GEND_TYPE_NMDTUP_TARR_27
  };
  static PRT_TYPE P_GEND_TYPE_27 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_27
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_28[] = 
  {
    "startL"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_28[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_28 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_28,
    P_GEND_TYPE_NMDTUP_TARR_28
  };
  static PRT_TYPE P_GEND_TYPE_28 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_28
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_29[] = 
  {
    "startpos"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_29[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_29 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_29,
    P_GEND_TYPE_NMDTUP_TARR_29
  };
  static PRT_TYPE P_GEND_TYPE_29 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_29
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_30[] = 
  {
    "t"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_30[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_30 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_30,
    P_GEND_TYPE_NMDTUP_TARR_30
  };
  static PRT_TYPE P_GEND_TYPE_30 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_30
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_31[] = 
  {
    "time"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_31[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_31 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_31,
    P_GEND_TYPE_NMDTUP_TARR_31
  };
  static PRT_TYPE P_GEND_TYPE_31 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_31
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_32[] = 
  {
    "timer"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_32[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_32 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_32,
    P_GEND_TYPE_NMDTUP_TARR_32
  };
  static PRT_TYPE P_GEND_TYPE_32 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_32
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_33[] = 
  {
    "timesync"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_33[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_33 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_33,
    P_GEND_TYPE_NMDTUP_TARR_33
  };
  static PRT_TYPE P_GEND_TYPE_33 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_33
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_34[] = 
  {
    "ts"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_34[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_34 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_34,
    P_GEND_TYPE_NMDTUP_TARR_34
  };
  static PRT_TYPE P_GEND_TYPE_34 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_34
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_35[] = 
  {
    "_payload_0"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_35[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_35 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_35,
    P_GEND_TYPE_NMDTUP_TARR_35
  };
  static PRT_TYPE P_GEND_TYPE_35 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_35
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_36[] = 
  {
    "_payload_1"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_36[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_36 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_36,
    P_GEND_TYPE_NMDTUP_TARR_36
  };
  static PRT_TYPE P_GEND_TYPE_36 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_36
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_37[] = 
  {
    "_payload_2"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_37[] = 
  {
    &P_GEND_TYPE_5
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_37 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_37,
    P_GEND_TYPE_NMDTUP_TARR_37
  };
  static PRT_TYPE P_GEND_TYPE_37 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_37
    }
  };
  static PRT_SEQTYPE P_GEND_TYPE_SEQ_38 = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_TYPE P_GEND_TYPE_38 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_38
    }
  };
  static PRT_SEQTYPE P_GEND_TYPE_SEQ_39 = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_TYPE P_GEND_TYPE_39 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_39
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_40[] = 
  {
    &P_GEND_TYPE_1
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_40 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_40
  };
  static PRT_TYPE P_GEND_TYPE_40 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_40
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_41[] = 
  {
    &P_GEND_TYPE_3
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_41 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_41
  };
  static PRT_TYPE P_GEND_TYPE_41 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_41
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_42[] = 
  {
    &P_GEND_TYPE_4
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_42 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_42
  };
  static PRT_TYPE P_GEND_TYPE_42 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_42
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_43[] = 
  {
    "TrajMap"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_43[] = 
  {
    &P_GEND_TYPE_7
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_43 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_43,
    P_GEND_TYPE_NMDTUP_TARR_43
  };
  static PRT_TYPE P_GEND_TYPE_43 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_43
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_44[] = 
  {
    "counter",
    "noOfRobots"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_44[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_44 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_44,
    P_GEND_TYPE_NMDTUP_TARR_44
  };
  static PRT_TYPE P_GEND_TYPE_44 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_44
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_45[] = 
  {
    "currTimePeriod",
    "expectedEndTime"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_45[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_45 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_45,
    P_GEND_TYPE_NMDTUP_TARR_45
  };
  static PRT_TYPE P_GEND_TYPE_45 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_45
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_46[] = 
  {
    "g",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_46[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_46 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_46,
    P_GEND_TYPE_NMDTUP_TARR_46
  };
  static PRT_TYPE P_GEND_TYPE_46 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_46
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_47[] = 
  {
    "mp",
    "rid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_47[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_47 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_47,
    P_GEND_TYPE_NMDTUP_TARR_47
  };
  static PRT_TYPE P_GEND_TYPE_47 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_47
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_48[] = 
  {
    "payload",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_48[] = 
  {
    &P_GEND_TYPE_0,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_48 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_48,
    P_GEND_TYPE_NMDTUP_TARR_48
  };
  static PRT_TYPE P_GEND_TYPE_48 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_48
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_49[] = 
  {
    "priority",
    "robot"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_49[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_49 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_49,
    P_GEND_TYPE_NMDTUP_TARR_49
  };
  static PRT_TYPE P_GEND_TYPE_49 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_49
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_50[] = 
  {
    "ret"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_50[] = 
  {
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_50 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_50,
    P_GEND_TYPE_NMDTUP_TARR_50
  };
  static PRT_TYPE P_GEND_TYPE_50 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_50
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_51[] = 
  {
    "retVal",
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_51[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_51 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_51,
    P_GEND_TYPE_NMDTUP_TARR_51
  };
  static PRT_TYPE P_GEND_TYPE_51 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_51
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_52[] = 
  {
    "robot",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_52[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_52 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_52,
    P_GEND_TYPE_NMDTUP_TARR_52
  };
  static PRT_TYPE P_GEND_TYPE_52 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_52
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_53[] = 
  {
    "robotId",
    "startL"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_53[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_53 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_53,
    P_GEND_TYPE_NMDTUP_TARR_53
  };
  static PRT_TYPE P_GEND_TYPE_53 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_53
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_54[] = 
  {
    "robotId",
    "timesync"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_54[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_54 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_54,
    P_GEND_TYPE_NMDTUP_TARR_54
  };
  static PRT_TYPE P_GEND_TYPE_54 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_54
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_55[] = 
  {
    "robotid",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_55[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_55 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_55,
    P_GEND_TYPE_NMDTUP_TARR_55
  };
  static PRT_TYPE P_GEND_TYPE_55 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_55
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_56[] = 
  {
    "robotid",
    "startpos"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_56[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_56 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_56,
    P_GEND_TYPE_NMDTUP_TARR_56
  };
  static PRT_TYPE P_GEND_TYPE_56 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_56
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_57[] = 
  {
    "robots"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_57[] = 
  {
    &P_GEND_TYPE_39
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_57 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_57,
    P_GEND_TYPE_NMDTUP_TARR_57
  };
  static PRT_TYPE P_GEND_TYPE_57 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_57
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_58[] = 
  {
    "startT",
    "robotId"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_58[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_58 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_58,
    P_GEND_TYPE_NMDTUP_TARR_58
  };
  static PRT_TYPE P_GEND_TYPE_58 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_58
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_59[] = 
  {
    "success",
    "nextRobot"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_59[] = 
  {
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_59 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_59,
    P_GEND_TYPE_NMDTUP_TARR_59
  };
  static PRT_TYPE P_GEND_TYPE_59 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_59
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_60[] = 
  {
    "timer",
    "time"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_60[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_60 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_60,
    P_GEND_TYPE_NMDTUP_TARR_60
  };
  static PRT_TYPE P_GEND_TYPE_60 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_60
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_61[] = 
  {
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_61[] = 
  {
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_61 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_61,
    P_GEND_TYPE_NMDTUP_TARR_61
  };
  static PRT_TYPE P_GEND_TYPE_61 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_61
    }
  };
  static PRT_SEQTYPE P_GEND_TYPE_SEQ_62 = 
  {
    &P_GEND_TYPE_38
  };
  static PRT_TYPE P_GEND_TYPE_62 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_62
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_63[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_63 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_63
  };
  static PRT_TYPE P_GEND_TYPE_63 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_63
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_64[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_64 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_64
  };
  static PRT_TYPE P_GEND_TYPE_64 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_64
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_65[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_1
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_65 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_65
  };
  static PRT_TYPE P_GEND_TYPE_65 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_65
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_66[] = 
  {
    &P_GEND_TYPE_38
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_66 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_66
  };
  static PRT_TYPE P_GEND_TYPE_66 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_66
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_67[] = 
  {
    "allrobots",
    "timesync"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_67[] = 
  {
    &P_GEND_TYPE_39,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_67 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_67,
    P_GEND_TYPE_NMDTUP_TARR_67
  };
  static PRT_TYPE P_GEND_TYPE_67 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_67
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_68[] = 
  {
    "ev",
    "payload",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_68[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_0,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_68 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_68,
    P_GEND_TYPE_NMDTUP_TARR_68
  };
  static PRT_TYPE P_GEND_TYPE_68 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_68
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_69[] = 
  {
    "index",
    "robots"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_69[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_39
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_69 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_69,
    P_GEND_TYPE_NMDTUP_TARR_69
  };
  static PRT_TYPE P_GEND_TYPE_69 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_69
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_70[] = 
  {
    "index",
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_70[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_70 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_70,
    P_GEND_TYPE_NMDTUP_TARR_70
  };
  static PRT_TYPE P_GEND_TYPE_70 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_70
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_71[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_71[] = 
  {
    &P_GEND_TYPE_46
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_71 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_71,
    P_GEND_TYPE_NMDTUP_TARR_71
  };
  static PRT_TYPE P_GEND_TYPE_71 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_71
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_72[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_72[] = 
  {
    &P_GEND_TYPE_47
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_72 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_72,
    P_GEND_TYPE_NMDTUP_TARR_72
  };
  static PRT_TYPE P_GEND_TYPE_72 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_72
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_73[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_73[] = 
  {
    &P_GEND_TYPE_49
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_73 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_73,
    P_GEND_TYPE_NMDTUP_TARR_73
  };
  static PRT_TYPE P_GEND_TYPE_73 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_73
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_74[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_74[] = 
  {
    &P_GEND_TYPE_55
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_74 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_74,
    P_GEND_TYPE_NMDTUP_TARR_74
  };
  static PRT_TYPE P_GEND_TYPE_74 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_74
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_75[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_75[] = 
  {
    &P_GEND_TYPE_56
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_75 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_75,
    P_GEND_TYPE_NMDTUP_TARR_75
  };
  static PRT_TYPE P_GEND_TYPE_75 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_75
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_76[] = 
  {
    "retTraj",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_76[] = 
  {
    &P_GEND_TYPE_38,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_76 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_76,
    P_GEND_TYPE_NMDTUP_TARR_76
  };
  static PRT_TYPE P_GEND_TYPE_76 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_76
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_77[] = 
  {
    "rinfo"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_77[] = 
  {
    &P_GEND_TYPE_56
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_77 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_77,
    P_GEND_TYPE_NMDTUP_TARR_77
  };
  static PRT_TYPE P_GEND_TYPE_77 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_77
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_78[] = 
  {
    "robotid",
    "counter",
    "noOfRobots"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_78[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_78 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_78,
    P_GEND_TYPE_NMDTUP_TARR_78
  };
  static PRT_TYPE P_GEND_TYPE_78 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_78
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_79[] = 
  {
    "source",
    "retVal",
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_79[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_79 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_79,
    P_GEND_TYPE_NMDTUP_TARR_79
  };
  static PRT_TYPE P_GEND_TYPE_79 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_79
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_80[] = 
  {
    "startT",
    "robotId",
    "timesync"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_80[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_80 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_80,
    P_GEND_TYPE_NMDTUP_TARR_80
  };
  static PRT_TYPE P_GEND_TYPE_80 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_80
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_81[] = 
  {
    "target"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_81[] = 
  {
    &P_GEND_TYPE_49
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_81 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_81,
    P_GEND_TYPE_NMDTUP_TARR_81
  };
  static PRT_TYPE P_GEND_TYPE_81 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_81
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_82[] = 
  {
    "timeSync",
    "robotid",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_82[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_82 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_82,
    P_GEND_TYPE_NMDTUP_TARR_82
  };
  static PRT_TYPE P_GEND_TYPE_82 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_82
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_83[] = 
  {
    "traj",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_83[] = 
  {
    &P_GEND_TYPE_38,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_83 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_83,
    P_GEND_TYPE_NMDTUP_TARR_83
  };
  static PRT_TYPE P_GEND_TYPE_83 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_83
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_84[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_84[] = 
  {
    &P_GEND_TYPE_46
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_84 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_84,
    P_GEND_TYPE_NMDTUP_TARR_84
  };
  static PRT_TYPE P_GEND_TYPE_84 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_84
    }
  };
  static PRT_SEQTYPE P_GEND_TYPE_SEQ_85 = 
  {
    &P_GEND_TYPE_63
  };
  static PRT_TYPE P_GEND_TYPE_85 = 
  {
    PRT_KIND_SEQ,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_85
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_86[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_86 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_86
  };
  static PRT_TYPE P_GEND_TYPE_86 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_86
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_87[] = 
  {
    &P_GEND_TYPE_63
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_87 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_87
  };
  static PRT_TYPE P_GEND_TYPE_87 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_87
    }
  };
  static PRT_MAPTYPE P_GEND_TYPE_MAP_88 = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_85
  };
  static PRT_TYPE P_GEND_TYPE_88 = 
  {
    PRT_KIND_MAP,
    
    {
        &P_GEND_TYPE_MAP_88
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_89[] = 
  {
    "avoids",
    "robotid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_89[] = 
  {
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_89 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_89,
    P_GEND_TYPE_NMDTUP_TARR_89
  };
  static PRT_TYPE P_GEND_TYPE_89 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_89
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_90[] = 
  {
    "currTimePeriod",
    "traj",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_90[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_90 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_90,
    P_GEND_TYPE_NMDTUP_TARR_90
  };
  static PRT_TYPE P_GEND_TYPE_90 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_90
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_91[] = 
  {
    "currTraj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_91[] = 
  {
    &P_GEND_TYPE_85
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_91 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_91,
    P_GEND_TYPE_NMDTUP_TARR_91
  };
  static PRT_TYPE P_GEND_TYPE_91 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_91
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_92[] = 
  {
    "path",
    "startT",
    "robotId"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_92[] = 
  {
    &P_GEND_TYPE_38,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_92 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_92,
    P_GEND_TYPE_NMDTUP_TARR_92
  };
  static PRT_TYPE P_GEND_TYPE_92 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_92
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_93[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_93[] = 
  {
    &P_GEND_TYPE_67
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_93 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_93,
    P_GEND_TYPE_NMDTUP_TARR_93
  };
  static PRT_TYPE P_GEND_TYPE_93 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_93
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_94[] = 
  {
    "payload",
    "ts"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_94[] = 
  {
    &P_GEND_TYPE_47,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_94 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_94,
    P_GEND_TYPE_NMDTUP_TARR_94
  };
  static PRT_TYPE P_GEND_TYPE_94 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_94
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_95[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_95[] = 
  {
    &P_GEND_TYPE_85
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_95 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_95,
    P_GEND_TYPE_NMDTUP_TARR_95
  };
  static PRT_TYPE P_GEND_TYPE_95 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_95
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_96[] = 
  {
    "rinfo",
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_96[] = 
  {
    &P_GEND_TYPE_56,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_96 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_96,
    P_GEND_TYPE_NMDTUP_TARR_96
  };
  static PRT_TYPE P_GEND_TYPE_96 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_96
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_97[] = 
  {
    "robotid",
    "source",
    "retVal",
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_97[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_97 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_97,
    P_GEND_TYPE_NMDTUP_TARR_97
  };
  static PRT_TYPE P_GEND_TYPE_97 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_97
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_98[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_63
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_98 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_98
  };
  static PRT_TYPE P_GEND_TYPE_98 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_98
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_99[] = 
  {
    &P_GEND_TYPE_85
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_99 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_99
  };
  static PRT_TYPE P_GEND_TYPE_99 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_99
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_100[] = 
  {
    "allTarget",
    "ev",
    "payload",
    "source"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_100[] = 
  {
    &P_GEND_TYPE_39,
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_0,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_100 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_100,
    P_GEND_TYPE_NMDTUP_TARR_100
  };
  static PRT_TYPE P_GEND_TYPE_100 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_100
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_101[] = 
  {
    "avoid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_101[] = 
  {
    &P_GEND_TYPE_88
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_101 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_101,
    P_GEND_TYPE_NMDTUP_TARR_101
  };
  static PRT_TYPE P_GEND_TYPE_101 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_101
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_102[] = 
  {
    "g",
    "avoids",
    "robotid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_102[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_102 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_102,
    P_GEND_TYPE_NMDTUP_TARR_102
  };
  static PRT_TYPE P_GEND_TYPE_102 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_102
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_103[] = 
  {
    "path",
    "startT",
    "robotId",
    "timesync"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_103[] = 
  {
    &P_GEND_TYPE_38,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_103 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_103,
    P_GEND_TYPE_NMDTUP_TARR_103
  };
  static PRT_TYPE P_GEND_TYPE_103 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_103
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_104[] = 
  {
    "robot",
    "currTraj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_104[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_85
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_104 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_104,
    P_GEND_TYPE_NMDTUP_TARR_104
  };
  static PRT_TYPE P_GEND_TYPE_104 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_104
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_105[] = 
  {
    "robotInfo",
    "robot",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_105[] = 
  {
    &P_GEND_TYPE_56,
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_105 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_105,
    P_GEND_TYPE_NMDTUP_TARR_105
  };
  static PRT_TYPE P_GEND_TYPE_105 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_105
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_106[] = 
  {
    "timeSync",
    "robotid",
    "source",
    "retVal",
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_106[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_106 = 
  {
    5,
    P_GEND_TYPE_NMDTUP_NARR_106,
    P_GEND_TYPE_NMDTUP_TARR_106
  };
  static PRT_TYPE P_GEND_TYPE_106 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_106
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_107[] = 
  {
    "timedTraj",
    "s"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_107[] = 
  {
    &P_GEND_TYPE_85,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_107 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_107,
    P_GEND_TYPE_NMDTUP_TARR_107
  };
  static PRT_TYPE P_GEND_TYPE_107 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_107
    }
  };
  static PRT_TYPE *P_GEND_TYPE_TUP_ARR_108[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_85
  };
  static PRT_TUPTYPE P_GEND_TYPE_TUP_108 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_108
  };
  static PRT_TYPE P_GEND_TYPE_108 = 
  {
    PRT_KIND_TUPLE,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_108
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_109[] = 
  {
    "convertedAvoids",
    "index",
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_109[] = 
  {
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_109 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_109,
    P_GEND_TYPE_NMDTUP_TARR_109
  };
  static PRT_TYPE P_GEND_TYPE_109 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_109
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_110[] = 
  {
    "goal",
    "avoid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_110[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_88
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_110 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_110,
    P_GEND_TYPE_NMDTUP_TARR_110
  };
  static PRT_TYPE P_GEND_TYPE_110 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_110
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_111[] = 
  {
    "noOfRobots",
    "robotInfo",
    "robot",
    "index"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_111[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_56,
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_111 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_111,
    P_GEND_TYPE_NMDTUP_TARR_111
  };
  static PRT_TYPE P_GEND_TYPE_111 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_111
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_112[] = 
  {
    "payload"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_112[] = 
  {
    &P_GEND_TYPE_104
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_112 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_112,
    P_GEND_TYPE_NMDTUP_TARR_112
  };
  static PRT_TYPE P_GEND_TYPE_112 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_112
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_113[] = 
  {
    "s",
    "g",
    "avoids",
    "robotid"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_113[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_113 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_113,
    P_GEND_TYPE_NMDTUP_TARR_113
  };
  static PRT_TYPE P_GEND_TYPE_113 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_113
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_114[] = 
  {
    "maxComputeTimeForPlanner",
    "convertedAvoids",
    "index",
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_114[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_114 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_114,
    P_GEND_TYPE_NMDTUP_TARR_114
  };
  static PRT_TYPE P_GEND_TYPE_114 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_114
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_115[] = 
  {
    "startingTimePeriod",
    "maxComputeTimeForPlanner",
    "convertedAvoids",
    "index",
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_115[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_115 = 
  {
    5,
    P_GEND_TYPE_NMDTUP_NARR_115,
    P_GEND_TYPE_NMDTUP_TARR_115
  };
  static PRT_TYPE P_GEND_TYPE_115 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_115
    }
  };
  static PRT_STRING P_GEND_TYPE_NMDTUP_NARR_116[] = 
  {
    "currTimePeriod",
    "startingTimePeriod",
    "maxComputeTimeForPlanner",
    "convertedAvoids",
    "index",
    "traj"
  };
  static PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_116[] = 
  {
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_62,
    &P_GEND_TYPE_3,
    &P_GEND_TYPE_38
  };
  static PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_116 = 
  {
    6,
    P_GEND_TYPE_NMDTUP_NARR_116,
    P_GEND_TYPE_NMDTUP_TARR_116
  };
  static PRT_TYPE P_GEND_TYPE_116 = 
  {
    PRT_KIND_NMDTUP,
    
    {
        (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_116
    }
  };
  static PRT_VALUE P_GEND_VALUE_0 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_CANCEL_FAILURE
    }
  };
  static PRT_VALUE P_GEND_VALUE_1 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_CANCEL_SUCCESS
    }
  };
  static PRT_VALUE P_GEND_VALUE_2 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_TIMEOUT
    }
  };
  static PRT_VALUE P_GEND_VALUE_3 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_UNIT
    }
  };
  static PRT_VALUE P_GEND_VALUE_4 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eAllRobots
    }
  };
  static PRT_VALUE P_GEND_VALUE_5 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eCurrTimePeriod
    }
  };
  static PRT_VALUE P_GEND_VALUE_6 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eCurrentTraj
    }
  };
  static PRT_VALUE P_GEND_VALUE_7 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eDistMotionPlanMachine
    }
  };
  static PRT_VALUE P_GEND_VALUE_8 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eGetTimePeriod
    }
  };
  static PRT_VALUE P_GEND_VALUE_9 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eNewTask
    }
  };
  static PRT_VALUE P_GEND_VALUE_10 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_ePlanCompletion
    }
  };
  static PRT_VALUE P_GEND_VALUE_11 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_ePlanExecutorMachine
    }
  };
  static PRT_VALUE P_GEND_VALUE_12 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eRequestCurrentTraj
    }
  };
  static PRT_VALUE P_GEND_VALUE_13 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eStartExecutingPlan
    }
  };
  static PRT_VALUE P_GEND_VALUE_14 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eTask_completed
    }
  };
  static PRT_VALUE P_GEND_VALUE_15 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        P_EVENT_eTimeSyncId
    }
  };
  static PRT_VALUE P_GEND_VALUE_16 = 
  {
    PRT_VALUE_KIND_INT,
    
    {
        0U
    }
  };
  static PRT_VALUE P_GEND_VALUE_17 = 
  {
    PRT_VALUE_KIND_INT,
    
    {
        1U
    }
  };
  static PRT_VALUE P_GEND_VALUE_18 = 
  {
    PRT_VALUE_KIND_INT,
    
    {
        4U
    }
  };
  static PRT_VALUE P_GEND_VALUE_19 = 
  {
    PRT_VALUE_KIND_INT,
    
    {
        100U
    }
  };
  static PRT_VALUE P_GEND_VALUE_20 = 
  {
    PRT_VALUE_KIND_INT,
    
    {
        500U
    }
  };
  static PRT_VALUE P_GEND_VALUE_21 = 
  {
    PRT_VALUE_KIND_BOOL,
    
    {
        PRT_FALSE
    }
  };
  static PRT_VALUE P_GEND_VALUE_22 = 
  {
    PRT_VALUE_KIND_EVENT,
    
    {
        PRT_SPECIAL_EVENT_HALT
    }
  };
  static PRT_VALUE P_GEND_VALUE_23 = 
  {
    PRT_VALUE_KIND_NULL,
    
    {
        PRT_SPECIAL_EVENT_NULL
    }
  };
  static PRT_VALUE P_GEND_VALUE_24 = 
  {
    PRT_VALUE_KIND_BOOL,
    
    {
        PRT_TRUE
    }
  };
  PRT_VARDECL P_GEND_VARS_DistributedMotionPlannerMachine[] = 
  {
    
    {
        P_VAR_DistributedMotionPlannerMachine_allAvoidsV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "allAvoidsV",
        &P_GEND_TYPE_88,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_allRobotsMPV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "allRobotsMPV",
        &P_GEND_TYPE_39,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_currTaskId,
        P_MACHINE_DistributedMotionPlannerMachine,
        "currTaskId",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_currTaskV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "currTaskV",
        &P_GEND_TYPE_46,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_currentLocationV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "currentLocationV",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_currentTrajV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "currentTrajV",
        &P_GEND_TYPE_85,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_localTimeV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "localTimeV",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_myIdV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "myIdV",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_numOfRobots,
        P_MACHINE_DistributedMotionPlannerMachine,
        "numOfRobots",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_pendingRequestsV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "pendingRequestsV",
        &P_GEND_TYPE_39,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_planExecutorV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "planExecutorV",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV,
        P_MACHINE_DistributedMotionPlannerMachine,
        "receivedTrajFromV",
        &P_GEND_TYPE_7,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_DistributedTimeSyncMachine[] = 
  {
    
    {
        P_VAR_DistributedTimeSyncMachine_noOfRobots,
        P_MACHINE_DistributedTimeSyncMachine,
        "noOfRobots",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV,
        P_MACHINE_DistributedTimeSyncMachine,
        "robotsLocalTimeV",
        &P_GEND_TYPE_6,
        0U,
        NULL
    },
    
    {
        P_VAR_DistributedTimeSyncMachine_timerV,
        P_MACHINE_DistributedTimeSyncMachine,
        "timerV",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_Main[] = 
  {
    
    {
        P_VAR_Main_allRobotsV,
        P_MACHINE_Main,
        "allRobotsV",
        &P_GEND_TYPE_39,
        0U,
        NULL
    },
    
    {
        P_VAR_Main_goalLocations,
        P_MACHINE_Main,
        "goalLocations",
        &P_GEND_TYPE_38,
        0U,
        NULL
    },
    
    {
        P_VAR_Main_taskscompleted,
        P_MACHINE_Main,
        "taskscompleted",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_Main_timeSyncV,
        P_MACHINE_Main,
        "timeSyncV",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_PlanExecutorMachine[] = 
  {
    
    {
        P_VAR_PlanExecutorMachine_localTimeV,
        P_MACHINE_PlanExecutorMachine,
        "localTimeV",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_PlanExecutorMachine_motionplanner,
        P_MACHINE_PlanExecutorMachine,
        "motionplanner",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_PlanExecutorMachine_robotId,
        P_MACHINE_PlanExecutorMachine,
        "robotId",
        &P_GEND_TYPE_3,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_RobotMachine[] = 
  {
    
    {
        P_VAR_RobotMachine_allRobots,
        P_MACHINE_RobotMachine,
        "allRobots",
        &P_GEND_TYPE_39,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotMachine_currentLocation,
        P_MACHINE_RobotMachine,
        "currentLocation",
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotMachine_motionplanner,
        P_MACHINE_RobotMachine,
        "motionplanner",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotMachine_planexecutor,
        P_MACHINE_RobotMachine,
        "planexecutor",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotMachine_robotid,
        P_MACHINE_RobotMachine,
        "robotid",
        &P_GEND_TYPE_3,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_Timer[] = 
  {
    
    {
        P_VAR_Timer_client,
        P_MACHINE_Timer,
        "client",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_DistributedMotionPlannerMachine_WaitForRequests[] = 
  {
    
    {
        0,
        P_STATE_DistributedMotionPlannerMachine_WaitForRequests,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eNewTask,
        P_STATE_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots,
        P_FUN_DistributedMotionPlannerMachine_ANON13,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Timer_Init[] = 
  {
    
    {
        0,
        P_STATE_Timer_Init,
        P_MACHINE_Timer,
        P_EVENT_UNIT,
        P_STATE_Timer_WaitForReq,
        P_FUN_Timer_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Timer_WaitForCancel[] = 
  {
    
    {
        0,
        P_STATE_Timer_WaitForCancel,
        P_MACHINE_Timer,
        P_EVENT_CANCEL,
        P_STATE_Timer_WaitForReq,
        P_FUN_Timer_ANON0,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_Timer_WaitForCancel,
        P_MACHINE_Timer,
        _P_EVENT_NULL,
        P_STATE_Timer_WaitForReq,
        P_FUN_Timer_ANON3,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_Timer_WaitForReq[] = 
  {
    
    {
        0,
        P_STATE_Timer_WaitForReq,
        P_MACHINE_Timer,
        P_EVENT_CANCEL,
        P_STATE_Timer_WaitForReq,
        P_FUN_Timer_ANON2,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_Timer_WaitForReq,
        P_MACHINE_Timer,
        P_EVENT_START,
        P_STATE_Timer_WaitForCancel,
        P_FUN_Timer_ANON1,
        0U,
        NULL
    }
  };
  PRT_VALUE *P_FUN_BROADCAST_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_CreateTimer_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ComputeTimedTraj_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ConvertTimedTrajToTraj_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_allTrajsReceived_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_GetCurrentTimePeriod_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_InvokeStartExecutingPathAndWait_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_Main_InitializeSystem_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_MotionPrimitiveTimePeriod_IMPL(PRT_MACHINEINST *context);

  PRT_DODECL P_GEND_DOS_DistributedMotionPlannerMachine_GetAllDistMotionPlanners[] = 
  {
    
    {
        0,
        P_STATE_DistributedMotionPlannerMachine_GetAllDistMotionPlanners,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eDistMotionPlanMachine,
        P_FUN_DistributedMotionPlannerMachine_ANON11,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots[] = 
  {
    
    {
        0,
        P_STATE_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eCurrentTraj,
        P_FUN_DistributedMotionPlannerMachine_ANON10,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eRequestCurrentTraj,
        P_FUN_DistributedMotionPlannerMachine_ANON3,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation[] = 
  {
    
    {
        0,
        P_STATE_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_ePlanCompletion,
        P_FUN_DistributedMotionPlannerMachine_ANON7,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eRequestCurrentTraj,
        P_FUN_DistributedMotionPlannerMachine_ANON5,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_DistributedMotionPlannerMachine_WaitForRequests[] = 
  {
    
    {
        0,
        P_STATE_DistributedMotionPlannerMachine_WaitForRequests,
        P_MACHINE_DistributedMotionPlannerMachine,
        P_EVENT_eRequestCurrentTraj,
        P_FUN_DistributedMotionPlannerMachine_ANON6,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_DistributedTimeSyncMachine_WaitForGetTimeRequest[] = 
  {
    
    {
        0,
        P_STATE_DistributedTimeSyncMachine_WaitForGetTimeRequest,
        P_MACHINE_DistributedTimeSyncMachine,
        P_EVENT_TIMEOUT,
        P_FUN_DistributedTimeSyncMachine_ANON2,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_DistributedTimeSyncMachine_WaitForGetTimeRequest,
        P_MACHINE_DistributedTimeSyncMachine,
        P_EVENT_eGetTimePeriod,
        P_FUN_DistributedTimeSyncMachine_ANON1,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_Main_StartSendingTaskRequest[] = 
  {
    
    {
        0,
        P_STATE_Main_StartSendingTaskRequest,
        P_MACHINE_Main,
        P_EVENT_eTask_completed,
        P_FUN_Main_ANON1,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_PlanExecutorMachine_WaitForPathToExecute[] = 
  {
    
    {
        0,
        P_STATE_PlanExecutorMachine_WaitForPathToExecute,
        P_MACHINE_PlanExecutorMachine,
        P_EVENT_eStartExecutingPlan,
        P_FUN_PlanExecutorMachine_ANON3,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotMachine_Init[] = 
  {
    
    {
        0,
        P_STATE_RobotMachine_Init,
        P_MACHINE_RobotMachine,
        P_EVENT_eAllRobots,
        P_FUN_RobotMachine_ANON3,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotMachine_Init,
        P_MACHINE_RobotMachine,
        P_EVENT_eDistMotionPlanMachine,
        P_FUN_RobotMachine_ANON1,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_RobotMachine_Init,
        P_MACHINE_RobotMachine,
        P_EVENT_eNewTask,
        P_FUN_RobotMachine_ANON2,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_Timer_WaitForCancel[] = 
  {
    
    {
        0,
        P_STATE_Timer_WaitForCancel,
        P_MACHINE_Timer,
        P_EVENT_START,
        _P_FUN_PUSH_OR_IGN,
        0U,
        NULL
    }
  };
  PRT_VALUE *P_FUN_BROADCAST_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 4U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_1) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[4U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_4(PrtMkBoolValue(!PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_3)), PRT_TRUE, PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
        {
          P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_frame.locals[2U], PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE, P_EXPR_2(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
        }
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 4U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE), PRT_FALSE);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_CreateTimer_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_ret;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      p_tmp_ret = P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_Timer, p_tmp_expr_0)->id), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(&P_GEND_TYPE_17);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ComputeTimedTraj_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_expr_6;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 12U)
      {
        goto L12;
      }
      if (p_tmp_frame.returnTo == 13U)
      {
        goto L13;
      }
      if (p_tmp_frame.returnTo == 14U)
      {
        goto L14;
      }
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 4U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_18, PRT_FALSE), PRT_FALSE);
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 5U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_myIdV], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_localTimeV], PRT_FALSE);
      L12:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 12U, p_tmp_mach_priv, 5U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[4U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 6U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_1) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[6U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE), PRT_TRUE))
      {
        P_EXPR_6(PrtPushNewFrame(p_tmp_mach_priv, 32U, PRT_FUN_PARAM_CLONE, p_tmp_expr_5, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, PrtMapGetNC(p_tmp_expr_1, p_tmp_expr_4), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_2), PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE, p_tmp_frame.locals[6U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE);
        L13:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 13U, p_tmp_mach_priv, 32U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetLocalVarEx(p_tmp_frame.locals, 7U, p_tmp_funstmt_ret, PRT_FALSE);
        P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[5U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_86, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[7U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        if (!P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_2) > PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[7U], PRT_FALSE), PRT_TRUE))
        {
          PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
        }
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 6U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[6U], PRT_FALSE), PRT_FALSE);
      }
      if (!P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_4, p_tmp_expr_3)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_1) - PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_numOfRobots], PRT_FALSE, p_tmp_frame.locals[5U], PRT_FALSE), PRT_TRUE))
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currentTrajV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_85), PRT_TRUE), PRT_FALSE);
      P_EXPR_4(PrtPushNewFrame(p_tmp_mach_priv, 34U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_myIdV], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentLocationV], PRT_FALSE, p_tmp_frame.locals[5U], PRT_FALSE);
      L14:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 14U, p_tmp_mach_priv, 34U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 7U, p_tmp_funstmt_ret, PRT_FALSE);
      if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[7U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_98, p_tmp_expr_1, p_tmp_expr_2), PRT_TRUE, P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentLocationV], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_21, PRT_FALSE));
        goto P_EXIT_FUN;
      }
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 6U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      if (!P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_2) > PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[7U], PRT_FALSE), PRT_TRUE))
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[7U], PRT_FALSE, p_tmp_frame.locals[6U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_6(P_TUPLE_1(&P_GEND_TYPE_98, p_tmp_expr_0, p_tmp_expr_5), PRT_TRUE, P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_3, p_tmp_expr_4), PRT_TRUE, PrtSeqGetNC(p_tmp_expr_2, p_tmp_expr_0), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_1) + PrtPrimGetInt(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[7U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE, p_tmp_frame.locals[6U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 6U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[6U], PRT_FALSE), PRT_FALSE);
      }
      p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_24, PRT_FALSE));
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(&P_GEND_TYPE_110);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ConvertTimedTrajToTraj_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_expr_6;
      PRT_VALUE *p_tmp_expr_7;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_4) >= PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_3, 0), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_2, p_tmp_expr_0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_TRUE))
        {
          P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[2U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_6(P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_4, p_tmp_expr_5), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_3, 1), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, PrtSeqGetNC(p_tmp_expr_2, p_tmp_expr_0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_FALSE);
          PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
          PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
          PrtFree(p_tmp_stmt_0->valueUnion.tuple);
          PrtFree(p_tmp_stmt_0);
        }
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[2U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_7(P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_1, p_tmp_expr_6), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_5, 1), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_4), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_3) - PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
      }
      p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[2U], PRT_FALSE));
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(&P_GEND_TYPE_107);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_allTrajsReceived_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtMapGetKeys(p_tmp_expr_0), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_4)), PRT_TRUE, PrtMapGetNC(p_tmp_expr_0, p_tmp_expr_3), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
        {
          p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_21, PRT_FALSE));
          goto P_EXIT_FUN;
        }
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      }
      p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_24, PRT_FALSE));
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(&P_GEND_TYPE_43);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  PRT_VALUE *P_FUN_GetCurrentTimePeriod_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 26U)
      {
        goto L26;
      }
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_55, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_8, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      L26:
      if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 26U))
      {
        return NULL;
      }
      PrtGetFunction(p_tmp_mach_priv, p_tmp_frame.rcase->funIndex)(context);
      if (p_tmp_mach_priv->receive != NULL)
      {
        PrtPushFrame(p_tmp_mach_priv, &p_tmp_frame);
        return NULL;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      p_tmp_frame.rcase = NULL;
      p_tmp_frame.returnTo = 0x0FFFFU;
      p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[3U], PRT_FALSE));
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(&P_GEND_TYPE_82);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  PRT_VALUE *P_FUN_InvokeStartExecutingPathAndWait_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 20U)
      {
        goto L20;
      }
      if (p_tmp_frame.returnTo == 21U)
      {
        goto L21;
      }
      if (p_tmp_frame.returnTo == 22U)
      {
        goto L22;
      }
      if (p_tmp_frame.returnTo == 23U)
      {
        goto L23;
      }
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 5U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE);
      L20:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 20U, p_tmp_mach_priv, 5U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 4U, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 5U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_2) + PrtPrimGetInt(p_tmp_expr_0)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE), PRT_FALSE);
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 14U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE);
      L21:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 21U, p_tmp_mach_priv, 14U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 5U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE);
      L22:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 22U, p_tmp_mach_priv, 5U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 4U, p_tmp_funstmt_ret, PRT_FALSE);
      if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[5U], PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE), PRT_TRUE))
      {
        P_EXPR_5(PrtPushNewFrame(p_tmp_mach_priv, 13U, PRT_FUN_PARAM_CLONE, p_tmp_expr_4), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_3) * PrtPrimGetInt(p_tmp_expr_0)), PRT_TRUE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_2) - PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[5U], PRT_FALSE, p_tmp_frame.locals[4U], PRT_FALSE, P_SEQ(PrtPushNewFrame(p_tmp_mach_priv, 11U), PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 11U)), PRT_TRUE);
        L23:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 23U, p_tmp_mach_priv, 13U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        if (p_tmp_funstmt_ret != NULL)
        {
          PrtFreeValue(p_tmp_funstmt_ret);
        }
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_Main_InitializeSystem_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 0U)
      {
        goto L0;
      }
      if (p_tmp_frame.returnTo == 1U)
      {
        goto L1;
      }
      if (p_tmp_frame.returnTo == 2U)
      {
        goto L2;
      }
      PrtPushNewFrame(p_tmp_mach_priv, 7U);
      L0:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 7U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_TRUE))
      {
        P_EXPR_1(PrtPushNewFrame(p_tmp_mach_priv, 8U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE);
        L1:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 1U, p_tmp_mach_priv, 8U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_funstmt_ret, PRT_FALSE);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_RobotMachine, p_tmp_expr_0)->id), PRT_TRUE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSeqInsertEx(p_tmp_mach_priv->varValues[P_VAR_Main_allRobotsV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_64, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_FALSE);
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_Main_timeSyncV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_DistributedTimeSyncMachine, p_tmp_expr_0)->id), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_Main_allRobotsV], PRT_FALSE), PRT_FALSE);
      P_EXPR_5(PrtPushNewFrame(p_tmp_mach_priv, 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_4, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_67, p_tmp_expr_0, p_tmp_expr_2), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_timeSyncV], PRT_FALSE, &P_GEND_VALUE_4, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_allRobotsV], PRT_FALSE);
      L2:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 2U, p_tmp_mach_priv, 2U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_MotionPrimitiveTimePeriod_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_20, PRT_FALSE));
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_ret == NULL)
      {
        return PrtMkDefaultValue(NULL);
      }
      else
      {
        return p_tmp_ret;
      }
    }
  }

  static PRT_VALUE *P_FUN_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[4U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_localTimeV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON10_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtMapInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allAvoidsV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PRT_FALSE, PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_108, p_tmp_expr_2, p_tmp_expr_1), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
      PrtFree(p_tmp_stmt_0->valueUnion.tuple);
      PrtFree(p_tmp_stmt_0);
      if (!P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtMapExists(p_tmp_expr_1, p_tmp_expr_2)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      P_STMT_1(PrtMapUpdateEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_24, PRT_FALSE), PRT_FALSE);
      if (P_BOOL_EXPR(P_EXPR_1(P_SEQ(PrtPushNewFrame(p_tmp_mach_priv, 35U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 35U)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_ComputeTrajState, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON11_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_expr_6;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtMapInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PRT_FALSE, PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_65, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, &P_GEND_VALUE_24, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
      PrtFree(p_tmp_stmt_0->valueUnion.tuple);
      PrtFree(p_tmp_stmt_0);
      if (P_BOOL_EXPR(P_EXPR_6(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_5, p_tmp_expr_3)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_4)), PRT_TRUE, PrtMapGetKeys(p_tmp_expr_1), PRT_TRUE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) - PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_numOfRobots], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_allRobotsMPV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtMapGetKeys(p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_7), PRT_TRUE), PRT_FALSE);
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_WaitForRequests, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON12_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 11U)
      {
        goto L11;
      }
      P_EXPR_5(PrtPushNewFrame(p_tmp_mach_priv, 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_4, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_49, p_tmp_expr_1, p_tmp_expr_3), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, &P_GEND_VALUE_12, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currTaskId], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE);
      L11:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 11U, p_tmp_mach_priv, 2U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      if (P_BOOL_EXPR(P_EXPR_1(P_SEQ(PrtPushNewFrame(p_tmp_mach_priv, 35U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 35U)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_ComputeTrajState, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON13_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 10U)
      {
        goto L10;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currTaskV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      PrtPushNewFrame(p_tmp_mach_priv, 9U);
      L10:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 10U, p_tmp_mach_priv, 9U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currTaskId, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_1) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_1(PrtMapUpdateEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_receivedTrajFromV], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_21, PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON14_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 15U)
      {
        goto L15;
      }
      if (p_tmp_frame.returnTo == 16U)
      {
        goto L16;
      }
      if (p_tmp_frame.returnTo == 17U)
      {
        goto L17;
      }
      if (p_tmp_frame.returnTo == 18U)
      {
        goto L18;
      }
      if (p_tmp_frame.returnTo == 19U)
      {
        goto L19;
      }
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 31U, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currTaskV], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allAvoidsV], PRT_FALSE);
      L15:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 15U, p_tmp_mach_priv, 31U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_funstmt_ret, PRT_FALSE);
      if (P_BOOL_EXPR(P_EXPR_1(PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE))
      {
        P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 33U, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) - PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_numOfRobots], PRT_FALSE);
        L16:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 16U, p_tmp_mach_priv, 33U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_funstmt_ret, PRT_FALSE);
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currTaskV], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_2(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_allRobotsMPV], PRT_FALSE), PRT_FALSE);
        P_EXPR_5(PrtPushNewFrame(p_tmp_mach_priv, 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_4, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_104, p_tmp_expr_3, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_pendingRequestsV], PRT_FALSE, &P_GEND_VALUE_6, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE);
        L17:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 17U, p_tmp_mach_priv, 2U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        if (p_tmp_funstmt_ret != NULL)
        {
          PrtFreeValue(p_tmp_funstmt_ret);
        }
        P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_pendingRequestsV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_39), PRT_TRUE), PRT_FALSE);
        P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 13U, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) * PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_19, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_myIdV], PRT_FALSE);
        L18:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 18U, p_tmp_mach_priv, 13U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        if (p_tmp_funstmt_ret != NULL)
        {
          PrtFreeValue(p_tmp_funstmt_ret);
        }
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_WaitForRequests, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      else
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_13, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_planExecutorV], PRT_FALSE), PRT_FALSE);
        P_EXPR_5(PrtPushNewFrame(p_tmp_mach_priv, 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_4, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_104, p_tmp_expr_3, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_pendingRequestsV], PRT_FALSE, &P_GEND_VALUE_6, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE);
        L19:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 19U, p_tmp_mach_priv, 2U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        if (p_tmp_funstmt_ret != NULL)
        {
          PrtFreeValue(p_tmp_funstmt_ret);
        }
        P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_pendingRequestsV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_39), PRT_TRUE), PRT_FALSE);
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_planExecutorV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_numOfRobots], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_WaitForRequests, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
        goto P_EXIT_FUN;
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_2) < PrtPrimGetInt(p_tmp_expr_0)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currTaskId], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_104, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_6, PRT_FALSE), PRT_FALSE, P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      }
      else
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_pendingRequestsV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_64, p_tmp_expr_1, p_tmp_expr_2), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON4_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON5_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_104, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_6, PRT_FALSE), PRT_FALSE, P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON6_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_104, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_6, PRT_FALSE), PRT_FALSE, P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON7_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currentLocationV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_EXPR_2(PrtFormatPrintf("--- Robot ", 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, 2U, 0U, " completed task and is at location ", 1U, " ---\n"), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_myIdV], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentLocationV], PRT_FALSE);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), &P_GEND_VALUE_23, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_14, PRT_FALSE), PRT_FALSE, P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currTaskV], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_WaitForRequests, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON8_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currentTrajV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_85), PRT_TRUE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_allAvoidsV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(PrtMkDefaultValue(&P_GEND_TYPE_88), PRT_TRUE), PRT_FALSE);
      P_STMT_0(PrtSeqInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentTrajV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_98, p_tmp_expr_1, p_tmp_expr_2), PRT_TRUE, P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedMotionPlannerMachine_currentLocationV], PRT_FALSE), PRT_FALSE);
      PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
      PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
      PrtFree(p_tmp_stmt_0->valueUnion.tuple);
      PrtFree(p_tmp_stmt_0);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedMotionPlannerMachine_ANON9_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 7U)
      {
        goto L7;
      }
      if (p_tmp_frame.returnTo == 8U)
      {
        goto L8;
      }
      if (p_tmp_frame.returnTo == 9U)
      {
        goto L9;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_myIdV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_currentLocationV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      PrtPushNewFrame(p_tmp_mach_priv, 7U);
      L7:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 7U, p_tmp_mach_priv, 7U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedMotionPlannerMachine_numOfRobots, p_tmp_funstmt_ret, PRT_FALSE);
      L8:
      if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 8U))
      {
        return NULL;
      }
      PrtGetFunction(p_tmp_mach_priv, p_tmp_frame.rcase->funIndex)(context);
      if (p_tmp_mach_priv->receive != NULL)
      {
        PrtPushFrame(p_tmp_mach_priv, &p_tmp_frame);
        return NULL;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      p_tmp_frame.rcase = NULL;
      p_tmp_frame.returnTo = 0x0FFFFU;
      L9:
      if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 9U))
      {
        return NULL;
      }
      PrtGetFunction(p_tmp_mach_priv, p_tmp_frame.rcase->funIndex)(context);
      if (p_tmp_mach_priv->receive != NULL)
      {
        PrtPushFrame(p_tmp_mach_priv, &p_tmp_frame);
        return NULL;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      p_tmp_frame.rcase = NULL;
      p_tmp_frame.returnTo = 0x0FFFFU;
      P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedMotionPlannerMachine_GetAllDistMotionPlanners, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedTimeSyncMachine_ANON0_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_DistributedTimeSyncMachine_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_3(PrtMapGetNC(p_tmp_expr_1, p_tmp_expr_2), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_5, PRT_FALSE), PRT_FALSE, P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedTimeSyncMachine_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 29U)
      {
        goto L29;
      }
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_noOfRobots], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_1(PrtMapUpdateEx(p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE, P_EXPR_4(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_3) + PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMapGetNC(p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      }
      P_EXPR_2(PrtPushNewFrame(p_tmp_mach_priv, 15U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_timerV], PRT_FALSE, P_SEQ(PrtPushNewFrame(p_tmp_mach_priv, 11U), PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 11U)), PRT_TRUE);
      L29:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 29U, p_tmp_mach_priv, 15U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_DistributedTimeSyncMachine_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 27U)
      {
        goto L27;
      }
      if (p_tmp_frame.returnTo == 28U)
      {
        goto L28;
      }
      PrtPushNewFrame(p_tmp_mach_priv, 7U);
      L27:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 27U, p_tmp_mach_priv, 7U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedTimeSyncMachine_noOfRobots, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_noOfRobots], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtMapInsertEx(p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_robotsLocalTimeV], PrtTupleGetNC(p_tmp_stmt_0, 0U), PRT_FALSE, PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DistributedTimeSyncMachine_timerV, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_Timer, p_tmp_expr_0)->id), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE);
      P_EXPR_2(PrtPushNewFrame(p_tmp_mach_priv, 15U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DistributedTimeSyncMachine_timerV], PRT_FALSE, P_SEQ(PrtPushNewFrame(p_tmp_mach_priv, 11U), PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 11U)), PRT_TRUE);
      L28:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 28U, p_tmp_mach_priv, 15U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_DistributedTimeSyncMachine_WaitForGetTimeRequest, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Main_ANON0_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_Main_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 6U)
      {
        goto L6;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_Main_taskscompleted, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_taskscompleted], PRT_FALSE), PRT_FALSE);
      if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_1, p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_Main_taskscompleted], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_goalLocations], PRT_FALSE), PRT_TRUE))
      {
        PrtPushNewFrame(p_tmp_mach_priv, 20U);
        L6:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 6U, p_tmp_mach_priv, 20U);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        if (p_tmp_funstmt_ret != NULL)
        {
          PrtFreeValue(p_tmp_funstmt_ret);
        }
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Main_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 3U)
      {
        goto L3;
      }
      PrtPushNewFrame(p_tmp_mach_priv, 21U);
      L3:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 3U, p_tmp_mach_priv, 21U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_Main_StartSendingTaskRequest, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Main_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 4U)
      {
        goto L4;
      }
      if (p_tmp_frame.returnTo == 5U)
      {
        goto L5;
      }
      PrtPushNewFrame(p_tmp_mach_priv, 6U);
      L4:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 4U, p_tmp_mach_priv, 6U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_Main_goalLocations, p_tmp_funstmt_ret, PRT_FALSE);
      PrtPushNewFrame(p_tmp_mach_priv, 7U);
      L5:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 5U, p_tmp_mach_priv, 7U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_funstmt_ret, PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_Main_goalLocations], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_4(P_TUPLE_1(&P_GEND_TYPE_46, p_tmp_expr_3, p_tmp_expr_2), PRT_TRUE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_goalLocations], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_2(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_Main_allRobotsV], PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
        if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_1) >= PrtPrimGetInt(p_tmp_expr_0)), PRT_TRUE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_TRUE))
        {
          P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
        }
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_PlanExecutorMachine_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_PlanExecutorMachine_localTimeV, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_PlanExecutorMachine_ANON1_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_PlanExecutorMachine_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 24U)
      {
        goto L24;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_PlanExecutorMachine_motionplanner, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_PlanExecutorMachine_robotId, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_11, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_PlanExecutorMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      L24:
      if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 24U))
      {
        return NULL;
      }
      PrtGetFunction(p_tmp_mach_priv, p_tmp_frame.rcase->funIndex)(context);
      if (p_tmp_mach_priv->receive != NULL)
      {
        PrtPushFrame(p_tmp_mach_priv, &p_tmp_frame);
        return NULL;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      p_tmp_frame.rcase = NULL;
      p_tmp_frame.returnTo = 0x0FFFFU;
      P_STMT_0(PrtGoto(p_tmp_mach_priv, P_STATE_PlanExecutorMachine_WaitForPathToExecute, p_tmp_stmt_0), &P_GEND_VALUE_23, PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_PlanExecutorMachine_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_expr_5;
      PRT_VALUE *p_tmp_expr_6;
      PRT_VALUE *p_tmp_expr_7;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 25U)
      {
        goto L25;
      }
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_16, PRT_FALSE), PRT_FALSE);
      while (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) < PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[2U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_4(P_TUPLE_1(&P_GEND_TYPE_63, p_tmp_expr_0, p_tmp_expr_3), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_2, 1), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 3U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[3U], PRT_FALSE), PRT_FALSE);
      }
      P_EXPR_7(PrtPushNewFrame(p_tmp_mach_priv, 10U, PRT_FUN_PARAM_CLONE, p_tmp_expr_3, PRT_FUN_PARAM_CLONE, p_tmp_expr_6, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_5, 0), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_4), PRT_FALSE, &P_GEND_VALUE_16, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_PlanExecutorMachine_robotId], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_PlanExecutorMachine_localTimeV], PRT_FALSE);
      L25:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 25U, p_tmp_mach_priv, 10U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_4(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_3), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_2) - PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_17, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_10, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_PlanExecutorMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_RobotMachine_ANON0_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_RobotMachine_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_1(PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_4), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_7, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_RobotMachine_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_RobotMachine_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_expr_4;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 31U)
      {
        goto L31;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotMachine_allRobots, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_15, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_15, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotMachine_planexecutor], PRT_FALSE), PRT_FALSE);
      P_EXPR_4(PrtPushNewFrame(p_tmp_mach_priv, 2U, PRT_FUN_PARAM_CLONE, p_tmp_expr_0, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_2, PRT_FUN_PARAM_CLONE, p_tmp_expr_3), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotMachine_motionplanner], PRT_FALSE, &P_GEND_VALUE_7, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotMachine_allRobots], PRT_FALSE);
      L31:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 31U, p_tmp_mach_priv, 2U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_RobotMachine_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_expr_1;
      PRT_VALUE *p_tmp_expr_2;
      PRT_VALUE *p_tmp_expr_3;
      PRT_VALUE *p_tmp_funstmt_ret;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_tuple;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (p_tmp_frame.returnTo == 30U)
      {
        goto L30;
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotMachine_robotid, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotMachine_currentLocation, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_EXPR_3(PrtPushNewFrame(p_tmp_mach_priv, 12U, PRT_FUN_PARAM_CLONE, p_tmp_expr_1, PRT_FUN_PARAM_CLONE, p_tmp_expr_2), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotMachine_robotid], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE);
      L30:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 30U, p_tmp_mach_priv, 12U);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      if (p_tmp_funstmt_ret != NULL)
      {
        PrtFreeValue(p_tmp_funstmt_ret);
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotMachine_motionplanner, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_DistributedMotionPlannerMachine, p_tmp_expr_0)->id), PRT_TRUE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotMachine_planexecutor, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_PlanExecutorMachine, p_tmp_expr_2)->id), PRT_TRUE, P_TUPLE_1(&P_GEND_TYPE_47, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_RobotMachine_robotid], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotMachine_motionplanner], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Timer_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_BOOLEAN p_tmp_bool;
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      if (P_BOOL_EXPR(P_EXPR_0(PrtMkNondetBoolValue(), PRT_TRUE), PRT_TRUE))
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_1, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_Timer_client], PRT_FALSE), PRT_FALSE);
      }
      else
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_0, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_Timer_client], PRT_FALSE), PRT_FALSE);
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_2, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_Timer_client], PRT_FALSE), PRT_FALSE);
      }
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Timer_ANON1_IMPL(PRT_MACHINEINST *context)
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

  static PRT_VALUE *P_FUN_Timer_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_0, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_Timer_client], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Timer_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      PRT_VALUE *p_tmp_stmt_2;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(context, PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2, PRT_FALSE)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_2, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_Timer_client], PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  static PRT_VALUE *P_FUN_Timer_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    {
      PRT_FUNSTACK_INFO p_tmp_frame;
      PRT_MACHINEINST_PRIV *p_tmp_mach_priv;
      PRT_VALUE *p_tmp_expr_0;
      PRT_VALUE *p_tmp_ret;
      PRT_VALUE *p_tmp_stmt_0;
      PRT_VALUE *p_tmp_stmt_1;
      p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
      p_tmp_ret = NULL;
      PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_Timer_client, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_23, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_3, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
      goto P_EXIT_FUN;
      P_EXIT_FUN:
      PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
      return p_tmp_ret;
    }
  }

  PRT_CASEDECL P_GEND_CASES_24[] = 
  {
    
    {
        P_EVENT_eTimeSyncId,
        16U
    }
  };
  PRT_CASEDECL P_GEND_CASES_26[] = 
  {
    
    {
        P_EVENT_eCurrTimePeriod,
        1U
    }
  };
  PRT_CASEDECL P_GEND_CASES_8[] = 
  {
    
    {
        P_EVENT_ePlanExecutorMachine,
        17U
    }
  };
  PRT_CASEDECL P_GEND_CASES_9[] = 
  {
    
    {
        P_EVENT_eTimeSyncId,
        16U
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_DistributedMotionPlannerMachine_ANON9[] = 
  {
    
    {
        8U,
        P_GEND_EVENTSET_ePlanExecutorMachine,
        1U,
        P_GEND_CASES_8
    },
    
    {
        9U,
        P_GEND_EVENTSET_eTimeSyncId,
        1U,
        P_GEND_CASES_9
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod[] = 
  {
    
    {
        26U,
        P_GEND_EVENTSET_eCurrTimePeriod,
        1U,
        P_GEND_CASES_26
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_PlanExecutorMachine_ANON2[] = 
  {
    
    {
        24U,
        P_GEND_EVENTSET_eTimeSyncId,
        1U,
        P_GEND_CASES_24
    }
  };
  PRT_FUNDECL P_GEND_FUNS_DistributedMotionPlannerMachine[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_DistributedMotionPlannerMachine,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_DistributedMotionPlannerMachine,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_DistributedMotionPlannerMachine,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_DistributedMotionPlannerMachine,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_DistributedMotionPlannerMachine,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_DistributedMotionPlannerMachine,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_DistributedMotionPlannerMachine,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_DistributedMotionPlannerMachine,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_DistributedMotionPlannerMachine,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON0,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON0_IMPL,
        1U,
        1U,
        2U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON1,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON1_IMPL,
        1U,
        1U,
        2U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON2,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON2_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON3,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON3_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON4_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON5,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON5_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON6,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON6_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON7,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON7_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON8,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON8_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON9,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON9_IMPL,
        1U,
        2U,
        1U,
        NULL,
        2U,
        P_GEND_RECEIVE_P_FUN_DistributedMotionPlannerMachine_ANON9,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON10,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON10_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON11,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON11_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON12,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON12_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON13,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON13_IMPL,
        1U,
        2U,
        1U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ANON14,
        P_MACHINE_DistributedMotionPlannerMachine,
        NULL,
        &P_FUN_DistributedMotionPlannerMachine_ANON14_IMPL,
        1U,
        3U,
        1U,
        &P_GEND_TYPE_59,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ComputeTimedTraj,
        P_MACHINE_DistributedMotionPlannerMachine,
        "ComputeTimedTraj",
        &P_FUN_DistributedMotionPlannerMachine_ComputeTimedTraj_IMPL,
        2U,
        8U,
        0U,
        &P_GEND_TYPE_116,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_ConvertTimedTrajToTraj,
        P_MACHINE_DistributedMotionPlannerMachine,
        "ConvertTimedTrajToTraj",
        &P_FUN_DistributedMotionPlannerMachine_ConvertTimedTrajToTraj_IMPL,
        2U,
        4U,
        0U,
        &P_GEND_TYPE_76,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_GetRandomNumber,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetRandomNumber",
        &P_FUN_DistributedMotionPlannerMachine_GetRandomNumber_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_PlanGenerator,
        P_MACHINE_DistributedMotionPlannerMachine,
        "PlanGenerator",
        &P_FUN_DistributedMotionPlannerMachine_PlanGenerator_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedMotionPlannerMachine_allTrajsReceived,
        P_MACHINE_DistributedMotionPlannerMachine,
        "allTrajsReceived",
        &P_FUN_DistributedMotionPlannerMachine_allTrajsReceived_IMPL,
        1U,
        3U,
        0U,
        &P_GEND_TYPE_69,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_FUNDECL P_GEND_FUNS_DistributedTimeSyncMachine[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_DistributedTimeSyncMachine,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_DistributedTimeSyncMachine,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_DistributedTimeSyncMachine,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_DistributedTimeSyncMachine,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_DistributedTimeSyncMachine,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_DistributedTimeSyncMachine,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_DistributedTimeSyncMachine,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_DistributedTimeSyncMachine,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_DistributedTimeSyncMachine,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_DistributedTimeSyncMachine,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_DistributedTimeSyncMachine,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_DistributedTimeSyncMachine,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_DistributedTimeSyncMachine,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_DistributedTimeSyncMachine,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedTimeSyncMachine_ANON0,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        &P_FUN_DistributedTimeSyncMachine_ANON0_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedTimeSyncMachine_ANON1,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        &P_FUN_DistributedTimeSyncMachine_ANON1_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedTimeSyncMachine_ANON2,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        &P_FUN_DistributedTimeSyncMachine_ANON2_IMPL,
        1U,
        2U,
        1U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_DistributedTimeSyncMachine_ANON3,
        P_MACHINE_DistributedTimeSyncMachine,
        NULL,
        &P_FUN_DistributedTimeSyncMachine_ANON3_IMPL,
        1U,
        2U,
        1U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_FUNDECL P_GEND_FUNS_Main[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_Main,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_Main,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_Main,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_Main,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_Main,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_Main,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_Main,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_Main,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_Main,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_Main,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_Main,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_Main,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_Main,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_Main,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_Main,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_Main,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_ANON0,
        P_MACHINE_Main,
        NULL,
        &P_FUN_Main_ANON0_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_ANON1,
        P_MACHINE_Main,
        NULL,
        &P_FUN_Main_ANON1_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_ANON2,
        P_MACHINE_Main,
        NULL,
        &P_FUN_Main_ANON2_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_ANON3,
        P_MACHINE_Main,
        NULL,
        &P_FUN_Main_ANON3_IMPL,
        1U,
        4U,
        1U,
        &P_GEND_TYPE_78,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_ExitP,
        P_MACHINE_Main,
        "ExitP",
        &P_FUN_Main_ExitP_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Main_InitializeSystem,
        P_MACHINE_Main,
        "InitializeSystem",
        &P_FUN_Main_InitializeSystem_IMPL,
        0U,
        4U,
        0U,
        &P_GEND_TYPE_111,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_FUNDECL P_GEND_FUNS_PlanExecutorMachine[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_PlanExecutorMachine,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_PlanExecutorMachine,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_PlanExecutorMachine,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_PlanExecutorMachine,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_PlanExecutorMachine,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_PlanExecutorMachine,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_PlanExecutorMachine,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_PlanExecutorMachine,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_PlanExecutorMachine,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_PlanExecutorMachine,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_PlanExecutorMachine,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_PlanExecutorMachine,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_PlanExecutorMachine,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_PlanExecutorMachine,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_PlanExecutorMachine_ANON0,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        &P_FUN_PlanExecutorMachine_ANON0_IMPL,
        1U,
        1U,
        2U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_PlanExecutorMachine_ANON1,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        &P_FUN_PlanExecutorMachine_ANON1_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_PlanExecutorMachine_ANON2,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        &P_FUN_PlanExecutorMachine_ANON2_IMPL,
        1U,
        2U,
        1U,
        NULL,
        1U,
        P_GEND_RECEIVE_P_FUN_PlanExecutorMachine_ANON2,
        0U,
        NULL
    },
    
    {
        P_FUN_PlanExecutorMachine_ANON3,
        P_MACHINE_PlanExecutorMachine,
        NULL,
        &P_FUN_PlanExecutorMachine_ANON3_IMPL,
        1U,
        4U,
        1U,
        &P_GEND_TYPE_90,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_FUNDECL P_GEND_FUNS_RobotMachine[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_RobotMachine,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_RobotMachine,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_RobotMachine,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_RobotMachine,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_RobotMachine,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_RobotMachine,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_RobotMachine,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_RobotMachine,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_RobotMachine,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_RobotMachine,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_RobotMachine,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_RobotMachine,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_RobotMachine,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_RobotMachine,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_RobotMachine,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RobotMachine_ANON0,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_RobotMachine_ANON0_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RobotMachine_ANON1,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_RobotMachine_ANON1_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RobotMachine_ANON2,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_RobotMachine_ANON2_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RobotMachine_ANON3,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_RobotMachine_ANON3_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RobotMachine_ANON4,
        P_MACHINE_RobotMachine,
        NULL,
        &P_FUN_RobotMachine_ANON4_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_FUNDECL P_GEND_FUNS_Timer[] = 
  {
    
    {
        _P_FUN_PUSH_OR_IGN,
        P_MACHINE_Timer,
        NULL,
        NULL,
        1U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_ANON0,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_ANON0_IMPL,
        1U,
        1U,
        5U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_BROADCAST,
        P_MACHINE_Timer,
        "BROADCAST",
        &P_FUN_BROADCAST_IMPL,
        4U,
        5U,
        0U,
        &P_GEND_TYPE_14,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CancelTimer,
        P_MACHINE_Timer,
        "CancelTimer",
        &P_FUN_CancelTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_CreateTimer,
        P_MACHINE_Timer,
        "CreateTimer",
        &P_FUN_CreateTimer_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetCurrentTimePeriod,
        P_MACHINE_Timer,
        "GetCurrentTimePeriod",
        &P_FUN_GetCurrentTimePeriod_IMPL,
        3U,
        5U,
        0U,
        &P_GEND_TYPE_21,
        1U,
        P_GEND_RECEIVE_P_FUN_GetCurrentTimePeriod,
        0U,
        NULL
    },
    
    {
        P_FUN_GetGoalLocations,
        P_MACHINE_Timer,
        "GetGoalLocations",
        &P_FUN_GetGoalLocations_IMPL,
        0U,
        1U,
        0U,
        &P_GEND_TYPE_50,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetNumOfRobots,
        P_MACHINE_Timer,
        "GetNumOfRobots",
        &P_FUN_GetNumOfRobots_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetRobotInfo,
        P_MACHINE_Timer,
        "GetRobotInfo",
        &P_FUN_GetRobotInfo_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_GetUniqueTaskId,
        P_MACHINE_Timer,
        "GetUniqueTaskId",
        &P_FUN_GetUniqueTaskId_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_InvokeStartExecutingPathAndWait,
        P_MACHINE_Timer,
        "InvokeStartExecutingPathAndWait",
        &P_FUN_InvokeStartExecutingPathAndWait_IMPL,
        4U,
        6U,
        0U,
        &P_GEND_TYPE_45,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_MotionPrimitiveTimePeriod,
        P_MACHINE_Timer,
        "MotionPrimitiveTimePeriod",
        &P_FUN_MotionPrimitiveTimePeriod_IMPL,
        0U,
        0U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_RosInit,
        P_MACHINE_Timer,
        "RosInit",
        &P_FUN_RosInit_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Sleep,
        P_MACHINE_Timer,
        "Sleep",
        &P_FUN_Sleep_IMPL,
        1U,
        1U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartExecutingPath,
        P_MACHINE_Timer,
        "StartExecutingPath",
        &P_FUN_StartExecutingPath_IMPL,
        3U,
        3U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_StartTimer,
        P_MACHINE_Timer,
        "StartTimer",
        &P_FUN_StartTimer_IMPL,
        2U,
        2U,
        0U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Timer_ANON0,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_Timer_ANON0_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Timer_ANON1,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_Timer_ANON1_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Timer_ANON2,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_Timer_ANON2_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Timer_ANON3,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_Timer_ANON3_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    },
    
    {
        P_FUN_Timer_ANON4,
        P_MACHINE_Timer,
        NULL,
        &P_FUN_Timer_ANON4_IMPL,
        1U,
        1U,
        1U,
        NULL,
        0U,
        NULL,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_DistributedMotionPlannerMachine[] = 
  {
    
    {
        P_STATE_DistributedMotionPlannerMachine_ComputeTrajState,
        P_MACHINE_DistributedMotionPlannerMachine,
        "ComputeTrajState",
        0,
        0,
        P_GEND_EVENTSET_eNewTaskePlanCompletion,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        NULL,
        NULL,
        P_FUN_DistributedMotionPlannerMachine_ANON14,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedMotionPlannerMachine_GetAllDistMotionPlanners,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetAllDistMotionPlanners",
        0,
        1,
        P_GEND_EVENTSET_eNewTaskeRequestCurrentTraj,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eDistMotionPlanMachine,
        NULL,
        P_GEND_DOS_DistributedMotionPlannerMachine_GetAllDistMotionPlanners,
        P_FUN_DistributedMotionPlannerMachine_ANON2,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots,
        P_MACHINE_DistributedMotionPlannerMachine,
        "GetCurrentStateOfAllRobots",
        0,
        2,
        P_GEND_EVENTSET_eNewTask,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eCurrentTrajeRequestCurrentTraj,
        NULL,
        P_GEND_DOS_DistributedMotionPlannerMachine_GetCurrentStateOfAllRobots,
        P_FUN_DistributedMotionPlannerMachine_ANON12,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedMotionPlannerMachine_Init,
        P_MACHINE_DistributedMotionPlannerMachine,
        "Init",
        0,
        0,
        P_GEND_EVENTSET_eDistMotionPlanMachine,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        NULL,
        NULL,
        P_FUN_DistributedMotionPlannerMachine_ANON9,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation,
        P_MACHINE_DistributedMotionPlannerMachine,
        "WaitForPlanCompletionOrCancellation",
        0,
        2,
        P_GEND_EVENTSET_eNewTask,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_ePlanCompletioneRequestCurrentTraj,
        NULL,
        P_GEND_DOS_DistributedMotionPlannerMachine_WaitForPlanCompletionOrCancellation,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedMotionPlannerMachine_WaitForRequests,
        P_MACHINE_DistributedMotionPlannerMachine,
        "WaitForRequests",
        1,
        1,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eNewTask,
        P_GEND_EVENTSET_eRequestCurrentTraj,
        P_GEND_TRANS_DistributedMotionPlannerMachine_WaitForRequests,
        P_GEND_DOS_DistributedMotionPlannerMachine_WaitForRequests,
        P_FUN_DistributedMotionPlannerMachine_ANON8,
        P_FUN_DistributedMotionPlannerMachine_ANON4,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_DistributedTimeSyncMachine[] = 
  {
    
    {
        P_STATE_DistributedTimeSyncMachine_Init,
        P_MACHINE_DistributedTimeSyncMachine,
        "Init",
        0,
        0,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        NULL,
        NULL,
        P_FUN_DistributedTimeSyncMachine_ANON3,
        P_FUN_DistributedTimeSyncMachine_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_DistributedTimeSyncMachine_WaitForGetTimeRequest,
        P_MACHINE_DistributedTimeSyncMachine,
        "WaitForGetTimeRequest",
        0,
        2,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_TIMEOUTeGetTimePeriod,
        NULL,
        P_GEND_DOS_DistributedTimeSyncMachine_WaitForGetTimeRequest,
        P_FUN_DistributedTimeSyncMachine_ANON0,
        P_FUN_DistributedTimeSyncMachine_ANON0,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_Main[] = 
  {
    
    {
        P_STATE_Main_Init,
        P_MACHINE_Main,
        "Init",
        0,
        0,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        NULL,
        NULL,
        P_FUN_Main_ANON2,
        P_FUN_Main_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_Main_StartSendingTaskRequest,
        P_MACHINE_Main,
        "StartSendingTaskRequest",
        0,
        1,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eTask_completed,
        NULL,
        P_GEND_DOS_Main_StartSendingTaskRequest,
        P_FUN_Main_ANON3,
        P_FUN_Main_ANON0,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_PlanExecutorMachine[] = 
  {
    
    {
        P_STATE_PlanExecutorMachine_Init,
        P_MACHINE_PlanExecutorMachine,
        "Init",
        0,
        0,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        NULL,
        NULL,
        P_FUN_PlanExecutorMachine_ANON2,
        P_FUN_PlanExecutorMachine_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_PlanExecutorMachine_WaitForPathToExecute,
        P_MACHINE_PlanExecutorMachine,
        "WaitForPathToExecute",
        0,
        1,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eStartExecutingPlan,
        NULL,
        P_GEND_DOS_PlanExecutorMachine_WaitForPathToExecute,
        P_FUN_PlanExecutorMachine_ANON1,
        P_FUN_PlanExecutorMachine_ANON1,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_RobotMachine[] = 
  {
    
    {
        P_STATE_RobotMachine_Init,
        P_MACHINE_RobotMachine,
        "Init",
        0,
        3,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_eAllRobotseDistMotionPlanMachineeNewTask,
        NULL,
        P_GEND_DOS_RobotMachine_Init,
        P_FUN_RobotMachine_ANON4,
        P_FUN_RobotMachine_ANON0,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_Timer[] = 
  {
    
    {
        P_STATE_Timer_Init,
        P_MACHINE_Timer,
        "Init",
        1,
        0,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_UNIT,
        P_GEND_EVENTSET_,
        P_GEND_TRANS_Timer_Init,
        NULL,
        P_FUN_Timer_ANON4,
        P_FUN_Timer_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_Timer_WaitForCancel,
        P_MACHINE_Timer,
        "WaitForCancel",
        2,
        1,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_CANCELnull,
        P_GEND_EVENTSET_START,
        P_GEND_TRANS_Timer_WaitForCancel,
        P_GEND_DOS_Timer_WaitForCancel,
        P_FUN_Timer_ANON1,
        P_FUN_Timer_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_Timer_WaitForReq,
        P_MACHINE_Timer,
        "WaitForReq",
        2,
        0,
        P_GEND_EVENTSET_,
        P_GEND_EVENTSET_CANCELSTART,
        P_GEND_EVENTSET_,
        P_GEND_TRANS_Timer_WaitForReq,
        NULL,
        P_FUN_Timer_ANON1,
        P_FUN_Timer_ANON1,
        0U,
        NULL
    }
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_DistributedMotionPlannerMachine = 
  {
    P_MACHINE_DistributedMotionPlannerMachine,
    "DistributedMotionPlannerMachine",
    12,
    6,
    21,
    4294967295,
    P_STATE_DistributedMotionPlannerMachine_Init,
    P_GEND_VARS_DistributedMotionPlannerMachine,
    P_GEND_STATES_DistributedMotionPlannerMachine,
    P_GEND_FUNS_DistributedMotionPlannerMachine,
    &P_CTOR_DistributedMotionPlannerMachine_IMPL,
    &P_DTOR_DistributedMotionPlannerMachine_IMPL,
    0U,
    NULL
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_DistributedTimeSyncMachine = 
  {
    P_MACHINE_DistributedTimeSyncMachine,
    "DistributedTimeSyncMachine",
    3,
    2,
    5,
    4294967295,
    P_STATE_DistributedTimeSyncMachine_Init,
    P_GEND_VARS_DistributedTimeSyncMachine,
    P_GEND_STATES_DistributedTimeSyncMachine,
    P_GEND_FUNS_DistributedTimeSyncMachine,
    &P_CTOR_DistributedTimeSyncMachine_IMPL,
    &P_DTOR_DistributedTimeSyncMachine_IMPL,
    0U,
    NULL
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_Main = 
  {
    P_MACHINE_Main,
    "Main",
    4,
    2,
    7,
    4294967295,
    P_STATE_Main_Init,
    P_GEND_VARS_Main,
    P_GEND_STATES_Main,
    P_GEND_FUNS_Main,
    &P_CTOR_Main_IMPL,
    &P_DTOR_Main_IMPL,
    0U,
    NULL
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_PlanExecutorMachine = 
  {
    P_MACHINE_PlanExecutorMachine,
    "PlanExecutorMachine",
    3,
    2,
    5,
    4294967295,
    P_STATE_PlanExecutorMachine_Init,
    P_GEND_VARS_PlanExecutorMachine,
    P_GEND_STATES_PlanExecutorMachine,
    P_GEND_FUNS_PlanExecutorMachine,
    &P_CTOR_PlanExecutorMachine_IMPL,
    &P_DTOR_PlanExecutorMachine_IMPL,
    0U,
    NULL
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_RobotMachine = 
  {
    P_MACHINE_RobotMachine,
    "RobotMachine",
    5,
    1,
    6,
    4294967295,
    P_STATE_RobotMachine_Init,
    P_GEND_VARS_RobotMachine,
    P_GEND_STATES_RobotMachine,
    P_GEND_FUNS_RobotMachine,
    &P_CTOR_RobotMachine_IMPL,
    &P_DTOR_RobotMachine_IMPL,
    0U,
    NULL
  };
  PRT_MACHINEDECL P_MACHINE_STRUCT_Timer = 
  {
    P_MACHINE_Timer,
    "Timer",
    1,
    3,
    6,
    4294967295,
    P_STATE_Timer_Init,
    P_GEND_VARS_Timer,
    P_GEND_STATES_Timer,
    P_GEND_FUNS_Timer,
    &P_CTOR_Timer_IMPL,
    &P_DTOR_Timer_IMPL,
    0U,
    NULL
  };
  