
  #ifndef P_PROGRAM_H
    #define P_PROGRAM_H
    #include "linker.h"
    #ifdef __cplusplus
      extern "C"{
    #endif
    enum P_FUNS_GLOBAL
    {
      _P_FUN_PUSH_OR_IGN = 0
    };

    enum P_FUNS_Main
    {
      P_FUN_Main_ANON0 = 1,
      P_FUN_Main_ANON1 = 2,
      P_FUN_Main_ANON2 = 3,
      P_FUN_Main_ANON3 = 4,
      P_FUN_Main_ANON4 = 5,
      P_FUN_Main_ANON5 = 6,
      _P_FUNS_Main_COUNT = 7
    };

    enum P_STATES_Main
    {
      P_STATE_Main_Flying = 0,
      P_STATE_Main_Init = 1,
      P_STATE_Main_Standby = 2,
      _P_STATES_Main_COUNT = 3
    };

    enum P_VARS_Main
    {
      _P_VARS_Main_COUNT = 0
    };

    void P_DTOR_Main_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_Main_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    #ifdef __cplusplus
      }
    #endif
  #endif
  