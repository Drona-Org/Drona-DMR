/* Functions for parsing the workspace info */
type RobotInfoType = (
	robotid: int,
	startpos: int
	);
model fun GetNumOfRobots(): int { return 2; }
model fun GetRobotInfo(robotid: int): RobotInfoType { 
	return (robotid = robotid, startpos = robotid);
}

model fun GetGoalLocations(): seq[int] { 
	var ret: seq[int];
	ret += (0, 1);
	ret += (0, 57);
	return ret;
}


