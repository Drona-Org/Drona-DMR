/*
File: Complan.h
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

The grid locations are assinged integer values as follows for a 4x4 grid

--------------------
4 | 5 | 12   | 13 |
--------------------
3  | 6  | 11  |14 |
--------------------
2  | 7  | 10 | 	15 |
--------------------
1  |  8  | 9 | 16  |
--------------------
*/

/** Provides an interface function for generating motion plans with rest to a sequence of obstacles.
* @param[in] startLocation Starting location of the robot.
* @param[in] endLocation Starting location of the robot.
* @param[in] sequenceOfObstacles Integer sequence of obstacle locations, that identify the grid location the robot should avoid.
* @param[in] obsSize Size of the sequenceOfObstacles list.
* @param[out] sequenceOfSteps Integer sequence of locations, path from start to end.
* @param[out] Size of sequenceOfSteps.
* @returns An instance of a primitive. Caller is responsible for freeing.
* @see PrtFreeType
*/

#ifndef COMPLAN_H
#define COMPLAN_H

#ifdef PLAT_WINDOWS
#include <Windows.h>
#endif

/*

*/

const unsigned int max_traj_length = 50;

const int Delta = 0;

#ifdef PLAT_WINDOWS
#ifdef __cplusplus
extern "C"{
#define BOOLEAN bool
#endif

	typedef struct __AvoidPositions {
		int* PositionsOccupied;
		int size;
	} AvoidPositions;

	__declspec(dllexport)
		BOOLEAN GenerateMotionPlanFor(
		_In_ int startLocation,
		_In_ int endLocation,
		_In_ int* sequenceOfObstacles,
		_In_ int obsSize,
		_In_ AvoidPositions* avoidPositions,
		_In_ int avoidSize,
		_Out_ int sequenceOfSteps[100],
		_Out_ int* stepsSize
		);
#ifdef __cplusplus
}
#endif
#else

struct A {
	int PositionsOccupied[100];
    int size;
};

typedef struct A AvoidPositions; 


bool GenerateMotionPlanFor(
	int startLocation,
	int endLocation,
	int* sequenceOfObstacles,
	int obsSize,
	AvoidPositions* avoidPositions,
	int avoidSize,
	int sequenceOfSteps[100],
	int* stepsSize
	);
#endif



#endif
