#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Semplan.h"

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
	Dimension dimension;
	RobotPosition_Vector obstacles;
	Workspace workspace;
	MotionPrimitive_Cost prim_cost;
	string line;
	int count;
	int x, y;
	RobotPosition pos_start, pos_end, pos_obs;
        int index;
   	int **obsmap;

	ReadMotionPrimitives(primitives);
	//WriteMotionPrimitives(primitives);

	GetMotionPrimitiveCost(primitives, prim_cost);
	//WriteMotionPrimitiveCost(prim_cost);

	ReadDimension(dimension);
	//WriteDimension(dimension);

	FindLocation(dimension, startLocation, x, y);
	pos_start.x = x;
	pos_start.y = y;

	FindLocation(dimension, endLocation, x, y);
	pos_end.x = x;
	pos_end.y = y;

	for (count = 0; count < obsSize; count++)
	{
		FindLocation(dimension, sequenceOfObstacles[count], x, y);
		//cout << "x = " << x << " " << "y = " << y << endl;
		pos_obs.x = x;
		pos_obs.y = y;
		obstacles.push_back(pos_obs);
	}

        CAstar astar;
  	astar.SetPrimitive(primitives);
  	astar.SetDimension(dimension);
  	astar.SetObstacleMap(dimension, obstacles);
 	astar.SetSEpoint(pos_start, pos_end);
        astar.SetAvoidPositions(dimension, avoidPositions, avoidSize);

        astar.PrintAvoidPositions();

  	RobotPosition_Vector path = astar.FindCollisionFreePath();
  	
      	stepsSize = path.size();
	for (count = 0; count < stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
		FindIndex(dimension, path[count].x, path[count].y, index);
		//cout << index << endl;
		sequenceOfSteps[count] = index;
	}

        obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);

	return true;
}
