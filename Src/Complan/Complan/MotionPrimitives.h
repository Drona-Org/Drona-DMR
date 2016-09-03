/*
File: MotionPrimitives.h
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file defines data types for storing the robot state, position and motion primitive information.
*/
#include <iostream>
#include <vector>
using namespace std;


struct _RobotState
{
  int velocity;
  //int configuration;
};

typedef struct _RobotState RobotState;

struct _RobotPosition
{
  int x;
  int y;
};

typedef struct _RobotPosition RobotPosition;

typedef std::vector<RobotPosition> RobotPosition_Vector;

class MotionPrimitive
{
  private:
    RobotState q_i;
    RobotState q_f;
    RobotPosition pos_f;
    float cost;
    RobotPosition_Vector swath;    
    RobotPosition pos_min;
    RobotPosition pos_max;

  public:
	  MotionPrimitive(RobotState, RobotState, RobotPosition, float, RobotPosition_Vector, RobotPosition, RobotPosition);
    RobotState get_q_i();
    RobotState get_q_f();
    RobotPosition get_pos_f();
    float get_cost();
    RobotPosition_Vector get_swath();
    RobotPosition get_pos_min();
    RobotPosition get_pos_max();
	~MotionPrimitive();
};
