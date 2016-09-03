/**********************************************
Helper functions 
***********************************************/


//function to print the value in error trace.
static model fun PRINT(a:any) [printvalue=a]{}

//function to send event to other machines
static model fun _SEND(target:machine, e:event, p:any) {
	//we are not considering message loss right now
	//if ($)
		send target, e, p;
}

//function to broadcast event
static fun BROADCAST(targetSeq: seq[machine], e:event, p:any)
{
	var index: int;
	index = 0;
	while(index < sizeof(targetSeq))
	{
		_SEND(targetSeq[index], e, p);
	    index = index + 1;
	}
}



