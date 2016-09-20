#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "PlanGenerator.h"

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
	MotionPrimitive_Vector primitives;
	RobotPosition_Vector obstacles;
	MotionPrimitive_Cost prim_cost;
	string line;
	int count;
	WS_Coord coord;
	WS_Coord pos_start, pos_end, pos_obs;
    int index;
   	int ***obsmap;

	ReadMotionPrimitives(primitives);

	GetMotionPrimitiveCost(primitives, prim_cost);

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
  	astar.SetPrimitive(primitives);
  	astar.SetDimension(WSInfo.dimension);
  	astar.SetObstacleMap(WSInfo.dimension, obstacles);
 	astar.SetSEpoint(pos_start, pos_end);
    astar.SetAvoidPositions(WSInfo.dimension, avoidPositions, avoidSize);

    astar.PrintAvoidPositions();

  	RobotPosition_Vector path = astar.FindCollisionFreePath();
  	
    *stepsSize = path.size();
	for (count = 0; count < *stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
		sequenceOfSteps[count] = ConvertCoordToGridLocation(path[count], WSInfo.dimension);;
	}

    obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);

	return true;
}
