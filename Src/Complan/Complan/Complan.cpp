#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "MotionPrimitives.h"
#include "InputParser.h"
#include "GenerateConstraints.h"
#include "GenerateTrajectory.h"
#include "Z3OutputParser.h"
#include "Complan.h"

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
	_Out_ int* stepsSize
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
	int* stepsSize
	)
#endif
{
	MotionPrimitive_Vector primitives;
	Dimension dimension;
	RobotPosition_Vector obstacles;
	Workspace workspace;
	MotionPrimitive_Cost prim_cost;
	int trajectory_length;
	string line;
	int count;
	int x, y;
	RobotPosition pos_start, pos_end, pos_obs;

	ReadMotionPrimitives(primitives);
	//writePrimitives(primitives);

	GetMotionPrimitiveCost(primitives, prim_cost);
	//writePrimitiveCost(prim_cost);

	ReadDimension(dimension);
	//writeDimension(dimension);

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

	bool result;
	result = GenerateTrajectory(primitives, prim_cost, dimension, obstacles, avoidPositions, avoidSize, pos_start, pos_end, &trajectory_length);

	if (!result)
		return result;

	OptimizeTrajectory(primitives, prim_cost, dimension, obstacles, avoidPositions, avoidSize, pos_start, pos_end, trajectory_length);

	int index;
	vector< vector<int> > X, Y;

	X.clear();
	result = ExtractTrajectoryRobotPositionXInformation(X);
	if (!result)
		return result;
	
        Y.clear();
	result = ExtractTrajectoryRobotPositionYInformation(Y);
	if (!result)
		return result;

	if (X.size() != Y.size())
	{
		cout << "Complan Error : The size of X array is not equal to the size of Y array!!" << endl;
		return false;
	}
	else
	{
		*stepsSize = (X[0]).size();
		//output_seq_of_locations[output_size];
		for (count = 0; count < *stepsSize; count++)
		{
			//cout << (X[0])[count] << " " << (Y[0])[count] << endl;
			FindIndex(dimension, (X[0])[count], (Y[0])[count], index);
			//cout << index << endl;
			sequenceOfSteps[count] = index;
		}
	}

#ifdef PLAT_WINDOWS
	//perform clean-up
	DeleteFile(L"z3_output");
	DeleteFile(L"Constraints.smt2");
#endif
	return true;
}
