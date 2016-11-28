#include "timer.p"

event GPS_NOLOCK : machine; 
event GPS_LOCK : machine; 
event ARMED;
event SUCCESS;

// error messages
event ARM_REFUSED;
event MISSION_REFUSED;
event TAKEOFF_REFUSED;
event LOITER_REFUSED;
event RTL_REFUSED;
event LAND_REFUSED;
event MANUAL_REFUSED;

// events from RemoteControl.
event INIT;
event GPSLOCK_ON;
event GPSLOCK_OFF;
event GPS_HOME; // gps detected we are back home
event GPS_HOME_SET; 
event SET_HOME_POS; // sent from Simulator app
event ARM_ON;
event ARM_OFF;
event MANUAL;
event LAND;
event TAKEOFF;
event RTL;
event LOITER;
event MISSION;

// sensor events 
event SET_ALTITUDE: int;
event ALTITUDE_REACHED; // we have reached a target altitude
event ALTITUDE_LANDED; // we have landed
event WATCH_FOR_ALTITUDE:int;
event ALTITUDE_COMPLETE;

// gps sensor events
event GPS_CHANGED: int;

machine GpsSensor {
  var server: machine;
  var home: any;
  var pos: any;

  start state Init { 
    entry (payload:machine) { 
      server = payload;
      raise SUCCESS;
    }
    on SUCCESS goto WaitLock;
  }
  state WaitLock { 
    entry { 
      send server, GPS_NOLOCK, this;
    }
    on GPSLOCK_ON goto Locked;
    ignore SET_HOME_POS;
  }
  state Locked { 
    entry { 
      send server, GPS_LOCK, this;
    } 
    on GPSLOCK_OFF goto WaitLock;

    on SET_HOME_POS do {
        home = pos;
        send server, GPS_HOME_SET;
    }

    on GPS_CHANGED do (newpos:any)
    {
       pos = newpos;
    }

    on GPS_HOME do {       
        send server, GPS_HOME;
    }
  }
}


machine Altimeter {
  var server: machine;
  var altitude: int;
  var target:int;

  start state Init { 
    entry (payload:machine) { 
      server = payload;
      send server,  ALTITUDE_LANDED; // assume we are on the ground
      raise ALTITUDE_COMPLETE;
    }
    on ALTITUDE_COMPLETE goto Idle;
  }

  state Idle
  {   
    on WATCH_FOR_ALTITUDE push MeasureAltitude;
    ignore SET_ALTITUDE;
  }

  state MeasureAltitude { 
    entry (payload:int) { 
      target = payload;
    } 
    on SET_ALTITUDE do (payload:int) {
        altitude = payload;
        if (altitude == 0)
        {
            send server, ALTITUDE_LANDED;
            pop;
        }
        else if (altitude == target) 
        {
            send server, ALTITUDE_REACHED;
            pop;
        }
    }

  }
}

model RemoteControl {
  
  var server: machine;
  var counter: int;

  start state Init { 
    entry {       
      server = new FlightController(this);

      send server, GPS_LOCK;
      send server, GPS_HOME_SET;
      send server, ARM_ON;

      while (counter < 5)
      {
          if ($) {
            send server, MANUAL;
          }
          else if ($) {
            send server, LAND;
          }
          else if ($) {
            send server, TAKEOFF;
          }
          else if ($) {
            send server, RTL;
          }
          else if ($) {
            send server, LOITER;
          }
          else if ($) {
            send server, MISSION;
          }
          counter = counter + 1;
      }
    } 
  }
}

machine FlightController { 
  var gps: machine;
  var remote: machine;
  var altimeter: machine;
  var gpsLocked: int;
  var homePos: int;  
  var wayPoints: int;
  var altitude: int;
  var timer: machine;
      

  start state Init { 
    entry (payload:machine) {  
      remote = payload;
      gpsLocked = 0; 
      gps = new GpsSensor(this); 
      altimeter = new Altimeter(this);
	  timer = new Timer(this);
	  send timer, START, 1000;
    } 
    on GPS_LOCK do {
        gpsLocked = 1;    
    }
    on GPS_NOLOCK do {
        gpsLocked = 0;    
    }
    on GPS_HOME_SET do {
        homePos = 1;    
    }
    
    on INIT push Standby;
    
    ignore ALTITUDE_LANDED;
    ignore ALTITUDE_REACHED;
    ignore ARM_OFF;
    on ARM_ON  do {
        send remote, ARM_REFUSED;
    }
    on MANUAL do {
        send remote, MANUAL_REFUSED;
    }
    on LAND do {
        send remote, LAND_REFUSED;
    }
    on TAKEOFF do {
        send remote, TAKEOFF_REFUSED;
    }
    on RTL do {
        send remote, RTL_REFUSED;
    }
    on LOITER do {
        send remote, LOITER_REFUSED;
    }
    on MISSION do {
        send remote, MISSION_REFUSED;
    }
  }
    
  state Standby { 
    on GPS_LOCK do {
        gpsLocked = 1;    
    }
    on GPS_NOLOCK do {
        gpsLocked = 0;    
    }
    on GPS_HOME_SET do {
        homePos = 1;    
    }
    
    on ARM_ON do {
        if (gpsLocked == 1 && homePos == 1) {
            raise ARMED;
        }
        else {
            send remote, ARM_REFUSED;
        }
    }

    ignore ARM_OFF;

    on ARMED push Armed;
    
  }
  
  state Armed { 
    ignore ARM_ON; // already armed.

    on ARM_OFF do {
        pop;
    }

    on GPS_NOLOCK do {
      // lost GPS lock, we need to go back to Standby.
      gpsLocked = 0;
      pop;
    }

    on MANUAL push Manual;
    on LAND push AutoLand;
    on TAKEOFF push AutoTakeOff;
    on MISSION push AutoMission; // assume mission can 'takeoff' safely.
  }
  
  state AutoTakeOff { 
    entry {
       send altimeter, WATCH_FOR_ALTITUDE, 1000;
    }
    on GPS_NOLOCK do {
      // lost GPS lock, we need to land.
      gpsLocked = 0;
      raise LAND;
    }
    
    ignore ARM_OFF; // cannot disarm while flying.
    on LAND goto AutoLand;
    on MANUAL goto Manual;
    on ALTITUDE_REACHED goto AutoLoiter; 
    ignore TAKEOFF; // already doing it
    on MISSION goto AutoMission; // we are not done taking off but the mission can take over.
    ignore ALTITUDE_LANDED; // should not happen unless we crashed somehow...
  }
  
  state AutoLand {
    entry {
       send altimeter, WATCH_FOR_ALTITUDE, 0;
    }
    on ALTITUDE_LANDED do {
      pop;    
    }
    ignore ARM_OFF; // cannot disarm while flying.
    ignore GPS_NOLOCK; // GPS went away, no problem, we'll land using altitude sensor...
    on MANUAL goto Manual; // user wants to take over landing manually.
    ignore LAND; // already landing!
    ignore ALTITUDE_REACHED; // might happen if altitude wavers a bit (an updraft perhaps?)
  }

  // This means "return to landing" which is a safety feature that brings the drone back home.
  state AutoRtl { 
    
    on GPS_NOLOCK do {
      // lost GPS lock, we need to land.
      gpsLocked = 0;
      raise LAND;
    }
    
    ignore ARM_OFF; // cannot disarm while flying.
    on LAND goto AutoLand;
    on MANUAL goto Manual; 
    on LAND goto AutoLand; // stop coming home, just land where we are.
    ignore RTL; // already doing it!
    on LOITER goto AutoLoiter; // stop and loiter
    on MISSION goto AutoMission; // mission can take over.
    on GPS_HOME goto AutoLand;
    ignore ALTITUDE_LANDED;
    ignore ALTITUDE_REACHED;
  }
  
  state AutoLoiter { 
    
    on GPS_NOLOCK do {
      // lost GPS lock, we need to land.
      gpsLocked = 0;
      raise LAND;
    }

    ignore INIT;
    ignore ARM_OFF; // cannot disarm while flying.
    on MANUAL goto Manual;
    on LAND goto AutoLand;
    ignore TAKEOFF;
    on RTL goto AutoRtl;
    ignore LOITER;
    on MISSION goto AutoMission;
    ignore ALTITUDE_LANDED;
    ignore ALTITUDE_REACHED;
  }
  
  state AutoMission {
    on GPS_NOLOCK do {
      // lost GPS lock, we need to land.
      gpsLocked = 0;
      raise LAND;
    }
    ignore INIT;
    ignore ARM_OFF; // cannot disarm while flying.
    on MANUAL goto Manual;
    on LAND goto AutoLand;
    ignore TAKEOFF;
    on RTL goto AutoRtl;
    on LOITER goto AutoLoiter;
    ignore MISSION;
    ignore ALTITUDE_LANDED;
    ignore ALTITUDE_REACHED;
  }

  state Manual
  {
    ignore GPS_NOLOCK;
    ignore INIT;
    on MANUAL goto Manual;
    on LAND goto AutoLand;
    on TAKEOFF goto AutoTakeOff;
    on RTL goto AutoRtl;
    on LOITER goto AutoLoiter;
    on MISSION goto AutoMission;
    ignore ALTITUDE_LANDED;
    ignore ALTITUDE_REACHED;

    // todo: need to remember if we are flying or not...
  }

} 
