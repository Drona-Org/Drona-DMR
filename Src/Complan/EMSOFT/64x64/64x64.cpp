#include <iostream>
#include <time.h>
#include<chrono>

#ifdef PLAT_WINDOWS
#include "..\..\Complan\Complan.h"
#else
#include "../../Complan/Complan.h"
#endif

using namespace std;
using namespace std::chrono;

int obs[76] = {
	23,	42,
	24,	41,
	25,	40,
	26,	39,
	27,	38,
	28,	37,
	78,	83,	110,
	77,	84,	109,
	147,	174,	179,
	148,	173,	180,
	88,	105,	120	,137,	152,	169,
	89,	104,	121,	136,	153,	168,
	93,	100,	125,	132,	157,	164,
	94,	99,	126,	131,	158	,163,
	214,	235,
	215,	234,
	216,	233,
	217,	232,
	218,	231,
	219,	230,
	210,	239,
	211,	238

};

AvoidPositions *avoidsArr = NULL;
int sizeof_avoids = 0;
int numRobots = 1;



bool notAnObstacleAndAvoids(int p)
{
	for (int i = 0; i < 76; i++)
	{
		if (p == obs[i])
			return false;
	}
	for (int i = 0; i < sizeof_avoids; i++)
	{

		for (int j = 0; j < avoidsArr[i].size; j++)
		{
			if (avoidsArr[i].PositionsOccupied[j] == p)
				return false;
		}
	}
	return true;
}
int computeStartPoint()
{
	int startpoint = rand() % (64 * 64);
	while (!notAnObstacleAndAvoids(startpoint))
	{
		startpoint = rand() % (64 * 64);
	}
	return startpoint;
}

int computeGoalPoint(int s)
{
	int GoalPoint = rand() % (64 * 64);
	while (!notAnObstacleAndAvoids(GoalPoint))
	{
		GoalPoint = rand() % (64 * 64);
	}
	return GoalPoint;
}

void CreateRandomAvoidsSet()
{
	cout << "Generating avoids" << endl;
	int counter = 0;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int outsize;
	avoidsArr = (AvoidPositions*)malloc((numRobots - 1)*sizeof(AvoidPositions));
	sizeof_avoids = 0;
	while (counter < (numRobots - 1))
	{
		int st = computeStartPoint();
		int g = computeGoalPoint(st);
		cout << st << endl;
		cout << g << endl;
		output_seq_of_locations = (int*)malloc(100 * sizeof(int));
		GenerateMotionPlanFor(st, g, obs, 64, avoidsArr, sizeof_avoids, output_seq_of_locations, &outsize);
		cout << "Trajectory Length = " << outsize << endl;
		cout << "Trajectory: " << endl;
		for (int count = 0; count < outsize; count++)
		{
			cout << output_seq_of_locations[count] << " ";
		}
		cout << endl;
		avoidsArr[counter].size = outsize;
		avoidsArr[counter].PositionsOccupied = output_seq_of_locations;
		sizeof_avoids++;
		counter++;
	}
	cout << "------------" << endl;
}

int main()
{
	int count;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int output_size = 0;
	srand(time(NULL));

	int exp = 3;
	int nr = 0;
	int ROBOTS[4] = { 1, 2, 4, 8 };
	while (nr < 4)
	{
		numRobots = ROBOTS[nr];
		cout << "--------------------------------" << endl;
		cout << "Num Robots: " << numRobots << endl;
		CreateRandomAvoidsSet();
		exp = 3;
		while (exp > 0)
		{
			int st = computeStartPoint();
			int g = computeGoalPoint(st);
			cout << st << endl;
			cout << g << endl;
			output_seq_of_locations = (int*)malloc(100 * sizeof(int));
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			GenerateMotionPlanFor(st, g, obs, 64, avoidsArr, sizeof_avoids, output_seq_of_locations, &output_size);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(t2 - t1).count();
			cout << "--------------------------------" << endl;
			cout << "TIME: " << duration << endl;
			cout << "--------------------------------" << endl;
			cout << "Trajectory Length = " << output_size << endl;
			cout << "Trajectory: " << endl;
			for (count = 0; count < output_size; count++)
			{
				cout << output_seq_of_locations[count] << " ";
			}
			cout << endl;
			free(output_seq_of_locations);
			exp--;
		}
		nr++;
		cout << "--------------------------------" << endl;
	}
	return 0;
}


