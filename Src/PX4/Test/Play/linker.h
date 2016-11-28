
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
      P_EVENT_battery_critical = 2,
      P_EVENT_fmom_battery_critical = 3,
      P_EVENT_init = 4,
      P_EVENT_take_off = 5,
      _P_EVENTS_COUNT = 6
    };

    enum P_EVENTSET
    {
      P_GEND_EVENTSET_ = 0,
      P_GEND_EVENTSET_battery_criticalfmom_battery_critical = 1,
      P_GEND_EVENTSET_fmom_battery_critical = 2,
      P_GEND_EVENTSET_init = 3,
      P_GEND_EVENTSET_take_off = 4,
      _P_EVENTSETS_COUNT = 5
    };

    enum P_FORGN_TYPES
    {
      _P_FORGN_TYPES_COUNT = 0
    };

    enum P_MACHINES
    {
      P_MACHINE_Main = 0,
      _P_MACHINES_COUNT = 1
    };

    extern PRT_MACHINEDECL P_MACHINE_STRUCT_Main;
    extern PRT_PROGRAMDECL P_GEND_PROGRAM;
    #ifdef __cplusplus
      }
    #endif
  #endif
  