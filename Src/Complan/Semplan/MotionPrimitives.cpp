/*
File: MotionPrimitives.cpp
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file defines data types for storing the robot state, position and motion primitive information.
*/

#include "MotionPrimitives.h"

MotionPrimitive::MotionPrimitive(RobotState q_i, RobotState q_f, RobotPosition pos_f, float cost, RobotPosition_Vector swath, RobotPosition pos_min, RobotPosition pos_max)
{
  this->q_i = q_i;
  this->q_f = q_f;
  this->pos_f = pos_f;
  this->cost = cost;
  this->swath = swath;
  this->pos_min = pos_min;
  this->pos_max = pos_max;
}

RobotState MotionPrimitive::get_q_i()
{
  return q_i;
}

RobotState MotionPrimitive::get_q_f()
{
  return q_f;
}

RobotPosition MotionPrimitive::get_pos_f()
{
  return pos_f;
}

float MotionPrimitive::get_cost()
{
  return cost;
}

RobotPosition_Vector MotionPrimitive::get_swath()
{
  return swath;
}

RobotPosition MotionPrimitive::get_pos_min()
{
  return pos_min;
}

RobotPosition MotionPrimitive::get_pos_max()
{
  return pos_max;
}

MotionPrimitive::~MotionPrimitive()
{
}
