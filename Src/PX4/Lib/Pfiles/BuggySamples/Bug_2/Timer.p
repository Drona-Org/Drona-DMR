// events from client of timer
event timer_start : int; //milliseconds
event timer_cancel;
// events from timer to client
event timer_timeout: machine;
event timer_cancel_success: machine;
event timer_cancel_failure: machine;
// local event for control transfer within timer
event timer_init;

model TimerMachine {
  var clientV: machine;

  start state Init {
    entry (payload : machine) {
      clientV = payload;
      // goto WaitForReq
      raise timer_init;
    }
    on timer_init goto WaitForReq;
  }

  state WaitForReq {
    on timer_cancel goto WaitForReq with { 
      send clientV, timer_cancel_failure, this;
    } 
    on timer_start goto WaitForCancel;
  }

  state WaitForCancel {
    ignore timer_start;
    on null goto WaitForReq with { 
		send clientV, timer_timeout, this; 
    }
    on timer_cancel goto WaitForReq with {
      if ($) {
        send clientV, timer_cancel_success, this;
      } else {
        send clientV, timer_cancel_failure, this;
        send clientV, timer_timeout, this;
      }
    }
  }
}
