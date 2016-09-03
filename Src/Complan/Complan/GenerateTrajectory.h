/*
File: GenerateTrajectory.h
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for generating the trajectory, as a sequence of the motion primitives.
*/


#include "Complan.h"

bool GenerateTrajectory(MotionPrimitive_Vector , MotionPrimitive_Cost , Dimension , RobotPosition_Vector , AvoidPositions* , int , RobotPosition , RobotPosition, int*);
void OptimizeTrajectory(MotionPrimitive_Vector , MotionPrimitive_Cost , Dimension , RobotPosition_Vector , AvoidPositions* , int , RobotPosition , RobotPosition , int );
