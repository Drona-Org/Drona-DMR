/*
File: MotionPrimitives.h
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file defines data types for storing the robot state, position and motion primitive information.
*/
#include <iostream>
#include <vector>
#include "Workspace.h"
using namespace std;


struct _RobotState
{
  	int velocity;
  	//int configuration;
};

typedef struct _RobotState RobotState;

typedef std::vector<WS_Coord> RobotPosition_Vector;

class MotionPrimitive
{
  private:
    	RobotState q_i;
    	RobotState q_f;
    	WS_Coord pos_f;
    	float cost;
    	RobotPosition_Vector swath;    
		WS_Coord pos_min;
		WS_Coord pos_max;

  public:
	MotionPrimitive(RobotState, RobotState, WS_Coord, float, RobotPosition_Vector, WS_Coord, WS_Coord);
    	RobotState get_q_i();
    	RobotState get_q_f();
		WS_Coord get_pos_f();
    	float get_cost();
    	RobotPosition_Vector get_swath();
		WS_Coord get_pos_min();
		WS_Coord get_pos_max();
	~MotionPrimitive();
};

struct _MotionPrimitive_Cost
{
	float max_cost;
	float min_cost;
	float min_cost_diff;
};

typedef struct _MotionPrimitive_Cost MotionPrimitive_Cost;


typedef std::vector<MotionPrimitive> MotionPrimitive_Vector;


void ReadMotionPrimitives(MotionPrimitive_Vector &);
void GetMotionPrimitiveCost(MotionPrimitive_Vector, MotionPrimitive_Cost &);
