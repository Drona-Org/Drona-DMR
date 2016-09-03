/*
The grid size is 8 x 16
There are 4 drones.

The priority could be any of the following:
0: Lowest Priority
1: Mid Priority
2: Highest Priority

If a drone receives request for two mails of same priority then the priority is resolved based on mailId.

The properties that must be satisfied by the system are:
1) All mails are eventually delivered.
2) If a drone receives two mail requests with different priority then it delivers mails in priority order.
3) Drone never fails because of low-battery error.
*/

include "HelperFunctions.p"

type MailInfo = (mail_id: int, priority: int);
type MailReq  = (mInfo: MailInfo, dest: int, sender: machine);

//mail req and resp events
event eMailDeliveryReq: MailReq;
event eMailDeliveryResp: MailInfo;

//event for configuring drone
event eConfigDrone: seq[machine];

//event when the current mail req gets updated because of higher priority mail received
event eUpdatedCurrentReq;

main machine TestDriver {
	var workerDrones : seq[machine];
	var mailcount: int;
	var numOfWorkerDrones : int;
	start state Init {
		entry {
			var index : int;
			var temp: machine;
			mailcount = 0;
			numOfWorkerDrones = 4;
			//create all the worker drones
			index = 0;
			while(index < numOfWorkerDrones)
			{
				temp = new DroneTaskPlanner(index);
				workerDrones += (0, temp);
			    index = index + 1;
			}

			//send config to all drones
			BROADCAST(workerDrones, eConfigDrone, workerDrones);
			raise eUnit;
		}

		on eUnit goto StartSendingMails;
	}


	var numOfMails : int;
	state StartSendingMails {
		entry {
			
		}
	}
}

machine DroneTaskPlanner
{
	var myId : int;
	var otherDrones: seq[machine];

	var pendingReq : seq[MailReq]; 
	var currentReq : MailReq;

	start state Init {

		entry (payload: int) {
			myId = payload;
		}

		on eConfigDrone goto WaitForMailRequest with (payload: seq[machine]) {
			var index : int;
			index = 0;
			while(index < sizeof(payload))
			{
				if(payload[index] != this)
					otherDrones +=(0, payload[index]);
			    index = index + 1;
			}
		};
	}

	state WaitForMailRequest {
		on eMailDeliveryReq goto Mode_ServiceMailReq with (payload: MailReq) {
			currentReq = payload;
		};
	}

	fun ComparePriority(m1 : MailInfo, m2 : MailInfo) : bool {
		if(m1.priority > m2.priority)
		{
			return true;
		}
		else if(m1.priority == m2.priority)
		{
			if(m1.mail_id < m2.mail_id)
				return true;
		}
		return false;
	}

	fun AddToPrioritySeq(item: MailReq)
	{
		var index: int;
		index = 0;
		while(index < sizeof(pendingReq) && !ComparePriority(item.mInfo, pendingReq[index].mInfo))
		{
		    index = index + 1;
		}
		pendingReq += (0, item);
	}

	state Mode_ServiceMailReq {
		entry {
			//send Motion Planner goto goal location
		}
		on eMailDeliveryReq do (payload : MailReq){
			if(ComparePriority(currentReq.mInfo, payload.mInfo))
			{
				//current is of higher priority, hence add new req in the seq in priority order
				AddToPrioritySeq(payload);
			}
			else
			{
				//send event to motion plan executor to cancel the plan
				AddToPrioritySeq(currentReq);
				currentReq = payload;
				raise eUpdatedCurrentReq;
			}
		};
		on eUpdatedCurrentReq goto Mode_ServiceMailReq;
		on null goto Mode_ServiceMailReq with {
			//task completed
			_SEND(currentReq.sender, eMailDeliveryResp, currentReq.mInfo);
			//fetch the next pending task and move on
			currentReq = pendingReq[0];
			pendingReq -= (0);
		};
	}
}