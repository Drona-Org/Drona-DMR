
static model fun InitializeMotionPlanning() : map[(int, int), seq[int]] {
	
	var AllMotionPlans : map[(int, int), seq[int]];
	var scanLocations: seq[int];
	var tempSeq: seq[int];
	var iter: int;
	iter = 1;
	
	scanLocations = ROBOT_SCAN_LOCATIONS();
	while(iter <= SIZE_OF_GRID())
	{
		if(iter == 1)
		{
			tempSeq = default(seq[int]);
			tempSeq += (sizeof(tempSeq), iter);
			tempSeq += (sizeof(tempSeq), iter + 1);
			AllMotionPlans[(iter, iter + 1)] = tempSeq;
		}
		else if(iter == SIZE_OF_GRID())
		{
			tempSeq = default(seq[int]);
			tempSeq += (sizeof(tempSeq), iter);
			tempSeq += (sizeof(tempSeq), iter-1);
			AllMotionPlans[(iter, iter-1)] = tempSeq;
		}
		else
		{
			tempSeq = default(seq[int]);
			tempSeq += (sizeof(tempSeq), iter);
			tempSeq += (sizeof(tempSeq), iter-1);
			AllMotionPlans[(iter, iter-1)] = tempSeq;
			tempSeq = default(seq[int]);
			tempSeq += (sizeof(tempSeq), iter);
			tempSeq += (sizeof(tempSeq), iter + 1);
			AllMotionPlans[(iter, iter + 1)] = tempSeq;
		}
		iter = iter + 1;
	}
	
	return AllMotionPlans;

}
