#pragma once

namespace FlightController
{
    public enum class SimulationEvent
    {
        _P_EVENT_NULL = 0,
        _P_EVENT_HALT = 1,
        P_EVENT_ALTITUDE_COMPLETE = 2,
        P_EVENT_ALTITUDE_LANDED = 3,
        P_EVENT_ALTITUDE_REACHED = 4,
        P_EVENT_ARMED = 5,
        P_EVENT_ARM_OFF = 6,
        P_EVENT_ARM_ON = 7,
        P_EVENT_ARM_REFUSED = 8,
        P_EVENT_CANCEL = 9,
        P_EVENT_CANCEL_FAILURE = 10,
        P_EVENT_CANCEL_SUCCESS = 11,
        P_EVENT_GPSLOCK_OFF = 12,
        P_EVENT_GPSLOCK_ON = 13,
        P_EVENT_GPS_CHANGED = 14,
        P_EVENT_GPS_HOME = 15,
        P_EVENT_GPS_HOME_SET = 16,
        P_EVENT_GPS_LOCK = 17,
        P_EVENT_GPS_NOLOCK = 18,
        P_EVENT_INIT = 19,
        P_EVENT_LAND = 20,
        P_EVENT_LAND_REFUSED = 21,
        P_EVENT_LOITER = 22,
        P_EVENT_LOITER_REFUSED = 23,
        P_EVENT_MANUAL = 24,
        P_EVENT_MANUAL_REFUSED = 25,
        P_EVENT_MISSION = 26,
        P_EVENT_MISSION_REFUSED = 27,
        P_EVENT_RTL = 28,
        P_EVENT_RTL_REFUSED = 29,
        P_EVENT_SET_ALTITUDE = 30,
        P_EVENT_SET_HOME_POS = 31,
        P_EVENT_START = 32,
        P_EVENT_SUCCESS = 33,
        P_EVENT_TAKEOFF = 34,
        P_EVENT_TAKEOFF_REFUSED = 35,
        P_EVENT_TIMEOUT = 36,
        P_EVENT_UNIT = 37,
        P_EVENT_WATCH_FOR_ALTITUDE = 38,
        _P_EVENTS_COUNT = 39
    };

    public enum class SimulationMachine
    {
        P_MACHINE_Altimeter = 0,
        P_MACHINE_FlightController = 1,
        P_MACHINE_GpsSensor = 2,
        _P_MACHINES_COUNT = 3
    };

    public ref class Simulation sealed
    {
        ~Simulation();
    public:
        Simulation();
        void Start();
        void Stop();
        void RaiseEvent(SimulationMachine machineId, SimulationEvent eventId, Platform::Object^ payload);
        event Windows::Foundation::EventHandler<Platform::String^>^ LogEvent;
    internal:
        void HandleLogEvent(Platform::String^ message);
    };
}
