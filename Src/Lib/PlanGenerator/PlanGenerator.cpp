#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "PlanGenerator.h"
#include <assert.h>

using namespace std;

bool GenerateMotionPlanFor(
	WorkspaceInfo WSInfo,
	int startLocation,
	int endLocation,
	int* sequenceOfObstacles,
	int obsSize,
	AvoidPositions* avoidPositions,
	int avoidSize,
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
    astar.SetAvoidPositions(WSInfo.dimension, avoidPositions, avoidSize);
	
	astar.PrintAvoidPositions();
	
	clock_t begin = clock();
    RobotPosition_Vector path = astar.FindCollisionFreePath();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("traj calculation takes %f\n", elapsed_secs);

  	
    *stepsSize = path.size();
	for (count = 0; count < *stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
		sequenceOfSteps[count] = ConvertCoordToGridLocation(path[count], WSInfo.dimension);;
	}

    obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);


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
		for (int y = 0; y < avoidSize; y++)
		{
			if(count < avoidPositions[y].size)
			{
				if (avoidPositions[y].PositionsOccupied[count] == sequenceOfObstacles[count])
				{
					cout << "Trajectory crashes with a robot " << y<< " trajectory at time "<< count << "and location " << sequenceOfObstacles[count] << endl;
					exit(0);
				}
			}
			else
			{
				if (avoidPositions[y].PositionsOccupied[avoidPositions[y].size - 1] == sequenceOfObstacles[count])
				{
					cout << "Trajectory crashes with a robot " << y << " stationary at time " << count << "and location " << sequenceOfObstacles[count] << endl;
					exit(0);
				}
			}
		}
	}
	return true;
}
