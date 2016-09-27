#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "PlanGenerator.h"
#include <assert.h>

using namespace std;

//pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

bool GenerateMotionPlanFor(
	int robotid,
	WorkspaceInfo WSInfo,
	int startLocation,
	int endLocation,
	int* sequenceOfObstacles,
	int obsSize,
	vector< vector<WS_Coord> > avoidPositions,
	int sequenceOfSteps[1000],
	int* stepsSize
	)
{
	RobotPosition_Vector obstacles;
	string line;
	int count;
	WS_Coord coord;
	WS_Coord pos_start, pos_end, pos_obs;
    int index;
   	int ***obsmap;

	coord = ExtractCoordFromGridLocation(startLocation, WSInfo.dimension);
	SetCoordTo(&pos_start, coord);

	coord = ExtractCoordFromGridLocation(endLocation, WSInfo.dimension);
	SetCoordTo(&pos_end, coord);

	for (count = 0; count < obsSize; count++)
	{
		coord = ExtractCoordFromGridLocation(sequenceOfObstacles[count], WSInfo.dimension);
		//cout << "x = " << x << " " << "y = " << y << endl;
		SetCoordTo(&pos_obs, coord);
		obstacles.push_back(pos_obs);
	}

    CAstar astar;
  	astar.SetDimension(WSInfo.dimension);
  	astar.SetObstacleMap(WSInfo.dimension, obstacles);
 	astar.SetSEpoint(pos_start, pos_end);
    astar.SetAvoidPositions(WSInfo.dimension, avoidPositions);
		
	clock_t begin = clock();
    RobotPosition_Vector path = astar.FindCollisionFreePath();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//pthread_mutex_lock(&print_lock);
	printf("====================================================\n");
	printf("Robot %d\n", robotid);
	PrintObstaclesList(*WORKSPACE_INFO);
	
	astar.PrintAvoidPositions();
	printf("traj calculation takes %f\n", elapsed_secs);
	assert(elapsed_secs < 2.0);

  	
    *stepsSize = path.size();
	for (count = 0; count < *stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
		sequenceOfSteps[count] = ConvertCoordToGridLocation(path[count], WSInfo.dimension);;
	}

    obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);


	printf("Trajectory:");
	for (int i = 0; i < *stepsSize; i++)
	{
		printf("%d ", sequenceOfSteps[i]);
	}
	printf("\n\n");
	printf("====================================================\n");
	//pthread_mutex_unlock(&print_lock);

	//assert that the traj generated is correct
	for (count = 0; count < *stepsSize; count++)
	{
		for (int x = 0; x < WSInfo.obstacles.size; x++)
		{
			if (WSInfo.obstacles.locations[x] == sequenceOfSteps[count])
			{
				cout << "Trajectory crashes with a static obstacle" << endl;
				exit(0);
			}
		}
		for (int y = 0; y < avoidPositions.size(); y++)
		{
			if(count < avoidPositions[y].size())
			{
				if (ConvertCoordToGridLocation(avoidPositions[y][count], WSInfo.dimension) == sequenceOfSteps[count])
				{
					cout << "Trajectory crashes with a robot " << y<< " trajectory at time "<< count << "and location " << sequenceOfSteps[count] << endl;
					exit(0);
				}
			}
			else
			{
				if (ConvertCoordToGridLocation(avoidPositions[y][avoidPositions[y].size() - 1], WSInfo.dimension) == sequenceOfSteps[count])
				{
					cout << "Trajectory crashes with a robot " << y << " stationary at time " << count << "and location " << sequenceOfSteps[count] << endl;
					exit(0);
				}
			}
		}
	}
	return true;
}
