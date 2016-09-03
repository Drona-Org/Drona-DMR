
static fun BATTERY_THRESHOLD() : int
{
	return 8;
}


static fun BATTERY_CHARGE_LOCATION() : int {
	return 21;
}

static fun WAIT_LOCATION() : int {
	return 8;
}
static fun ROBOT_START_STATE() : (loc:int, battery:int)
{
	if($)
		return (loc  = 4, battery = 20);
	else
		return (loc = 16, battery = 20);
}

static fun SIZE_OF_GRID() : int
{
	return 24;
}

static fun ROBOT_SCAN_LOCATIONS(scanLocations: seq[int], obstacles:seq[int], iter: int) : seq[int]
{
	iter = 0;
	scanLocations = default(seq[int]);
	obstacles = GetStaticObstacles(obstacles);
	while(iter <= SIZE_OF_GRID())
	{
		if(iter == obstacles[0])
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

static fun GetStaticGoals(staticGoalLoc:map[int, any]) : map[int, any]
{
	//operation : 0-> take picture
	staticGoalLoc = default(map[int, int]);
	return staticGoalLoc;
}

static fun GetStaticObstacles(obstacles : seq[int]) : seq[int] {
	obstacles = default(seq[int]);
	obstacles += (sizeof(obstacles), 5);
	obstacles += (sizeof(obstacles), 6);
	obstacles += (sizeof(obstacles), 10);
	obstacles += (sizeof(obstacles), 11);
	obstacles += (sizeof(obstacles), 17);
	obstacles += (sizeof(obstacles), 18);
	obstacles += (sizeof(obstacles), 19);
	return obstacles;
}

static fun EventDetected(envState : any): bool
{

	return false;

}