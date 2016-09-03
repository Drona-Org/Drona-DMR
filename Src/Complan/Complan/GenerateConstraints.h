/*
File: GenerateConstraints.h
Authors: 
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for generating Z3 constraints.
*/


#include "Complan.h"

void GenerateVariableDeclarations(ofstream &, int );
void GenerateInitialLocationConstraints(ofstream &, RobotPosition );
void GenerateFinalDestinationConstraints(ofstream & , RobotPosition , int );
void GenerateObstacleConstraints(ofstream & , Dimension , RobotPosition_Vector );
void GenerateTransitionConstraints(ofstream & , MotionPrimitive_Vector , Dimension , RobotPosition_Vector , AvoidPositions* , int , int );
void GenerateCostConstraint(ofstream & , int , float );
void GenerateOutputConstraints(ofstream & , int );
string FloatToReal(float flf);
template <typename T> string ToSTR(const T& t);

#define MAX_SIZE_OF_WORKSPACE 100
