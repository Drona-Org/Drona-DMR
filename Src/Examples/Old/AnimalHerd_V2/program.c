
  #include "program.h"
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
  #define P_EXPR_8(x8, f8, x7, f7, x6, f6, x5, f5, x4, f4, x3, f3, x2, f2, x1, f1, x0, f0) P_SEQ(p_tmp_expr_0 = (x0), p_tmp_expr_1 = (x1), p_tmp_expr_2 = (x2), p_tmp_expr_3 = (x3), p_tmp_expr_4 = (x4), p_tmp_expr_5 = (x5), p_tmp_expr_6 = (x6), p_tmp_expr_7 = (x7), p_tmp_expr_8 = (x8), ((f0) ? PrtFreeValue(p_tmp_expr_0) : 0U), ((f1) ? PrtFreeValue(p_tmp_expr_1) : 0U), ((f2) ? PrtFreeValue(p_tmp_expr_2) : 0U), ((f3) ? PrtFreeValue(p_tmp_expr_3) : 0U), ((f4) ? PrtFreeValue(p_tmp_expr_4) : 0U), ((f5) ? PrtFreeValue(p_tmp_expr_5) : 0U), ((f6) ? PrtFreeValue(p_tmp_expr_6) : 0U), ((f7) ? PrtFreeValue(p_tmp_expr_7) : 0U), p_tmp_expr_8)
  #define P_TUPLE_0(t, x0) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), p_tmp_tuple)
  #define P_TUPLE_1(t, x0, x1) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), PrtTupleSet(p_tmp_tuple, 1U, (x1)), p_tmp_tuple)
  #define P_TUPLE_2(t, x0, x1, x2) P_SEQ(p_tmp_tuple = PrtMkDefaultValue(t), PrtTupleSet(p_tmp_tuple, 0U, (x0)), PrtTupleSet(p_tmp_tuple, 1U, (x1)), PrtTupleSet(p_tmp_tuple, 2U, (x2)), p_tmp_tuple)
  PRT_TYPE P_GEND_TYPE_0 = 
  {
    PRT_KIND_ANY,
    NULL
  };
  PRT_TYPE P_GEND_TYPE_1 = 
  {
    PRT_KIND_BOOL,
    NULL
  };
  PRT_TYPE P_GEND_TYPE_2 = 
  {
    PRT_KIND_INT,
    NULL
  };
  PRT_TYPE P_GEND_TYPE_3 = 
  {
    PRT_KIND_NULL,
    NULL
  };
  PRT_TYPE P_GEND_TYPE_4 = 
  {
    PRT_KIND_MACHINE,
    NULL
  };
  PRT_MAPTYPE P_GEND_TYPE_MAP_5 = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_0
  };
  PRT_TYPE P_GEND_TYPE_5 = 
  {
    PRT_KIND_MAP,
    &P_GEND_TYPE_MAP_5
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_6[] = 
  {
    "a"
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
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_6
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_7[] = 
  {
    "a"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_7[] = 
  {
    &P_GEND_TYPE_2
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
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_7
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_8[] = 
  {
    "battery"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_8[] = 
  {
    &P_GEND_TYPE_2
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
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_8
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_9[] = 
  {
    "currLoc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_9[] = 
  {
    &P_GEND_TYPE_2
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
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_9
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_10[] = 
  {
    "d"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_10[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_10 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_10,
    P_GEND_TYPE_NMDTUP_TARR_10
  };
  PRT_TYPE P_GEND_TYPE_10 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_10
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_11[] = 
  {
    "dest"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_11[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_11 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_11,
    P_GEND_TYPE_NMDTUP_TARR_11
  };
  PRT_TYPE P_GEND_TYPE_11 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_11
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_12[] = 
  {
    "envM"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_12[] = 
  {
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_12 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_12,
    P_GEND_TYPE_NMDTUP_TARR_12
  };
  PRT_TYPE P_GEND_TYPE_12 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_12
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_13[] = 
  {
    "envState"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_13[] = 
  {
    &P_GEND_TYPE_0
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_13 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_13,
    P_GEND_TYPE_NMDTUP_TARR_13
  };
  PRT_TYPE P_GEND_TYPE_13 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_13
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_14[] = 
  {
    "envState"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_14[] = 
  {
    &P_GEND_TYPE_3
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_14 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_14,
    P_GEND_TYPE_NMDTUP_TARR_14
  };
  PRT_TYPE P_GEND_TYPE_14 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_14
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_15[] = 
  {
    "herdingMice"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_15[] = 
  {
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_15 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_15,
    P_GEND_TYPE_NMDTUP_TARR_15
  };
  PRT_TYPE P_GEND_TYPE_15 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_15
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_16[] = 
  {
    "isMicePresent"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_16[] = 
  {
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_16 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_16,
    P_GEND_TYPE_NMDTUP_TARR_16
  };
  PRT_TYPE P_GEND_TYPE_16 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_16
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_17[] = 
  {
    "iter"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_17[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_17 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_17,
    P_GEND_TYPE_NMDTUP_TARR_17
  };
  PRT_TYPE P_GEND_TYPE_17 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_17
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_18[] = 
  {
    "loc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_18[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_18 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_18,
    P_GEND_TYPE_NMDTUP_TARR_18
  };
  PRT_TYPE P_GEND_TYPE_18 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_18
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_19[] = 
  {
    "rloc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_19[] = 
  {
    &P_GEND_TYPE_2
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
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_19
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_20[] = 
  {
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_20[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_20 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_20,
    P_GEND_TYPE_NMDTUP_TARR_20
  };
  PRT_TYPE P_GEND_TYPE_20 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_20
  };
  PRT_SEQTYPE P_GEND_TYPE_SEQ_21 = 
  {
    &P_GEND_TYPE_2
  };
  PRT_TYPE P_GEND_TYPE_21 = 
  {
    PRT_KIND_SEQ,
    (PRT_MAPTYPE *)&P_GEND_TYPE_SEQ_21
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_22[] = 
  {
    &P_GEND_TYPE_2
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_22 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_22
  };
  PRT_TYPE P_GEND_TYPE_22 = 
  {
    PRT_KIND_TUPLE,
    (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_22
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_23[] = 
  {
    &P_GEND_TYPE_4
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_23 = 
  {
    1,
    P_GEND_TYPE_TUP_ARR_23
  };
  PRT_TYPE P_GEND_TYPE_23 = 
  {
    PRT_KIND_TUPLE,
    (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_23
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_24[] = 
  {
    "c",
    "d"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_24[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_24 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_24,
    P_GEND_TYPE_NMDTUP_TARR_24
  };
  PRT_TYPE P_GEND_TYPE_24 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_24
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_25[] = 
  {
    "currentObstacles"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_25[] = 
  {
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_25 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_25,
    P_GEND_TYPE_NMDTUP_TARR_25
  };
  PRT_TYPE P_GEND_TYPE_25 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_25
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_26[] = 
  {
    "destination",
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_26[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_26 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_26,
    P_GEND_TYPE_NMDTUP_TARR_26
  };
  PRT_TYPE P_GEND_TYPE_26 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_26
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_27[] = 
  {
    "herdingCat",
    "herdingMice"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_27[] = 
  {
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_27 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_27,
    P_GEND_TYPE_NMDTUP_TARR_27
  };
  PRT_TYPE P_GEND_TYPE_27 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_27
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_28[] = 
  {
    "isCatPresent",
    "isMicePresent"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_28[] = 
  {
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_28 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_28,
    P_GEND_TYPE_NMDTUP_TARR_28
  };
  PRT_TYPE P_GEND_TYPE_28 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_28
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_29[] = 
  {
    "loc",
    "battery"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_29[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_29 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_29,
    P_GEND_TYPE_NMDTUP_TARR_29
  };
  PRT_TYPE P_GEND_TYPE_29 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_29
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_30[] = 
  {
    "loc",
    "envState"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_30[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_0
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_30 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_30,
    P_GEND_TYPE_NMDTUP_TARR_30
  };
  PRT_TYPE P_GEND_TYPE_30 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_30
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_31[] = 
  {
    "loc",
    "envState"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_31[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_3
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_31 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_31,
    P_GEND_TYPE_NMDTUP_TARR_31
  };
  PRT_TYPE P_GEND_TYPE_31 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_31
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_32[] = 
  {
    "obs"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_32[] = 
  {
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_32 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_32,
    P_GEND_TYPE_NMDTUP_TARR_32
  };
  PRT_TYPE P_GEND_TYPE_32 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_32
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_33[] = 
  {
    "obstacles"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_33[] = 
  {
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_33 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_33,
    P_GEND_TYPE_NMDTUP_TARR_33
  };
  PRT_TYPE P_GEND_TYPE_33 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_33
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_34[] = 
  {
    "retVal",
    "iter"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_34[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_34 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_34,
    P_GEND_TYPE_NMDTUP_TARR_34
  };
  PRT_TYPE P_GEND_TYPE_34 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_34
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_35[] = 
  {
    "robotStManager",
    "currLoc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_35[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_35 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_35,
    P_GEND_TYPE_NMDTUP_TARR_35
  };
  PRT_TYPE P_GEND_TYPE_35 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_35
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_36[] = 
  {
    "rtStateManager",
    "loc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_36[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_36 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_36,
    P_GEND_TYPE_NMDTUP_TARR_36
  };
  PRT_TYPE P_GEND_TYPE_36 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_36
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_37[] = 
  {
    "src",
    "dest"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_37[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_37 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_37,
    P_GEND_TYPE_NMDTUP_TARR_37
  };
  PRT_TYPE P_GEND_TYPE_37 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_37
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_38[] = 
  {
    "steps"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_38[] = 
  {
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_38 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_38,
    P_GEND_TYPE_NMDTUP_TARR_38
  };
  PRT_TYPE P_GEND_TYPE_38 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_38
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_39[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_39 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_39
  };
  PRT_TYPE P_GEND_TYPE_39 = 
  {
    PRT_KIND_TUPLE,
    (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_39
  };
  PRT_TYPE *P_GEND_TYPE_TUP_ARR_40[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_4
  };
  PRT_TUPTYPE P_GEND_TYPE_TUP_40 = 
  {
    2,
    P_GEND_TYPE_TUP_ARR_40
  };
  PRT_TYPE P_GEND_TYPE_40 = 
  {
    PRT_KIND_TUPLE,
    (PRT_MAPTYPE *)&P_GEND_TYPE_TUP_40
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_41[] = 
  {
    "dest",
    "obs"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_41[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_41 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_41,
    P_GEND_TYPE_NMDTUP_TARR_41
  };
  PRT_TYPE P_GEND_TYPE_41 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_41
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_42[] = 
  {
    "dest",
    "steps"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_42[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_42 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_42,
    P_GEND_TYPE_NMDTUP_TARR_42
  };
  PRT_TYPE P_GEND_TYPE_42 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_42
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_43[] = 
  {
    "endConfiguration",
    "currentObstacles"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_43[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_43 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_43,
    P_GEND_TYPE_NMDTUP_TARR_43
  };
  PRT_TYPE P_GEND_TYPE_43 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_43
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_44[] = 
  {
    "herdingDog",
    "herdingCat",
    "herdingMice"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_44[] = 
  {
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_44 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_44,
    P_GEND_TYPE_NMDTUP_TARR_44
  };
  PRT_TYPE P_GEND_TYPE_44 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_44
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_45[] = 
  {
    "isDogPresent",
    "isCatPresent",
    "isMicePresent"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_45[] = 
  {
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1,
    &P_GEND_TYPE_1
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_45 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_45,
    P_GEND_TYPE_NMDTUP_TARR_45
  };
  PRT_TYPE P_GEND_TYPE_45 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_45
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_46[] = 
  {
    "robot",
    "robotStManager",
    "currLoc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_46[] = 
  {
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_4,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_46 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_46,
    P_GEND_TYPE_NMDTUP_TARR_46
  };
  PRT_TYPE P_GEND_TYPE_46 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_46
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_47[] = 
  {
    "scanLocations",
    "iter"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_47[] = 
  {
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_47 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_47,
    P_GEND_TYPE_NMDTUP_TARR_47
  };
  PRT_TYPE P_GEND_TYPE_47 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_47
  };
  PRT_MAPTYPE P_GEND_TYPE_MAP_48 = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_45
  };
  PRT_TYPE P_GEND_TYPE_48 = 
  {
    PRT_KIND_MAP,
    &P_GEND_TYPE_MAP_48
  };
  PRT_MAPTYPE P_GEND_TYPE_MAP_49 = 
  {
    &P_GEND_TYPE_39,
    &P_GEND_TYPE_21
  };
  PRT_TYPE P_GEND_TYPE_49 = 
  {
    PRT_KIND_MAP,
    &P_GEND_TYPE_MAP_49
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_50[] = 
  {
    "plan",
    "destination",
    "source"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_50[] = 
  {
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_50 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_50,
    P_GEND_TYPE_NMDTUP_TARR_50
  };
  PRT_TYPE P_GEND_TYPE_50 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_50
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_51[] = 
  {
    "robot",
    "envState"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_51[] = 
  {
    &P_GEND_TYPE_29,
    &P_GEND_TYPE_0
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_51 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_51,
    P_GEND_TYPE_NMDTUP_TARR_51
  };
  PRT_TYPE P_GEND_TYPE_51 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_51
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_52[] = 
  {
    "robotst",
    "envM"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_52[] = 
  {
    &P_GEND_TYPE_29,
    &P_GEND_TYPE_4
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_52 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_52,
    P_GEND_TYPE_NMDTUP_TARR_52
  };
  PRT_TYPE P_GEND_TYPE_52 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_52
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_53[] = 
  {
    "source",
    "dest",
    "obs"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_53[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_53 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_53,
    P_GEND_TYPE_NMDTUP_TARR_53
  };
  PRT_TYPE P_GEND_TYPE_53 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_53
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_54[] = 
  {
    "src",
    "dest",
    "steps"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_54[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_54 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_54,
    P_GEND_TYPE_NMDTUP_TARR_54
  };
  PRT_TYPE P_GEND_TYPE_54 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_54
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_55[] = 
  {
    "startConfiguration",
    "endConfiguration",
    "currentObstacles"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_55[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_55 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_55,
    P_GEND_TYPE_NMDTUP_TARR_55
  };
  PRT_TYPE P_GEND_TYPE_55 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_55
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_56[] = 
  {
    "AllMotionPlans"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_56[] = 
  {
    &P_GEND_TYPE_49
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_56 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_56,
    P_GEND_TYPE_NMDTUP_TARR_56
  };
  PRT_TYPE P_GEND_TYPE_56 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_56
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_57[] = 
  {
    "obstacles",
    "scanLocations",
    "iter"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_57[] = 
  {
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_2
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_57 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_57,
    P_GEND_TYPE_NMDTUP_TARR_57
  };
  PRT_TYPE P_GEND_TYPE_57 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_57
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_58[] = 
  {
    "staticGoalLoc"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_58[] = 
  {
    &P_GEND_TYPE_48
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_58 = 
  {
    1,
    P_GEND_TYPE_NMDTUP_NARR_58,
    P_GEND_TYPE_NMDTUP_TARR_58
  };
  PRT_TYPE P_GEND_TYPE_58 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_58
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_59[] = 
  {
    "scanLocations",
    "AllMotionPlans"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_59[] = 
  {
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_49
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_59 = 
  {
    2,
    P_GEND_TYPE_NMDTUP_NARR_59,
    P_GEND_TYPE_NMDTUP_TARR_59
  };
  PRT_TYPE P_GEND_TYPE_59 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_59
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_60[] = 
  {
    "tempSeq",
    "scanLocations",
    "AllMotionPlans"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_60[] = 
  {
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_49
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_60 = 
  {
    3,
    P_GEND_TYPE_NMDTUP_NARR_60,
    P_GEND_TYPE_NMDTUP_TARR_60
  };
  PRT_TYPE P_GEND_TYPE_60 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_60
  };
  PRT_STRING P_GEND_TYPE_NMDTUP_NARR_61[] = 
  {
    "iter",
    "tempSeq",
    "scanLocations",
    "AllMotionPlans"
  };
  PRT_TYPE *P_GEND_TYPE_NMDTUP_TARR_61[] = 
  {
    &P_GEND_TYPE_2,
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_21,
    &P_GEND_TYPE_49
  };
  PRT_NMDTUPTYPE P_GEND_TYPE_NMDTUP_61 = 
  {
    4,
    P_GEND_TYPE_NMDTUP_NARR_61,
    P_GEND_TYPE_NMDTUP_TARR_61
  };
  PRT_TYPE P_GEND_TYPE_61 = 
  {
    PRT_KIND_NMDTUP,
    (PRT_MAPTYPE *)&P_GEND_TYPE_NMDTUP_61
  };
  PRT_VALUE P_GEND_VALUE_0 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_BatteryLow
  };
  PRT_VALUE P_GEND_VALUE_1 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_CANCEL_FAILURE
  };
  PRT_VALUE P_GEND_VALUE_2 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_CANCEL_SUCCESS
  };
  PRT_VALUE P_GEND_VALUE_3 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_CancelPlan
  };
  PRT_VALUE P_GEND_VALUE_4 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_CurrentState
  };
  PRT_VALUE P_GEND_VALUE_5 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_EnvEventDetected
  };
  PRT_VALUE P_GEND_VALUE_6 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_EnvState
  };
  PRT_VALUE P_GEND_VALUE_7 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_ExecutePlan
  };
  PRT_VALUE P_GEND_VALUE_8 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_FailureToComputePlan
  };
  PRT_VALUE P_GEND_VALUE_9 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_GeneratePlanFor
  };
  PRT_VALUE P_GEND_VALUE_10 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_GetEnv
  };
  PRT_VALUE P_GEND_VALUE_11 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_GetRobotState
  };
  PRT_VALUE P_GEND_VALUE_12 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_hCat
  };
  PRT_VALUE P_GEND_VALUE_13 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_hDog
  };
  PRT_VALUE P_GEND_VALUE_14 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_hMice
  };
  PRT_VALUE P_GEND_VALUE_15 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_sCat
  };
  PRT_VALUE P_GEND_VALUE_16 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_sDog
  };
  PRT_VALUE P_GEND_VALUE_17 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_M_sMice
  };
  PRT_VALUE P_GEND_VALUE_18 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_MotionPlanFor
  };
  PRT_VALUE P_GEND_VALUE_19 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_ReDo
  };
  PRT_VALUE P_GEND_VALUE_20 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_ReachedDestination
  };
  PRT_VALUE P_GEND_VALUE_21 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_TIMEOUT
  };
  PRT_VALUE P_GEND_VALUE_22 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_UNIT
  };
  PRT_VALUE P_GEND_VALUE_23 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_UpdateRobotState
  };
  PRT_VALUE P_GEND_VALUE_24 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_continueCurrentHerding
  };
  PRT_VALUE P_GEND_VALUE_25 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_doScanning
  };
  PRT_VALUE P_GEND_VALUE_26 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_done
  };
  PRT_VALUE P_GEND_VALUE_27 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_initial_setup
  };
  PRT_VALUE P_GEND_VALUE_28 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_local
  };
  PRT_VALUE P_GEND_VALUE_29 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_startNewHerding
  };
  PRT_VALUE P_GEND_VALUE_30 = 
  {
    PRT_VALKIND_EVENT,
    P_EVENT_success
  };
  PRT_VALUE P_GEND_VALUE_31 = 
  {
    PRT_VALKIND_INT,
    0U
  };
  PRT_VALUE P_GEND_VALUE_32 = 
  {
    PRT_VALKIND_INT,
    1U
  };
  PRT_VALUE P_GEND_VALUE_33 = 
  {
    PRT_VALKIND_INT,
    2U
  };
  PRT_VALUE P_GEND_VALUE_34 = 
  {
    PRT_VALKIND_INT,
    3U
  };
  PRT_VALUE P_GEND_VALUE_35 = 
  {
    PRT_VALKIND_INT,
    4U
  };
  PRT_VALUE P_GEND_VALUE_36 = 
  {
    PRT_VALKIND_INT,
    5U
  };
  PRT_VALUE P_GEND_VALUE_37 = 
  {
    PRT_VALKIND_INT,
    6U
  };
  PRT_VALUE P_GEND_VALUE_38 = 
  {
    PRT_VALKIND_INT,
    7U
  };
  PRT_VALUE P_GEND_VALUE_39 = 
  {
    PRT_VALKIND_INT,
    9U
  };
  PRT_VALUE P_GEND_VALUE_40 = 
  {
    PRT_VALKIND_INT,
    10U
  };
  PRT_VALUE P_GEND_VALUE_41 = 
  {
    PRT_VALKIND_INT,
    11U
  };
  PRT_VALUE P_GEND_VALUE_42 = 
  {
    PRT_VALKIND_INT,
    13U
  };
  PRT_VALUE P_GEND_VALUE_43 = 
  {
    PRT_VALKIND_INT,
    15U
  };
  PRT_VALUE P_GEND_VALUE_44 = 
  {
    PRT_VALKIND_INT,
    16U
  };
  PRT_VALUE P_GEND_VALUE_45 = 
  {
    PRT_VALKIND_INT,
    20U
  };
  PRT_VALUE P_GEND_VALUE_46 = 
  {
    PRT_VALKIND_INT,
    30U
  };
  PRT_VALUE P_GEND_VALUE_47 = 
  {
    PRT_VALKIND_BOOL,
    PRT_FALSE
  };
  PRT_VALUE P_GEND_VALUE_48 = 
  {
    PRT_VALKIND_EVENT,
    PRT_SPECIAL_EVENT_HALT
  };
  PRT_VALUE P_GEND_VALUE_49 = 
  {
    PRT_VALKIND_NULL,
    PRT_SPECIAL_EVENT_NULL
  };
  PRT_VALUE P_GEND_VALUE_50 = 
  {
    PRT_VALKIND_BOOL,
    PRT_TRUE
  };
  PRT_EVENTDECL P_GEND_EVENTS[] = 
  {
    
    {
        _P_EVENT_NULL,
        "null",
        0U,
        &P_GEND_TYPE_3,
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
        P_EVENT_BatteryLow,
        "BatteryLow",
        4294967295U,
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_EVENT_CANCEL,
        "CANCEL",
        4294967295U,
        &P_GEND_TYPE_3,
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
        P_EVENT_CancelOperation,
        "CancelOperation",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_CancelPlan,
        "CancelPlan",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_CancelSucess,
        "CancelSucess",
        4294967295U,
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_EVENT_CurrentState,
        "CurrentState",
        2U,
        &P_GEND_TYPE_51,
        0U,
        NULL
    },
    
    {
        P_EVENT_EnvEventDetected,
        "EnvEventDetected",
        1U,
        &P_GEND_TYPE_30,
        0U,
        NULL
    },
    
    {
        P_EVENT_EnvState,
        "EnvState",
        4294967295U,
        &P_GEND_TYPE_30,
        0U,
        NULL
    },
    
    {
        P_EVENT_ExecutePlan,
        "ExecutePlan",
        4294967295U,
        &P_GEND_TYPE_38,
        0U,
        NULL
    },
    
    {
        P_EVENT_FailureExecuting,
        "FailureExecuting",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_FailureToComputePlan,
        "FailureToComputePlan",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_GeneratePlanFor,
        "GeneratePlanFor",
        4294967295U,
        &P_GEND_TYPE_37,
        0U,
        NULL
    },
    
    {
        P_EVENT_GetEnv,
        "GetEnv",
        4294967295U,
        &P_GEND_TYPE_36,
        0U,
        NULL
    },
    
    {
        P_EVENT_GetRobotState,
        "GetRobotState",
        2U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_hCat,
        "M_hCat",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_hDog,
        "M_hDog",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_hMice,
        "M_hMice",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_rCat,
        "M_rCat",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_rDog,
        "M_rDog",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_rMice,
        "M_rMice",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_sCat,
        "M_sCat",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_sDog,
        "M_sDog",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_M_sMice,
        "M_sMice",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_MotionPlanFor,
        "MotionPlanFor",
        4294967295U,
        &P_GEND_TYPE_54,
        0U,
        NULL
    },
    
    {
        P_EVENT_ReDo,
        "ReDo",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_ReachedDestination,
        "ReachedDestination",
        4294967295U,
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_EVENT_START,
        "START",
        4294967295U,
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_EVENT_SetEnv,
        "SetEnv",
        4294967295U,
        &P_GEND_TYPE_30,
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
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_UpdateRobotState,
        "UpdateRobotState",
        4294967295U,
        &P_GEND_TYPE_29,
        0U,
        NULL
    },
    
    {
        P_EVENT_continueCurrentHerding,
        "continueCurrentHerding",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_doScanning,
        "doScanning",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_done,
        "done",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_infer,
        "infer",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_initial_setup,
        "initial_setup",
        4294967295U,
        &P_GEND_TYPE_0,
        0U,
        NULL
    },
    
    {
        P_EVENT_local,
        "local",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_newPlan,
        "newPlan",
        4294967295U,
        &P_GEND_TYPE_21,
        0U,
        NULL
    },
    
    {
        P_EVENT_startNewHerding,
        "startNewHerding",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    },
    
    {
        P_EVENT_success,
        "success",
        4294967295U,
        &P_GEND_TYPE_3,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_DriverMachine[] = 
  {
    
    {
        P_VAR_DriverMachine_envMachine,
        P_MACHINE_DriverMachine,
        "envMachine",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_DriverMachine_robot,
        P_MACHINE_DriverMachine,
        "robot",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_DriverMachine_robotStMng,
        P_MACHINE_DriverMachine,
        "robotStMng",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_MotionPlanExecutor[] = 
  {
    
    {
        P_VAR_MotionPlanExecutor_RState,
        P_MACHINE_MotionPlanExecutor,
        "RState",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_MotionPlanExecutor_RobotTP,
        P_MACHINE_MotionPlanExecutor,
        "RobotTP",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_MotionPlanExecutor_currentLocation,
        P_MACHINE_MotionPlanExecutor,
        "currentLocation",
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_VAR_MotionPlanExecutor_currentPlan,
        P_MACHINE_MotionPlanExecutor,
        "currentPlan",
        &P_GEND_TYPE_21,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_MotionPlanner[] = 
  {
    
    {
        P_VAR_MotionPlanner_AllMotionPlans,
        P_MACHINE_MotionPlanner,
        "AllMotionPlans",
        &P_GEND_TYPE_49,
        0U,
        NULL
    },
    
    {
        P_VAR_MotionPlanner_Obstacles,
        P_MACHINE_MotionPlanner,
        "Obstacles",
        &P_GEND_TYPE_21,
        0U,
        NULL
    },
    
    {
        P_VAR_MotionPlanner_RobotTP,
        P_MACHINE_MotionPlanner,
        "RobotTP",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_RobotStateManager[] = 
  {
    
    {
        P_VAR_RobotStateManager_EnvMachine,
        P_MACHINE_RobotStateManager,
        "EnvMachine",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotStateManager_batteryLevel,
        P_MACHINE_RobotStateManager,
        "batteryLevel",
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotStateManager_currentLocation,
        P_MACHINE_RobotStateManager,
        "currentLocation",
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotStateManager_sensingMachine,
        P_MACHINE_RobotStateManager,
        "sensingMachine",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_RobotTaskPlanner[] = 
  {
    
    {
        P_VAR_RobotTaskPlanner_currentRobotState,
        P_MACHINE_RobotTaskPlanner,
        "currentRobotState",
        &P_GEND_TYPE_29,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_currentSensorState,
        P_MACHINE_RobotTaskPlanner,
        "currentSensorState",
        &P_GEND_TYPE_45,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_envMachine,
        P_MACHINE_RobotTaskPlanner,
        "envMachine",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_herdingState,
        P_MACHINE_RobotTaskPlanner,
        "herdingState",
        &P_GEND_TYPE_44,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_herdingTogether,
        P_MACHINE_RobotTaskPlanner,
        "herdingTogether",
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_motionPlanEx,
        P_MACHINE_RobotTaskPlanner,
        "motionPlanEx",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_motionPlanner,
        P_MACHINE_RobotTaskPlanner,
        "motionPlanner",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_nextLocation,
        P_MACHINE_RobotTaskPlanner,
        "nextLocation",
        &P_GEND_TYPE_2,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_robotStMng,
        P_MACHINE_RobotTaskPlanner,
        "robotStMng",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_scanLocations,
        P_MACHINE_RobotTaskPlanner,
        "scanLocations",
        &P_GEND_TYPE_21,
        0U,
        NULL
    },
    
    {
        P_VAR_RobotTaskPlanner_senseInfer,
        P_MACHINE_RobotTaskPlanner,
        "senseInfer",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_VARDECL P_GEND_VARS_SenseAndInfer[] = 
  {
    
    {
        P_VAR_SenseAndInfer_currentRobotState,
        P_MACHINE_SenseAndInfer,
        "currentRobotState",
        &P_GEND_TYPE_51,
        0U,
        NULL
    },
    
    {
        P_VAR_SenseAndInfer_robotStManager,
        P_MACHINE_SenseAndInfer,
        "robotStManager",
        &P_GEND_TYPE_4,
        0U,
        NULL
    },
    
    {
        P_VAR_SenseAndInfer_robotTP,
        P_MACHINE_SenseAndInfer,
        "robotTP",
        &P_GEND_TYPE_4,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_MotionPlanExecutor_Init[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanExecutor_Init,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_local,
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_FUN_MotionPlanExecutor_ANON2,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_MotionPlanExecutor_StartExecutingPlan[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_CancelPlan,
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_FUN_MotionPlanExecutor_ANON2,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_done,
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_FUN_MotionPlanExecutor_ANON3,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_local,
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_FUN_MotionPlanExecutor_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_MotionPlanExecutor_WaitForCommands[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_ExecutePlan,
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_FUN_MotionPlanExecutor_ANON5,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_MotionPlanner_Init[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanner_Init,
        P_MACHINE_MotionPlanner,
        P_EVENT_local,
        P_STATE_MotionPlanner_WaitForCommands,
        P_FUN_MotionPlanner_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotStateManager_Init[] = 
  {
    
    {
        0,
        P_STATE_RobotStateManager_Init,
        P_MACHINE_RobotStateManager,
        P_EVENT_initial_setup,
        P_STATE_RobotStateManager_WaitForCommands,
        P_FUN_RobotStateManager_ANON0,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotStateManager_WaitForCommands[] = 
  {
    
    {
        0,
        P_STATE_RobotStateManager_WaitForCommands,
        P_MACHINE_RobotStateManager,
        P_EVENT_GetRobotState,
        P_STATE_RobotStateManager_GetStateFromEnvMachine,
        _P_FUN_RobotStateManager_PUSH_OR_IGN,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotTaskPlanner_Init[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_Init,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_local,
        P_STATE_RobotTaskPlanner_SetUpSystem,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotTaskPlanner_LowBatteryDetected[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_BatteryLow,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_FUN_RobotTaskPlanner_CancelCurrentExecution,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_MotionPlanFor,
        P_STATE_RobotTaskPlanner_ExecutePlan,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_ReDo,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        3,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_success,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotTaskPlanner_ScanningModeOfOperation[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_BatteryLow,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_FUN_RobotTaskPlanner_CancelCurrentExecution,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_EnvEventDetected,
        P_STATE_RobotTaskPlanner_TakeActionOnEnvEventDetected,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_MotionPlanFor,
        P_STATE_RobotTaskPlanner_ExecutePlan,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        3,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_ReDo,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        4,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_startNewHerding,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_FUN_RobotTaskPlanner_CancelCurrentExecution,
        0U,
        NULL
    },
    
    {
        5,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_success,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotTaskPlanner_SelectGoalLocationAndComputePlan[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_BatteryLow,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_FUN_RobotTaskPlanner_CancelCurrentExecution,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_EnvEventDetected,
        P_STATE_RobotTaskPlanner_TakeActionOnEnvEventDetected,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_MotionPlanFor,
        P_STATE_RobotTaskPlanner_ExecutePlan,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        3,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_ReDo,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        4,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_doScanning,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_RobotTaskPlanner_SetUpSystem[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_SetUpSystem,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_local,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_SenseAndInfer_Init[] = 
  {
    
    {
        0,
        P_STATE_SenseAndInfer_Init,
        P_MACHINE_SenseAndInfer,
        P_EVENT_local,
        P_STATE_SenseAndInfer_PeriodicallySenseUpdate,
        P_FUN_SenseAndInfer_ANON1,
        0U,
        NULL
    }
  };
  PRT_TRANSDECL P_GEND_TRANS_SenseAndInfer_PeriodicallySenseUpdate[] = 
  {
    
    {
        0,
        P_STATE_SenseAndInfer_PeriodicallySenseUpdate,
        P_MACHINE_SenseAndInfer,
        _P_EVENT_NULL,
        P_STATE_SenseAndInfer_SenseEnvironment,
        _P_FUN_SenseAndInfer_PUSH_OR_IGN,
        0U,
        NULL
    }
  };
  PRT_VALUE *P_FUN_BATTERY_CHARGE_LOCATION_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_BATTERY_THRESHOLD_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_CAT_CAGE_LOC_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_CAT_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_DOG_CAGE_LOC_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_DOG_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_EventDetected_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_GetStaticGoals_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_GetStaticObstacles_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_MICE_CAGE_LOC_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_MICE_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_MotionPlanner_ComputeMotionPlanAndSend_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_ROBOT_SCAN_LOCATIONS_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_ROBOT_START_STATE_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_RobotTaskPlanner_CancelCurrentExecution_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_RobotTaskPlanner_GetNextScanLocation_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_RobotTaskPlanner_UpdateCurrentRobotState_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_SIZE_OF_GRID_IMPL(PRT_MACHINEINST *context);

  PRT_VALUE *P_FUN_SenseAndInfer_InferCurrentStateAndInformTPorMP_IMPL(PRT_MACHINEINST *context);

  PRT_DODECL P_GEND_DOS_MotionPlanExecutor_WaitForCommands[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_MACHINE_MotionPlanExecutor,
        P_EVENT_CancelPlan,
        _P_FUN_MotionPlanExecutor_PUSH_OR_IGN,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_MotionPlanner_WaitForCommands[] = 
  {
    
    {
        0,
        P_STATE_MotionPlanner_WaitForCommands,
        P_MACHINE_MotionPlanner,
        P_EVENT_GeneratePlanFor,
        P_FUN_MotionPlanner_ComputeMotionPlanAndSend,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotStateManager_GetStateFromEnvMachine[] = 
  {
    
    {
        0,
        P_STATE_RobotStateManager_GetStateFromEnvMachine,
        P_MACHINE_RobotStateManager,
        P_EVENT_EnvState,
        P_FUN_RobotStateManager_ANON5,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotStateManager_WaitForCommands[] = 
  {
    
    {
        0,
        P_STATE_RobotStateManager_WaitForCommands,
        P_MACHINE_RobotStateManager,
        P_EVENT_UpdateRobotState,
        P_FUN_RobotStateManager_ANON1,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotTaskPlanner_ExecutePlan[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_ExecutePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_ReachedDestination,
        P_FUN_RobotTaskPlanner_ANON2,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotTaskPlanner_ExecutePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_continueCurrentHerding,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotTaskPlanner_LowBatteryDetected[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_FailureToComputePlan,
        P_FUN_RobotTaskPlanner_ANON11,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotTaskPlanner_ScanningModeOfOperation[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_FailureToComputePlan,
        P_FUN_RobotTaskPlanner_ANON11,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_RobotTaskPlanner_SelectGoalLocationAndComputePlan[] = 
  {
    
    {
        0,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_FailureToComputePlan,
        P_FUN_RobotTaskPlanner_ANON11,
        0U,
        NULL
    },
    
    {
        1,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_ReachedDestination,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        2,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_continueCurrentHerding,
        _P_FUN_RobotTaskPlanner_PUSH_OR_IGN,
        0U,
        NULL
    },
    
    {
        3,
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        P_EVENT_success,
        P_FUN_RobotTaskPlanner_ANON10,
        0U,
        NULL
    }
  };
  PRT_DODECL P_GEND_DOS_SenseAndInfer_PeriodicallySenseUpdate[] = 
  {
    
    {
        0,
        P_STATE_SenseAndInfer_PeriodicallySenseUpdate,
        P_MACHINE_SenseAndInfer,
        P_EVENT_GetRobotState,
        P_FUN_SenseAndInfer_ANON3,
        0U,
        NULL
    }
  };
  PRT_VALUE *P_FUN_BATTERY_CHARGE_LOCATION_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_43, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_BATTERY_THRESHOLD_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_36, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_CAT_CAGE_LOC_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_35, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_CAT_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_32, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_DOG_CAGE_LOC_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_42, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_DOG_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_DriverMachine_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_DriverMachine_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DriverMachine_envMachine, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkModel(context->process, P_MODEL_Environment, p_tmp_expr_0)->id), PRT_FALSE, &P_GEND_VALUE_49, PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DriverMachine_robotStMng, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_RobotStateManager, p_tmp_expr_2)->id), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_52, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DriverMachine_envMachine], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 19U, NULL), PRT_TRUE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_DriverMachine_robot, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_RobotTaskPlanner, p_tmp_expr_2)->id), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_40, p_tmp_expr_0, p_tmp_expr_1), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_DriverMachine_robotStMng], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_DriverMachine_envMachine], PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_48, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_EventDetected_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PRT_VALUE *p_tmp_expr_6;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (P_BOOL_EXPR(P_EXPR_6(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_5) || PrtPrimGetBool(p_tmp_expr_4)), PRT_FALSE, PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_2) || PrtPrimGetBool(p_tmp_expr_3)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_1, 2), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_45), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
    {
      p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_50, PRT_FALSE));
      goto P_EXIT_FUN;
    }
    else
    {
      p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE));
      goto P_EXIT_FUN;
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_1);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_GetStaticGoals_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_1(PrtMapUpdateEx(p_tmp_frame.locals[0U], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(&P_GEND_VALUE_33, PRT_FALSE), PRT_FALSE, P_EXPR_2(P_TUPLE_2(&P_GEND_TYPE_45, p_tmp_expr_0, p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, &P_GEND_VALUE_50, PRT_FALSE, &P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtMapUpdateEx(p_tmp_frame.locals[0U], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(&P_GEND_VALUE_36, PRT_FALSE), PRT_FALSE, P_EXPR_2(P_TUPLE_2(&P_GEND_TYPE_45, p_tmp_expr_1, p_tmp_expr_0, p_tmp_expr_0), PRT_FALSE, &P_GEND_VALUE_50, PRT_FALSE, &P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtMapUpdateEx(p_tmp_frame.locals[0U], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(&P_GEND_VALUE_40, PRT_FALSE), PRT_FALSE, P_EXPR_2(P_TUPLE_2(&P_GEND_TYPE_45, p_tmp_expr_0, p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, &P_GEND_VALUE_50, PRT_FALSE, &P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtMapUpdateEx(p_tmp_frame.locals[0U], p_tmp_stmt_1, PRT_TRUE, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_0(&P_GEND_VALUE_41, PRT_FALSE), PRT_FALSE, P_EXPR_2(P_TUPLE_2(&P_GEND_TYPE_45, p_tmp_expr_1, p_tmp_expr_0, p_tmp_expr_0), PRT_FALSE, &P_GEND_VALUE_50, PRT_FALSE, &P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_5);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_GetStaticObstacles_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[0U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_39, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_37, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
    PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
    PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
    PrtFree(p_tmp_stmt_0->valueUnion.tuple);
    PrtFree(p_tmp_stmt_0);
    P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[0U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_39, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_38, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
    PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
    PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
    PrtFree(p_tmp_stmt_0->valueUnion.tuple);
    PrtFree(p_tmp_stmt_0);
    P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[0U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_39, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_39, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
    PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
    PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
    PrtFree(p_tmp_stmt_0->valueUnion.tuple);
    PrtFree(p_tmp_stmt_0);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[0U], PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_21);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_MICE_CAGE_LOC_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_44, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_MICE_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_33, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSeqRemove(p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], p_tmp_stmt_0), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 1U)
    {
      goto L1;
    }
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_1)), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], PRT_FALSE), PRT_TRUE))
    {
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_26, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    else
    {
      p_tmp_params = P_EXPR_3(P_TUPLE_0(&P_GEND_TYPE_19, p_tmp_expr_2), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], PRT_FALSE);
      L1:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 1U, p_tmp_mach_priv, 30U, p_tmp_params);
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
      if (P_BOOL_EXPR(P_EXPR_4(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_3)), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_2), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentLocation], PRT_FALSE), PRT_TRUE))
      {
      }
      else
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentLocation], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_20, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_RobotTP], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanExecutor_RState, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_46), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanExecutor_RobotTP, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_46), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanExecutor_currentLocation, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 2), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_46), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanExecutor_ANON5_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanExecutor_currentPlan, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    if (P_BOOL_EXPR(P_EXPR_4(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_3)), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_2), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentLocation], PRT_FALSE), PRT_TRUE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_STMT_0(PrtSeqRemove(p_tmp_mach_priv->varValues[P_VAR_MotionPlanExecutor_currentPlan], p_tmp_stmt_0), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanner_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanner_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 4U)
    {
      goto L4;
    }
    if (p_tmp_frame.returnTo == 5U)
    {
      goto L5;
    }
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanner_RobotTP, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_4), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    L4:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 4U, p_tmp_mach_priv, 11U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanner_Obstacles, p_tmp_funstmt_ret, PRT_FALSE);
    L5:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 5U, p_tmp_mach_priv, 12U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_MotionPlanner_AllMotionPlans, p_tmp_funstmt_ret, PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_MotionPlanner_ComputeMotionPlanAndSend_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 7U)
    {
      goto L7;
    }
    P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    p_tmp_params = P_EXPR_3(P_TUPLE_2(&P_GEND_TYPE_53, p_tmp_expr_2, p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_MotionPlanner_Obstacles], PRT_FALSE);
    L7:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 7U, p_tmp_mach_priv, 27U, p_tmp_params);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_funstmt_ret, PRT_FALSE);
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_1)), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_0)), PRT_TRUE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE), PRT_TRUE))
    {
      if (P_BOOL_EXPR(P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE))
      {
      }
      else
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_8, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_MotionPlanner_RobotTP], PRT_FALSE), PRT_FALSE);
    }
    else
    {
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_3(P_TUPLE_2(&P_GEND_TYPE_54, p_tmp_expr_2, p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[1U], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_18, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_MotionPlanner_RobotTP], PRT_FALSE), PRT_FALSE);
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_ROBOT_SCAN_LOCATIONS_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PRT_VALUE *p_tmp_expr_6;
    PRT_VALUE *p_tmp_expr_7;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 0U)
    {
      goto L0;
    }
    P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
    L0:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 11U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetLocalVarEx(p_tmp_frame.locals, 2U, p_tmp_funstmt_ret, PRT_FALSE);
    while (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_1) < PrtPrimGetInt(p_tmp_expr_0)), PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 21U, NULL), PRT_TRUE), PRT_TRUE))
    {
      if (P_BOOL_EXPR(P_EXPR_7(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_6) && PrtPrimGetBool(p_tmp_expr_5)), PRT_FALSE, PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_4) > PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_3)), PRT_TRUE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_2), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_frame.locals[2U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSeqRemove(p_tmp_frame.locals[2U], p_tmp_stmt_0), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
      }
      else
      {
        P_STMT_0(PrtSeqInsertEx(p_tmp_frame.locals[1U], PrtTupleGetNC(p_tmp_stmt_0, 0U), PrtTupleGetNC(p_tmp_stmt_0, 1U), PRT_FALSE), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_39, p_tmp_expr_2, p_tmp_expr_0), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_frame.locals[1U], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
        PrtFree(PrtTupleGetNC(p_tmp_stmt_0, 0U));
        PrtFree(p_tmp_stmt_0->valueUnion.tuple->values);
        PrtFree(p_tmp_stmt_0->valueUnion.tuple);
        PrtFree(p_tmp_stmt_0);
      }
      P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_FALSE, &P_GEND_VALUE_32, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
    }
    p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_21);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_ROBOT_START_STATE_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_29, p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, &P_GEND_VALUE_45, PRT_FALSE, &P_GEND_VALUE_32, PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_29);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_sensingMachine, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_4), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_0)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 2U, NULL), PRT_TRUE), PRT_TRUE))
    {
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_currentLocation, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_batteryLevel, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_46, PRT_FALSE), PRT_FALSE);
    }
    else
    {
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_currentLocation, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_batteryLevel, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_2) + PrtPrimGetInt(p_tmp_expr_0)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_batteryLevel], PRT_FALSE), PRT_FALSE);
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_2(P_TUPLE_1(&P_GEND_TYPE_36, p_tmp_expr_1, p_tmp_expr_0), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_currentLocation], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_10, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_EnvMachine], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_currentLocation, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_3(PrtTupleGetNC(p_tmp_expr_2, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_52), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_batteryLevel, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_3(PrtTupleGetNC(p_tmp_expr_2, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_52), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotStateManager_EnvMachine, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_52), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_0) > PrtPrimGetInt(p_tmp_expr_1)), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_batteryLevel], PRT_FALSE), PRT_TRUE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotStateManager_ANON5_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_0)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_currentLocation], PRT_FALSE), PRT_TRUE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_5(P_TUPLE_1(&P_GEND_TYPE_51, p_tmp_expr_4, p_tmp_expr_3), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_29, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_2, 1), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_currentLocation], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_batteryLevel], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_4, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotStateManager_sensingMachine], PRT_FALSE), PRT_FALSE);
    PrtPop(p_tmp_mach_priv);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_currentRobotState, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON10_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 19U)
    {
      goto L19;
    }
    if (p_tmp_frame.returnTo == 20U)
    {
      goto L20;
    }
    if (p_tmp_frame.returnTo == 21U)
    {
      goto L21;
    }
    if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 1U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_1)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE);
    }
    else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 0U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_1)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE);
    }
    else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 2U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_1)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE);
    }
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(!PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_2)), PRT_FALSE, PrtMkIntValue(-PrtPrimGetInt(p_tmp_expr_1)), PRT_TRUE, &P_GEND_VALUE_32, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingTogether], PRT_FALSE), PRT_TRUE))
    {
      if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_1, p_tmp_expr_0)), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingTogether], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 15U, NULL), PRT_TRUE), PRT_TRUE))
      {
        L19:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 19U, p_tmp_mach_priv, 16U, NULL);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_1, p_tmp_expr_0)), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingTogether], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 6U, NULL), PRT_TRUE), PRT_TRUE))
      {
        L20:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 20U, p_tmp_mach_priv, 7U, NULL);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_2(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_1, p_tmp_expr_0)), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingTogether], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 4U, NULL), PRT_TRUE), PRT_TRUE))
      {
        L21:
        p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 21U, p_tmp_mach_priv, 7U, NULL);
        if (p_tmp_mach_priv->receive != NULL)
        {
          return p_tmp_funstmt_ret;
        }
        if (p_tmp_mach_priv->lastOperation != ReturnStatement)
        {
          goto P_EXIT_FUN;
        }
        PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
      }
      P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_herdingTogether, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtMkIntValue(-PrtPrimGetInt(p_tmp_expr_0)), PRT_FALSE, &P_GEND_VALUE_32, PRT_FALSE), PRT_FALSE);
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_19, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    else
    {
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_25, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON11_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (P_BOOL_EXPR(P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_30, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 0U)
    {
      goto L0;
    }
    if (p_tmp_frame.returnTo == 1U)
    {
      goto L1;
    }
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_envMachine, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_40), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_robotStMng, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_40), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    L0:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 19U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_currentRobotState, p_tmp_funstmt_ret, PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_herdingState, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(P_TUPLE_2(&P_GEND_TYPE_44, p_tmp_expr_0, p_tmp_expr_0, p_tmp_expr_0), PRT_FALSE, &P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
    L1:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 1U, p_tmp_mach_priv, 18U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_scanLocations, p_tmp_funstmt_ret, PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_senseInfer, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_3(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_SenseAndInfer, p_tmp_expr_2)->id), PRT_FALSE, P_TUPLE_1(&P_GEND_TYPE_40, p_tmp_expr_1, p_tmp_expr_0), PRT_TRUE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_robotStMng], PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_motionPlanner, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_1(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_MotionPlanner, p_tmp_expr_0)->id), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_motionPlanEx, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_5(PrtCloneValue(PrtMkMachine(context->process, P_MACHINE_MotionPlanExecutor, p_tmp_expr_4)->id), PRT_FALSE, P_TUPLE_2(&P_GEND_TYPE_46, p_tmp_expr_2, p_tmp_expr_1, p_tmp_expr_3), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->id, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_robotStMng], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON5_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PRT_VALUE *p_tmp_expr_6;
    PRT_VALUE *p_tmp_expr_7;
    PRT_VALUE *p_tmp_expr_8;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 4U)
    {
      goto L4;
    }
    if (p_tmp_frame.returnTo == 5U)
    {
      goto L5;
    }
    if (p_tmp_frame.returnTo == 6U)
    {
      goto L6;
    }
    if (p_tmp_frame.returnTo == 7U)
    {
      goto L7;
    }
    p_tmp_params = P_EXPR_2(P_TUPLE_0(&P_GEND_TYPE_6, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE);
    L4:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 4U, p_tmp_mach_priv, 17U, p_tmp_params);
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
    p_tmp_params = P_EXPR_2(P_TUPLE_0(&P_GEND_TYPE_6, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE);
    L5:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 5U, p_tmp_mach_priv, 17U, p_tmp_params);
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
    p_tmp_params = P_EXPR_1(P_TUPLE_0(&P_GEND_TYPE_6, p_tmp_expr_0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_nextLocation], PRT_FALSE);
    L6:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 6U, p_tmp_mach_priv, 17U, p_tmp_params);
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
    p_tmp_params = P_EXPR_2(P_TUPLE_0(&P_GEND_TYPE_6, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE);
    L7:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 7U, p_tmp_mach_priv, 17U, p_tmp_params);
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
    if (P_BOOL_EXPR(P_EXPR_8(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_7) || PrtPrimGetBool(p_tmp_expr_6)), PRT_FALSE, PrtMkBoolValue(!PrtIsEqualValue(p_tmp_expr_5, p_tmp_expr_3)), PRT_TRUE, PrtMkBoolValue(!PrtIsEqualValue(p_tmp_expr_4, p_tmp_expr_1)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_2, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_2, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_nextLocation], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE))
    {
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_19, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    else
    {
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_2(P_TUPLE_0(&P_GEND_TYPE_38, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_7, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_motionPlanEx], PRT_FALSE), PRT_FALSE);
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON6_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 2U)
    {
      goto L2;
    }
    if (p_tmp_frame.returnTo == 3U)
    {
      goto L3;
    }
    L2:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 2U, p_tmp_mach_priv, 38U, NULL);
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
    L3:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 3U, p_tmp_mach_priv, 37U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_37, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_nextLocation], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_motionPlanner], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON7_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 9U)
    {
      goto L9;
    }
    if (p_tmp_frame.returnTo == 10U)
    {
      goto L10;
    }
    L9:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 9U, p_tmp_mach_priv, 38U, NULL);
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
    L10:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 10U, p_tmp_mach_priv, 2U, NULL);
    if (p_tmp_mach_priv->receive != NULL)
    {
      return p_tmp_funstmt_ret;
    }
    if (p_tmp_mach_priv->lastOperation != ReturnStatement)
    {
      goto P_EXIT_FUN;
    }
    PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_37, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_nextLocation], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_motionPlanner], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON8_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PRT_VALUE *p_tmp_expr_6;
    PRT_VALUE *p_tmp_expr_7;
    PRT_VALUE *p_tmp_expr_8;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 11U)
    {
      goto L11;
    }
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
    L11:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 11U, p_tmp_mach_priv, 38U, NULL);
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
    if (P_BOOL_EXPR(P_EXPR_4(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_3)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_currentSensorState, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtCastValue(p_tmp_expr_1, &P_GEND_TYPE_45), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_4) || PrtPrimGetBool(p_tmp_expr_3)), PRT_FALSE, PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_1) || PrtPrimGetBool(p_tmp_expr_2)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_TRUE))
    {
      if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_2) && PrtPrimGetBool(p_tmp_expr_4)), PRT_FALSE, PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_3)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
        {
          L12:
          p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 12U, p_tmp_mach_priv, 6U, NULL);
          if (p_tmp_mach_priv->receive != NULL)
          {
            return p_tmp_funstmt_ret;
          }
          if (p_tmp_mach_priv->lastOperation != ReturnStatement)
          {
            goto P_EXIT_FUN;
          }
          PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_herdingTogether, p_tmp_funstmt_ret, PRT_FALSE);
        }
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_2) && PrtPrimGetBool(p_tmp_expr_4)), PRT_FALSE, PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_3)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
        {
          L13:
          p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 13U, p_tmp_mach_priv, 15U, NULL);
          if (p_tmp_mach_priv->receive != NULL)
          {
            return p_tmp_funstmt_ret;
          }
          if (p_tmp_mach_priv->lastOperation != ReturnStatement)
          {
            goto P_EXIT_FUN;
          }
          PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_herdingTogether, p_tmp_funstmt_ret, PRT_FALSE);
        }
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 2U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_8(PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_7) && PrtPrimGetBool(p_tmp_expr_6)), PRT_FALSE, PrtMkBoolValue(PrtPrimGetBool(p_tmp_expr_2) && PrtPrimGetBool(p_tmp_expr_5)), PRT_TRUE, PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_4)), PRT_TRUE, PrtMkBoolValue(!PrtPrimGetBool(p_tmp_expr_3)), PRT_TRUE, PrtTupleGetNC(p_tmp_expr_1, 2), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
      }
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_24, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    else
    {
      if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_FALSE))
      {
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_50, PRT_FALSE), PRT_FALSE);
        if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_FALSE))
        {
          L14:
          p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 14U, p_tmp_mach_priv, 15U, NULL);
          if (p_tmp_mach_priv->receive != NULL)
          {
            return p_tmp_funstmt_ret;
          }
          if (p_tmp_mach_priv->lastOperation != ReturnStatement)
          {
            goto P_EXIT_FUN;
          }
          PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_herdingTogether, p_tmp_funstmt_ret, PRT_FALSE);
        }
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 2U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
      }
      else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_FALSE))
      {
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_50, PRT_FALSE), PRT_FALSE);
      }
      else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], PRT_FALSE), PRT_FALSE))
      {
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], 2U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_50, PRT_FALSE), PRT_FALSE);
        P_STMT_0(PrtTupleSetEx(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentSensorState], 2U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE);
      }
      else if (P_BOOL_EXPR(P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE))
      {
      }
      else
      {
        PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
      }
      P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_29, PRT_FALSE), PRT_FALSE);
      goto P_EXIT_FUN;
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_ANON9_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
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
    L15:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 15U, p_tmp_mach_priv, 38U, NULL);
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
    if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      L16:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 16U, p_tmp_mach_priv, 7U, NULL);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
    }
    else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      L17:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 17U, p_tmp_mach_priv, 5U, NULL);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
    }
    else if (P_BOOL_EXPR(P_EXPR_1(PrtTupleGetNC(p_tmp_expr_0, 2), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_herdingState], PRT_FALSE), PRT_FALSE))
    {
      L18:
      p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 18U, p_tmp_mach_priv, 16U, NULL);
      if (p_tmp_mach_priv->receive != NULL)
      {
        return p_tmp_funstmt_ret;
      }
      if (p_tmp_mach_priv->lastOperation != ReturnStatement)
      {
        goto P_EXIT_FUN;
      }
      PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_RobotTaskPlanner_nextLocation, p_tmp_funstmt_ret, PRT_FALSE);
    }
    else if (P_BOOL_EXPR(P_EXPR_0(&P_GEND_VALUE_47, PRT_FALSE), PRT_FALSE))
    {
    }
    else
    {
      PrtHandleError(PRT_STATUS_ASSERT, p_tmp_mach_priv);
    }
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_3(P_TUPLE_1(&P_GEND_TYPE_37, p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_nextLocation], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_9, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_motionPlanner], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_CancelCurrentExecution_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_3, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_motionPlanEx], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_GetNextScanLocation_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PRT_VALUE *p_tmp_expr_5;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
    while (P_BOOL_EXPR(P_EXPR_0(&P_GEND_VALUE_50, PRT_FALSE), PRT_FALSE))
    {
      if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_0, p_tmp_expr_2)), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_scanLocations], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_0(&P_GEND_VALUE_31, PRT_FALSE), PRT_FALSE);
      }
      if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtIsEqualValue(p_tmp_expr_3, p_tmp_expr_4)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtSeqGetNC(p_tmp_expr_2, p_tmp_expr_1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_scanLocations], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_currentRobotState], PRT_FALSE), PRT_TRUE))
      {
        if (P_BOOL_EXPR(P_EXPR_5(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_3) < PrtPrimGetInt(p_tmp_expr_4)), PRT_FALSE, PrtMkIntValue(PrtSeqSizeOf(p_tmp_expr_1)), PRT_TRUE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, &P_GEND_VALUE_32, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_scanLocations], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_TRUE))
        {
          P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_4(PrtSeqGetNC(p_tmp_expr_1, p_tmp_expr_3), PRT_FALSE, PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_2)), PRT_TRUE, &P_GEND_VALUE_32, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_scanLocations], PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
        }
        else
        {
          P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 1U, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtSeqGetNC(p_tmp_expr_0, p_tmp_expr_1), PRT_FALSE, &P_GEND_VALUE_31, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_scanLocations], PRT_FALSE), PRT_FALSE);
        }
        p_tmp_ret = PrtCloneValue(P_EXPR_0(p_tmp_frame.locals[1U], PRT_FALSE));
        goto P_EXIT_FUN;
      }
      else
      {
        P_STMT_0(PrtSetLocalVarEx(p_tmp_frame.locals, 0U, p_tmp_stmt_0, !PRT_TRUE), P_EXPR_2(PrtMkIntValue(PrtPrimGetInt(p_tmp_expr_0) + PrtPrimGetInt(p_tmp_expr_1)), PRT_FALSE, &P_GEND_VALUE_32, PRT_FALSE, p_tmp_frame.locals[0U], PRT_FALSE), PRT_FALSE);
      }
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_RobotTaskPlanner_UpdateCurrentRobotState_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 8U)
    {
      goto L8;
    }
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_11, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_RobotTaskPlanner_senseInfer], PRT_FALSE), PRT_FALSE);
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
    PrtPopEvent(p_tmp_mach_priv);
    p_tmp_frame.rcase = NULL;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SIZE_OF_GRID_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    p_tmp_ret = PrtCloneValue(P_EXPR_0(&P_GEND_VALUE_44, PRT_FALSE));
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_ret == NULL)
    {
      return PrtMkDefaultValue(&P_GEND_TYPE_2);
    }
    else
    {
      return p_tmp_ret;
    }
  }

  PRT_VALUE *P_FUN_SenseAndInfer_ANON0_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_SenseAndInfer_currentRobotState, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_1(PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_51), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SenseAndInfer_ANON1_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SenseAndInfer_ANON2_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_SenseAndInfer_robotTP, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_40), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_0(PrtSetGlobalVarEx(p_tmp_mach_priv, P_VAR_SenseAndInfer_robotStManager, p_tmp_stmt_0, !PRT_FALSE), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtCastValue(p_tmp_expr_0, &P_GEND_TYPE_40), PRT_FALSE, PrtGetCurrentPayload(p_tmp_mach_priv), PRT_FALSE), PRT_FALSE);
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_0(p_tmp_mach_priv->id, PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_27, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotStManager], PRT_FALSE), PRT_FALSE);
    P_STMT_1(PrtRaise(p_tmp_mach_priv, p_tmp_stmt_0, p_tmp_stmt_1), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_28, PRT_FALSE), PRT_FALSE);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SenseAndInfer_ANON3_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 0U)
    {
      goto L0;
    }
    if (p_tmp_frame.returnTo == 2U)
    {
      goto L2;
    }
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_11, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotStManager], PRT_FALSE), PRT_FALSE);
    L0:
    if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 0U))
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
    PrtPopEvent(p_tmp_mach_priv);
    p_tmp_frame.rcase = NULL;
    L1:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 1U, p_tmp_mach_priv, 29U, NULL);
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
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_4, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotTP], PRT_FALSE), PRT_FALSE);
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SenseAndInfer_ANON4_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (p_tmp_frame.returnTo == 2U)
    {
      goto L2;
    }
    if (p_tmp_frame.returnTo == 4U)
    {
      goto L4;
    }
    P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), &P_GEND_VALUE_49, PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_11, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotStManager], PRT_FALSE), PRT_FALSE);
    L2:
    if (p_tmp_frame.rcase == NULL && !PrtReceive(p_tmp_mach_priv, &p_tmp_frame, 2U))
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
    PrtPopEvent(p_tmp_mach_priv);
    p_tmp_frame.rcase = NULL;
    L3:
    p_tmp_funstmt_ret = PrtWrapFunStmt(&p_tmp_frame, 3U, p_tmp_mach_priv, 29U, NULL);
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
    PrtPop(p_tmp_mach_priv);
    goto P_EXIT_FUN;
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_VALUE *P_FUN_SenseAndInfer_InferCurrentStateAndInformTPorMP_IMPL(PRT_MACHINEINST *context)
  {
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_BOOLEAN p_tmp_bool;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_VALUE *p_tmp_tuple;
    PRT_VALUE *p_tmp_funstmt_ret;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    PRT_VALUE *p_tmp_stmt_0;
    PRT_VALUE *p_tmp_stmt_1;
    PRT_VALUE *p_tmp_stmt_2;
    PRT_VALUE *p_tmp_expr_0;
    PRT_VALUE *p_tmp_expr_1;
    PRT_VALUE *p_tmp_expr_2;
    PRT_VALUE *p_tmp_expr_3;
    PRT_VALUE *p_tmp_expr_4;
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    if (P_BOOL_EXPR(P_EXPR_4(PrtMkBoolValue(PrtPrimGetInt(p_tmp_expr_3) < PrtPrimGetInt(p_tmp_expr_0)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_2, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_1, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE, PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 3U, NULL), PRT_TRUE), PRT_TRUE))
    {
      P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_2(PrtTupleGetNC(p_tmp_expr_1, 1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE), PRT_FALSE, P_EXPR_0(&P_GEND_VALUE_0, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotTP], PRT_FALSE), PRT_FALSE);
    }
    if (P_BOOL_EXPR(P_EXPR_3(PrtMkBoolValue(!PrtIsEqualValue(p_tmp_expr_2, p_tmp_expr_1)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, &P_GEND_VALUE_49, PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE), PRT_TRUE))
    {
      if (P_BOOL_EXPR(P_EXPR_2(PrtWrapFunStmt(&p_tmp_frame, 0U, p_tmp_mach_priv, 8U, P_TUPLE_0(&P_GEND_TYPE_13, p_tmp_expr_1)), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE), PRT_TRUE))
      {
        P_STMT_2(P_SEQ(PrtCheckIsLocalMachineId(context, p_tmp_stmt_0), PrtSend(PrtGetMachine(context->process, p_tmp_stmt_0), p_tmp_stmt_1, p_tmp_stmt_2)), P_EXPR_4(P_TUPLE_1(&P_GEND_TYPE_30, p_tmp_expr_3, p_tmp_expr_1), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_2, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 0), PRT_FALSE, PrtTupleGetNC(p_tmp_expr_0, 1), PRT_FALSE, p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_currentRobotState], PRT_FALSE), PRT_TRUE, P_EXPR_0(&P_GEND_VALUE_5, PRT_FALSE), PRT_FALSE, P_EXPR_0(p_tmp_mach_priv->varValues[P_VAR_SenseAndInfer_robotTP], PRT_FALSE), PRT_FALSE);
      }
    }
    P_EXIT_FUN:
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
  }

  PRT_CASEDECL P_GEND_CASES_0[] = 
  {
    
    {
        P_EVENT_CurrentState,
        24U
    }
  };
  PRT_CASEDECL P_GEND_CASES_2[] = 
  {
    
    {
        P_EVENT_CurrentState,
        24U
    }
  };
  PRT_CASEDECL P_GEND_CASES_8[] = 
  {
    
    {
        P_EVENT_CurrentState,
        24U
    }
  };
  PRT_UINT32 P_GEND_EVENTSET_0[] = 
  {
    0x0U
  };
  PRT_UINT32 P_GEND_EVENTSET_1[] = 
  {
    0x1U
  };
  PRT_UINT32 P_GEND_EVENTSET_10[] = 
  {
    0x0U,
    0x4U
  };
  PRT_UINT32 P_GEND_EVENTSET_11[] = 
  {
    0x0U,
    0x080U
  };
  PRT_UINT32 P_GEND_EVENTSET_12[] = 
  {
    0x0U,
    0x100U
  };
  PRT_UINT32 P_GEND_EVENTSET_2[] = 
  {
    0x080U
  };
  PRT_UINT32 P_GEND_EVENTSET_3[] = 
  {
    0x200U
  };
  PRT_UINT32 P_GEND_EVENTSET_4[] = 
  {
    0x400U
  };
  PRT_UINT32 P_GEND_EVENTSET_5[] = 
  {
    0x0800U
  };
  PRT_UINT32 P_GEND_EVENTSET_6[] = 
  {
    0x1000U
  };
  PRT_UINT32 P_GEND_EVENTSET_7[] = 
  {
    0x4000U
  };
  PRT_UINT32 P_GEND_EVENTSET_8[] = 
  {
    0x08000U
  };
  PRT_UINT32 P_GEND_EVENTSET_9[] = 
  {
    0x20000U
  };
  PRT_EVENTSETDECL P_GEND_EVENTSETS[] = 
  {
    
    {
        0,
        1,
        P_GEND_EVENTSET_0
    },
    
    {
        1,
        1,
        P_GEND_EVENTSET_1
    },
    
    {
        2,
        1,
        P_GEND_EVENTSET_2
    },
    
    {
        3,
        1,
        P_GEND_EVENTSET_3
    },
    
    {
        4,
        1,
        P_GEND_EVENTSET_4
    },
    
    {
        5,
        1,
        P_GEND_EVENTSET_5
    },
    
    {
        6,
        1,
        P_GEND_EVENTSET_6
    },
    
    {
        7,
        1,
        P_GEND_EVENTSET_7
    },
    
    {
        8,
        1,
        P_GEND_EVENTSET_8
    },
    
    {
        9,
        1,
        P_GEND_EVENTSET_9
    },
    
    {
        10,
        2,
        P_GEND_EVENTSET_10
    },
    
    {
        11,
        2,
        P_GEND_EVENTSET_11
    },
    
    {
        12,
        2,
        P_GEND_EVENTSET_12
    }
  };
  PRT_EVENTSETDECL P_GEND_EVENTSETS[] = 
  {
    
    {
        0,
        2,
        P_GEND_EVENTSET_0
    },
    
    {
        1,
        1,
        P_GEND_EVENTSET_1
    },
    
    {
        2,
        1,
        P_GEND_EVENTSET_2
    },
    
    {
        3,
        1,
        P_GEND_EVENTSET_3
    },
    
    {
        4,
        1,
        P_GEND_EVENTSET_4
    },
    
    {
        5,
        1,
        P_GEND_EVENTSET_5
    },
    
    {
        6,
        1,
        P_GEND_EVENTSET_6
    },
    
    {
        7,
        1,
        P_GEND_EVENTSET_7
    },
    
    {
        8,
        1,
        P_GEND_EVENTSET_8
    },
    
    {
        9,
        1,
        P_GEND_EVENTSET_9
    },
    
    {
        10,
        2,
        P_GEND_EVENTSET_10
    },
    
    {
        11,
        2,
        P_GEND_EVENTSET_11
    },
    
    {
        12,
        2,
        P_GEND_EVENTSET_12
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_RobotTaskPlanner_UpdateCurrentRobotState[] = 
  {
    
    {
        8U,
        3U,
        1U,
        P_GEND_CASES_8
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_SenseAndInfer_ANON3[] = 
  {
    
    {
        0U,
        3U,
        1U,
        P_GEND_CASES_0
    }
  };
  PRT_RECEIVEDECL P_GEND_RECEIVE_P_FUN_SenseAndInfer_ANON4[] = 
  {
    
    {
        2U,
        3U,
        1U,
        P_GEND_CASES_2
    }
  };
  PRT_STATEDECL P_GEND_STATES_DriverMachine[] = 
  {
    
    {
        P_STATE_DriverMachine_Init,
        P_MACHINE_DriverMachine,
        "Init",
        0,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        P_FUN_DriverMachine_ANON1,
        P_FUN_DriverMachine_ANON0,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_MotionPlanExecutor[] = 
  {
    
    {
        P_STATE_MotionPlanExecutor_Init,
        P_MACHINE_MotionPlanExecutor,
        "Init",
        1,
        0,
        0,
        12,
        0,
        P_GEND_TRANS_MotionPlanExecutor_Init,
        NULL,
        P_FUN_MotionPlanExecutor_ANON4,
        P_FUN_MotionPlanExecutor_ANON2,
        0U,
        NULL
    },
    
    {
        P_STATE_MotionPlanExecutor_StartExecutingPlan,
        P_MACHINE_MotionPlanExecutor,
        "StartExecutingPlan",
        3,
        0,
        0,
        0,
        0,
        P_GEND_TRANS_MotionPlanExecutor_StartExecutingPlan,
        NULL,
        P_FUN_MotionPlanExecutor_ANON1,
        P_FUN_MotionPlanExecutor_ANON2,
        0U,
        NULL
    },
    
    {
        P_STATE_MotionPlanExecutor_WaitForCommands,
        P_MACHINE_MotionPlanExecutor,
        "WaitForCommands",
        1,
        1,
        0,
        6,
        2,
        P_GEND_TRANS_MotionPlanExecutor_WaitForCommands,
        P_GEND_DOS_MotionPlanExecutor_WaitForCommands,
        P_FUN_MotionPlanExecutor_ANON2,
        P_FUN_MotionPlanExecutor_ANON2,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_MotionPlanner[] = 
  {
    
    {
        P_STATE_MotionPlanner_Init,
        P_MACHINE_MotionPlanner,
        "Init",
        1,
        0,
        0,
        12,
        0,
        P_GEND_TRANS_MotionPlanner_Init,
        NULL,
        P_FUN_MotionPlanner_ANON1,
        P_FUN_MotionPlanner_ANON0,
        0U,
        NULL
    },
    
    {
        P_STATE_MotionPlanner_WaitForCommands,
        P_MACHINE_MotionPlanner,
        "WaitForCommands",
        0,
        1,
        0,
        0,
        8,
        NULL,
        P_GEND_DOS_MotionPlanner_WaitForCommands,
        P_FUN_MotionPlanner_ANON0,
        P_FUN_MotionPlanner_ANON0,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_RobotStateManager[] = 
  {
    
    {
        P_STATE_RobotStateManager_GetStateFromEnvMachine,
        P_MACHINE_RobotStateManager,
        "GetStateFromEnvMachine",
        0,
        1,
        0,
        0,
        5,
        NULL,
        P_GEND_DOS_RobotStateManager_GetStateFromEnvMachine,
        P_FUN_RobotStateManager_ANON3,
        P_FUN_RobotStateManager_ANON2,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotStateManager_Init,
        P_MACHINE_RobotStateManager,
        "Init",
        1,
        0,
        0,
        11,
        0,
        P_GEND_TRANS_RobotStateManager_Init,
        NULL,
        P_FUN_RobotStateManager_ANON4,
        P_FUN_RobotStateManager_ANON2,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotStateManager_WaitForCommands,
        P_MACHINE_RobotStateManager,
        "WaitForCommands",
        1,
        1,
        0,
        9,
        10,
        P_GEND_TRANS_RobotStateManager_WaitForCommands,
        P_GEND_DOS_RobotStateManager_WaitForCommands,
        P_FUN_RobotStateManager_ANON2,
        P_FUN_RobotStateManager_ANON2,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_RobotTaskPlanner[] = 
  {
    
    {
        P_STATE_RobotTaskPlanner_ExecutePlan,
        P_MACHINE_RobotTaskPlanner,
        "ExecutePlan",
        0,
        2,
        0,
        0,
        0,
        NULL,
        P_GEND_DOS_RobotTaskPlanner_ExecutePlan,
        P_FUN_RobotTaskPlanner_ANON5,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_Init,
        P_MACHINE_RobotTaskPlanner,
        "Init",
        1,
        0,
        0,
        12,
        0,
        P_GEND_TRANS_RobotTaskPlanner_Init,
        NULL,
        P_FUN_RobotTaskPlanner_ANON3,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_LowBatteryDetected,
        P_MACHINE_RobotTaskPlanner,
        "LowBatteryDetected",
        4,
        1,
        4,
        0,
        7,
        P_GEND_TRANS_RobotTaskPlanner_LowBatteryDetected,
        P_GEND_DOS_RobotTaskPlanner_LowBatteryDetected,
        P_FUN_RobotTaskPlanner_ANON7,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_ScanningModeOfOperation,
        P_MACHINE_RobotTaskPlanner,
        "ScanningModeOfOperation",
        6,
        1,
        0,
        0,
        7,
        P_GEND_TRANS_RobotTaskPlanner_ScanningModeOfOperation,
        P_GEND_DOS_RobotTaskPlanner_ScanningModeOfOperation,
        P_FUN_RobotTaskPlanner_ANON6,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_MACHINE_RobotTaskPlanner,
        "SelectGoalLocationAndComputePlan",
        5,
        4,
        0,
        0,
        0,
        P_GEND_TRANS_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_GEND_DOS_RobotTaskPlanner_SelectGoalLocationAndComputePlan,
        P_FUN_RobotTaskPlanner_ANON9,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_SetUpSystem,
        P_MACHINE_RobotTaskPlanner,
        "SetUpSystem",
        1,
        0,
        0,
        12,
        0,
        P_GEND_TRANS_RobotTaskPlanner_SetUpSystem,
        NULL,
        P_FUN_RobotTaskPlanner_ANON4,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_RobotTaskPlanner_TakeActionOnEnvEventDetected,
        P_MACHINE_RobotTaskPlanner,
        "TakeActionOnEnvEventDetected",
        0,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        P_FUN_RobotTaskPlanner_ANON8,
        P_FUN_RobotTaskPlanner_ANON1,
        0U,
        NULL
    }
  };
  PRT_STATEDECL P_GEND_STATES_SenseAndInfer[] = 
  {
    
    {
        P_STATE_SenseAndInfer_Init,
        P_MACHINE_SenseAndInfer,
        "Init",
        1,
        0,
        0,
        12,
        0,
        P_GEND_TRANS_SenseAndInfer_Init,
        NULL,
        P_FUN_SenseAndInfer_ANON2,
        P_FUN_SenseAndInfer_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_SenseAndInfer_PeriodicallySenseUpdate,
        P_MACHINE_SenseAndInfer,
        "PeriodicallySenseUpdate",
        1,
        1,
        0,
        1,
        9,
        P_GEND_TRANS_SenseAndInfer_PeriodicallySenseUpdate,
        P_GEND_DOS_SenseAndInfer_PeriodicallySenseUpdate,
        P_FUN_SenseAndInfer_ANON1,
        P_FUN_SenseAndInfer_ANON1,
        0U,
        NULL
    },
    
    {
        P_STATE_SenseAndInfer_SenseEnvironment,
        P_MACHINE_SenseAndInfer,
        "SenseEnvironment",
        0,
        0,
        9,
        0,
        0,
        NULL,
        NULL,
        P_FUN_SenseAndInfer_ANON4,
        P_FUN_SenseAndInfer_ANON1,
        0U,
        NULL
    }
  };
  PRT_MACHINEDECL P_GEND_MACHINES[] = 
  {
    
    {
        P_MACHINE_DriverMachine,
        "DriverMachine",
        3,
        1,
        3,
        4294967295,
        P_STATE_DriverMachine_Init,
        P_GEND_VARS_DriverMachine,
        P_GEND_STATES_DriverMachine,
        P_GEND_FUNS_DriverMachine,
        &P_CTOR_DriverMachine_IMPL,
        &P_DTOR_DriverMachine_IMPL,
        0U,
        NULL
    },
    
    {
        P_MACHINE_MotionPlanExecutor,
        "MotionPlanExecutor",
        4,
        3,
        8,
        4294967295,
        P_STATE_MotionPlanExecutor_Init,
        P_GEND_VARS_MotionPlanExecutor,
        P_GEND_STATES_MotionPlanExecutor,
        P_GEND_FUNS_MotionPlanExecutor,
        &P_CTOR_MotionPlanExecutor_IMPL,
        &P_DTOR_MotionPlanExecutor_IMPL,
        0U,
        NULL
    },
    
    {
        P_MACHINE_MotionPlanner,
        "MotionPlanner",
        3,
        2,
        6,
        4294967295,
        P_STATE_MotionPlanner_Init,
        P_GEND_VARS_MotionPlanner,
        P_GEND_STATES_MotionPlanner,
        P_GEND_FUNS_MotionPlanner,
        &P_CTOR_MotionPlanner_IMPL,
        &P_DTOR_MotionPlanner_IMPL,
        0U,
        NULL
    },
    
    {
        P_MACHINE_RobotStateManager,
        "RobotStateManager",
        4,
        3,
        7,
        4294967295,
        P_STATE_RobotStateManager_Init,
        P_GEND_VARS_RobotStateManager,
        P_GEND_STATES_RobotStateManager,
        P_GEND_FUNS_RobotStateManager,
        &P_CTOR_RobotStateManager_IMPL,
        &P_DTOR_RobotStateManager_IMPL,
        0U,
        NULL
    },
    
    {
        P_MACHINE_RobotTaskPlanner,
        "RobotTaskPlanner",
        11,
        7,
        16,
        4294967295,
        P_STATE_RobotTaskPlanner_Init,
        P_GEND_VARS_RobotTaskPlanner,
        P_GEND_STATES_RobotTaskPlanner,
        P_GEND_FUNS_RobotTaskPlanner,
        &P_CTOR_RobotTaskPlanner_IMPL,
        &P_DTOR_RobotTaskPlanner_IMPL,
        0U,
        NULL
    },
    
    {
        P_MACHINE_SenseAndInfer,
        "SenseAndInfer",
        3,
        3,
        7,
        4294967295,
        P_STATE_SenseAndInfer_Init,
        P_GEND_VARS_SenseAndInfer,
        P_GEND_STATES_SenseAndInfer,
        P_GEND_FUNS_SenseAndInfer,
        &P_CTOR_SenseAndInfer_IMPL,
        &P_DTOR_SenseAndInfer_IMPL,
        0U,
        NULL
    }
  };
  PRT_MODELIMPLDECL P_GEND_MODELS[] = 
  {
    
    {
        P_MODEL_Environment,
        "Environment",
        &P_CTOR_Environment_IMPL,
        &P_SEND_Environment_IMPL,
        &P_DTOR_Environment_IMPL,
        0U,
        NULL
    },
    
    {
        P_MODEL_Timer,
        "Timer",
        &P_CTOR_Timer_IMPL,
        &P_SEND_Timer_IMPL,
        &P_DTOR_Timer_IMPL,
        0U,
        NULL
    }
  };
  PRT_PROGRAMDECL P_GEND_PROGRAM = 
  {
    44U,
    13U,
    6U,
    2U,
    P_GEND_EVENTS,
    P_GEND_EVENTSETS,
    P_GEND_MACHINES,
    P_GEND_MODELS,
    0U,
    NULL
  };
  