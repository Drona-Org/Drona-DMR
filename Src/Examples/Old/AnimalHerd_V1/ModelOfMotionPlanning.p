
static model fun InitializeMotionPlanning(tempSeq: seq[int], AllMotionPlans : map[(int, int), seq[int]]) : map[(int, int), seq[int]] {



 tempSeq = default(seq[int]);
tempSeq += (sizeof(tempSeq), 2);
tempSeq += (sizeof(tempSeq), 1);
tempSeq += (sizeof(tempSeq), 8);
tempSeq += (sizeof(tempSeq), 9);
tempSeq += (sizeof(tempSeq), 16);
AllMotionPlans[(2, 16)] = tempSeq;


 tempSeq = default(seq[int]);
tempSeq += (sizeof(tempSeq), 5);
tempSeq += (sizeof(tempSeq), 12);
tempSeq += (sizeof(tempSeq), 13);
AllMotionPlans[(5, 13)] = tempSeq;


 tempSeq = default(seq[int]);
tempSeq += (sizeof(tempSeq), 5);
tempSeq += (sizeof(tempSeq), 12);
tempSeq += (sizeof(tempSeq), 13);
AllMotionPlans[(5, 13)] = tempSeq;


 tempSeq = default(seq[int]);
tempSeq += (sizeof(tempSeq), 10);
tempSeq += (sizeof(tempSeq), 7);
tempSeq += (sizeof(tempSeq), 6);
tempSeq += (sizeof(tempSeq), 3);
tempSeq += (sizeof(tempSeq), 4);
AllMotionPlans[(10, 4)] = tempSeq;

return AllMotionPlans;















}
	
	

























