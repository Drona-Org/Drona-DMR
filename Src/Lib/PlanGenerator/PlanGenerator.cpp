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

#ifdef PLAT_WINDOWS
BOOLEAN GenerateMotionPlanFor(
	_In_ int startLocation,
	_In_ int endLocation,
	_In_ int* sequenceOfObstacles,
	_In_ int obsSize,
	_In_ AvoidPositions* avoidPositions,
	_In_ int avoidSize,
	_Out_ int sequenceOfSteps[100],
	_Out_ int & stepsSize
	)
#else
bool GenerateMotionPlanFor(
	WorkspaceInfo WSInfo,
	int startLocation,
	int endLocation,
	int* sequenceOfObstacles,
	int obsSize,
	AvoidPositions* avoidPositions,
	int avoidSize,
	int sequenceOfSteps[100],
	int & stepsSize
	)
#endif
{
	MotionPrimitive_Vector primitives;
	RobotPosition_Vector obstacles;
	MotionPrimitive_Cost prim_cost;
	string line;
	int count;
	WS_Coord coord;
	WS_Coord pos_start, pos_end, pos_obs;
    int index;
   	int **obsmap;

	ReadMotionPrimitives(primitives);

	GetMotionPrimitiveCost(primitives, prim_cost);

	coord = ExtractCoordFromGridLocation(startLocation, WSInfo.dimension);
	pos_start.x = coord.x;
	pos_start.y = coord.y;

	coord = ExtractCoordFromGridLocation(endLocation, WSInfo.dimension);
	pos_end.x = coord.x;
	pos_end.y = coord.y;

	for (count = 0; count < obsSize; count++)
	{
		coord = ExtractCoordFromGridLocation(sequenceOfObstacles[count], WSInfo.dimension);
		//cout << "x = " << x << " " << "y = " << y << endl;
		pos_obs.x = coord.x;
		pos_obs.y = coord.y;
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
  	
      	stepsSize = path.size();
	for (count = 0; count < stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
		sequenceOfSteps[count] = ConvertCoordToGridLocation(path[count], WSInfo.dimension);;
	}

        obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);

	return true;
}
