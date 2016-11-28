
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
      P_EVENT_ATTACH_DRIVER = 2,
      P_EVENT_CANCEL = 3,
      P_EVENT_CANCEL_FAILURE = 4,
      P_EVENT_CANCEL_SUCCESS = 5,
      P_EVENT_READY = 6,
      P_EVENT_SELFTEST_FAILED = 7,
      P_EVENT_START = 8,
      P_EVENT_TIMEOUT = 9,
      P_EVENT_UNIT = 10,
      _P_EVENTS_COUNT = 11
    };

    enum P_EVENTSET
    {
      P_GEND_EVENTSET_ = 0,
      P_GEND_EVENTSET_ATTACH_DRIVER = 1,
      P_GEND_EVENTSET_CANCELSTART = 2,
      P_GEND_EVENTSET_CANCELnull = 3,
      P_GEND_EVENTSET_READY = 4,
      P_GEND_EVENTSET_SELFTEST_FAILED = 5,
      P_GEND_EVENTSET_START = 6,
      P_GEND_EVENTSET_UNIT = 7,
      _P_EVENTSETS_COUNT = 8
    };

    enum P_FIELD_INDEX_MpuReport
    {
      P_FIELD_INDEX_MpuReport_status = 0,
      P_FIELD_INDEX_MpuReport_ax = 1,
      P_FIELD_INDEX_MpuReport_ay = 2,
      P_FIELD_INDEX_MpuReport_az = 3,
      P_FIELD_INDEX_MpuReport_temp = 4,
      P_FIELD_INDEX_MpuReport_gx = 5,
      P_FIELD_INDEX_MpuReport_gy = 6,
      P_FIELD_INDEX_MpuReport_gz = 7,
      _P_FIELD_INDEX_MpuReport_COUNT = 8
    };

    enum P_FIELD_INDEX_Point
    {
      P_FIELD_INDEX_Point_x = 0,
      P_FIELD_INDEX_Point_y = 1,
      P_FIELD_INDEX_Point_z = 2,
      _P_FIELD_INDEX_Point_COUNT = 3
    };

    enum P_FORGN_TYPES
    {
      _P_FORGN_TYPES_COUNT = 0
    };

    enum P_MACHINES
    {
      P_MACHINE_MPU6000Client = 0,
      P_MACHINE_MPU6000Driver = 1,
      P_MACHINE_MPU6000Sensor = 2,
      P_MACHINE_TestDriver = 3,
      P_MACHINE_Timer = 4,
      _P_MACHINES_COUNT = 5
    };

    extern PRT_MACHINEDECL P_MACHINE_STRUCT_MPU6000Client;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_MPU6000Driver;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_MPU6000Sensor;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_TestDriver;
    extern PRT_MACHINEDECL P_MACHINE_STRUCT_Timer;
    extern PRT_PROGRAMDECL P_GEND_PROGRAM;
    extern PRT_TYPE *P_GEND_TYPE_MpuReport;
    extern PRT_TYPE *P_GEND_TYPE_Point;
    #ifdef __cplusplus
      }
    #endif
  #endif
  