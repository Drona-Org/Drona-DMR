static fun CAT_CAGE_LOC() : int
{
	return 4;
}

static fun DOG_CAGE_LOC() : int
{
	return 13;
}

static fun MICE_CAGE_LOC() : int
{
	return 16;
}

static fun BATTERY_THRESHOLD() : int
{
	return 5;
}

static fun DOG(): int{
	return 0;
}

static fun CAT(): int{
	return 1;
}

static fun MICE(): int{
	return 2;
}

static fun BATTERY_CHARGE_LOCATION() : int {
	return 15;
}

static fun ROBOT_START_STATE() : (loc:int, battery:int)
{
	return (loc  = 1, battery = 20);
}

static fun SIZE_OF_GRID() : int
{
	return 16;
}

static fun ROBOT_SCAN_LOCATIONS() : seq[int]
{
	var iter:int;
	var scanLocations: seq[int];
	var obstacles : seq[int];
	iter = 0;
	obstacles = GetStaticObstacles();
	while(iter < SIZE_OF_GRID())
	{
		if(sizeof(obstacles) > 0 && iter == obstacles[0])
		{
			obstacles -=(0);
		}
		else
		{
			scanLocations += (sizeof(scanLocations), iter);
		}
		iter = iter + 1;
	}
	return scanLocations;
}

static fun GetStaticGoals() : map[int, any]
{
	//in this case there are three different types of goal
	//(isDogPresent:bool, isCatPresent:bool, isMicePresent:bool)
	var staticGoalLoc : map[int, (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool)];
	staticGoalLoc[2] =  (isDogPresent = false, isCatPresent = false, isMicePresent = true);
	staticGoalLoc[5] =  (isDogPresent = true, isCatPresent = false, isMicePresent = false);
	staticGoalLoc[10] = (isDogPresent = false, isCatPresent = true, isMicePresent = false);
	staticGoalLoc[11] = (isDogPresent = true, isCatPresent = false, isMicePresent = false);
	
	return staticGoalLoc;
}

static fun GetStaticObstacles() : seq[int] {
	var obstacles :seq[int];
	obstacles += (sizeof(obstacles), 6);
	obstacles += (sizeof(obstacles), 7);
	obstacles += (sizeof(obstacles), 9);
	return obstacles;
}

static fun EventDetected(envState : any): bool
{
	if((envState as (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool)).isCatPresent || (envState as (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool)).isDogPresent || (envState as (isDogPresent:bool, isCatPresent:bool, isMicePresent:bool)).isMicePresent)
	{
		return true;
	}
	else
	{
		return false;
	}
}