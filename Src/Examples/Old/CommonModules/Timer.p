
// local event for control transfer within timer
event UNIT; 
model Timer {
  var client: machine;
  start state Init {
    entry {
      client = payload as machine;
      raise UNIT;  // goto handler of UNIT
    }
    on UNIT goto WaitForReq;
  }

  state WaitForReq {
    on CANCEL goto WaitForReq with { 
      send client, CANCEL_FAILURE, this;
    };  
    on START goto WaitForCancel;
  }

  state WaitForCancel {
    ignore START;
    on null goto WaitForReq with { 
	  send client, TIMEOUT, this; 
	};
    on CANCEL goto WaitForReq with {
      if ($) {
        send client, CANCEL_SUCCESS, this;
      } else {
        send client, CANCEL_FAILURE, this;
        send client, TIMEOUT, this;
      }
    };
  }
}
