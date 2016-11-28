//Functions for interacting with the timer machine
fun CreateTimer(owner : machine): machine {
	return new Timer(owner);
}

model fun StartTimer(timer : machine, time: int) {
	send timer, START;
}

model fun CancelTimer(timer : machine) {
	send timer, CANCEL;
}

fun CancelTimerAndHandleResponse(timer: machine): bool {
	var timerCanceled: bool;
	CancelTimer(timer);
	receive {
		case timer_cancel_success: (payload: machine) 
		{ 
			assert(timer == payload);
			timerCanceled = true; 
		}
		case timer_cancel_failure: (payload: machine) 
		{ 
			assert(timer == payload);
			timerCanceled = false; 
		}
	}
	return timerCanceled;
}

// events from client to timer
event timer_start: int;
event timer_cancel;
// events from timer to client
event timer_timeout: machine;
event timer_cancel_success: machine;
event timer_cancel_failure: machine;
// local event for control transfer within timer
event timer_init; 

machine Timer {
  var client: machine;

  start state Init {
    entry (payload: machine) {
      client = payload;
	  // goto WaitForReq
      raise timer_init;
    }
    on timer_init goto WaitForReq;
  }

  state WaitForReq {
    on timer_cancel goto WaitForReq with { 
      send client, timer_cancel_failure, this;
    } 
    on timer_start goto WaitForCancel;
  }

  state WaitForCancel {
    ignore timer_start;
    on null goto WaitForReq with { 
	  send client, timer_timeout, this; 
	}
    on timer_cancel goto WaitForReq with {
      if ($) {
        send client, timer_cancel_success, this;
      } else {
        send client, timer_cancel_failure, this;
        send client, timer_timeout, this;
      }
    }
  }
}
