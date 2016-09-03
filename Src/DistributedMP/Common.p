	static fun ChooseInt(s : int) : int {
		while(s > 0)
		{
			if($)
				return s;
			else
				s = s - 1;
		}
		return s;
	}

	static fun BROADCAST(allTarget: seq[machine], ev: event, payload: any)
	{
		var index: int;
		index = 0;
		while(index < sizeof(allTarget))
		{
			send allTarget[index], ev, payload;
		    index = index + 1;
		}
	}

	static fun COMPLAN(allAvoidsV : map[int, TimedTrajType], task:TaskType, startTime: int) : TimedTrajType {

	}