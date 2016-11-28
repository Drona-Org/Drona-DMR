
  #ifndef P_PROGRAM_H
    #define P_PROGRAM_H
    #include "PrtUser.h"
    #include "PrtExecution.h"
    #ifdef __cplusplus
      extern "C"{
    #endif
    enum P_EVENTS
    {
      _P_EVENT_NULL = 0,
      _P_EVENT_HALT = 1,
      P_EVENT_PING = 2,
      P_EVENT_PONG = 3,
      P_EVENT_SUCCESS = 4,
      _P_EVENTS_COUNT = 5
    };

    enum P_FORGN_TYPES
    {
      _P_FORGN_TYPES_COUNT = 0
    };

    enum P_FUNS_Client
    {
      P_FUN_Client_ANON0 = 1,
      P_FUN_Client_ANON1 = 2,
      P_FUN_Client_ANON2 = 3,
      P_FUN_Client_ANON3 = 4,
      _P_FUNS_Client_COUNT = 5
    };

    enum P_FUNS_STATIC
    {
      _P_FUN_PUSH_OR_IGN = 0
    };

    enum P_MACHINES
    {
      P_MACHINE_Client = 0,
      _P_MACHINE_MAIN = 0,
      _P_MACHINES_COUNT = 1
    };

    enum P_MODELS
    {
      _P_MODELS_COUNT = 0
    };

    enum P_STATES_Client
    {
      P_STATE_Client_Init = 0,
      P_STATE_Client_SendPing = 1,
      P_STATE_Client_SendPong = 2,
      P_STATE_Client_WaitPing = 3,
      P_STATE_Client_WaitPong = 4,
      _P_STATES_Client_COUNT = 5
    };

    enum P_VARS_Client
    {
      _P_VARS_Client_COUNT = 0
    };

    void P_DTOR_Client_IMPL(PRT_MACHINEINST *context);

    void P_CTOR_Client_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value);

    extern PRT_PROGRAMDECL P_GEND_PROGRAM;
    #ifdef __cplusplus
      }
    #endif
  #endif
  