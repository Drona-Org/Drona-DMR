/*
File: GenerateConstraints.cpp
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for generating Z3 constraints.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "MotionPrimitives.h"
#include "InputParser.h"
#include "GenerateConstraints.h"
#include "Complan.h"

void GenerateVariableDeclarations(ofstream &ofp, int number_of_points)
{
  int count;

  ofp << "(declare-fun obstacle (Int Int) Bool)" << endl;
  ofp << endl;

  ofp << "(declare-const total_cost Real)" << endl;
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(declare-const prim_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
    ofp << "(declare-const x_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
      ofp << "(declare-const y_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
    ofp << "(declare-const vel_i_1_" << count << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
      ofp << "(declare-const vel_f_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
      ofp << "(declare-const x_f_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
      ofp << "(declare-const y_f_1_" << count + 1 << " Int)" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
      ofp << "(declare-const cost_1_" << count + 1 << " Real)" << endl;
  }
  ofp << endl;
}


void GenerateInitialLocationConstraints(ofstream &ofp, RobotPosition pos_start)
{
  ofp << "(assert (= x_1_1 " << pos_start.x << "))" << endl;
  ofp << "(assert (= y_1_1 " << pos_start.y << "))" << endl;
  ofp << endl;
}


void GenerateFinalDestinationConstraints(ofstream &ofp, RobotPosition pos_end, int number_of_points)
{
  ofp << "(assert (= x_1_" << number_of_points << " " << pos_end.x << "))" << endl;
  ofp << "(assert (= y_1_" << number_of_points << " " << pos_end.y << "))" << endl;
  ofp << endl;
}


void GenerateObstacleConstraints(ofstream &ofp, Dimension dimension, RobotPosition_Vector obstacles)
{
  int count, count1, count2;

  bool workspace_obstacles[MAX_SIZE_OF_WORKSPACE][MAX_SIZE_OF_WORKSPACE];


  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      workspace_obstacles[count1][count2] = false;
    }
  }

  for (count = 0; count < obstacles.size(); count++)
  {
    workspace_obstacles[obstacles[count].x][obstacles[count].y] = true;
  }
  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (workspace_obstacles[count1][count2] == true)
        ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "true" << "))" << endl;
    }
  }
  ofp << endl;
}


void GenerateTransitionConstraints(ofstream &ofp, MotionPrimitive_Vector primitives, Dimension dimension, RobotPosition_Vector obstacles, AvoidPositions* avoidPositions, int avoidSize, int number_of_points)
{
  RobotState q_i, q_f;
  RobotPosition pos_f;
  RobotPosition_Vector swath, swath1, swath2;
  float cost;
  int x, y;
  int count, count1, count2, count3, count4;

  ofp << "(assert (= vel_i_1_1 0))" << endl;
  ofp << "(assert (= vel_f_1_" << number_of_points - 1 << " 0))" << endl;
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(assert (and (>= prim_1_" << count + 1 << " 1) (<= prim_1_" << count + 1 << " " << primitives.size() << ")))" << endl;
  }
  ofp << endl;

  for (count = 1; count < number_of_points - 1; count++)
  {
    ofp << "(assert (and (>= vel_i_1_" << count + 1 << " 0) (<= vel_i_1_" << count + 1 << " 8)))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 2; count++)
  {
    ofp << "(assert (and (>= vel_f_1_" << count + 1 << " 0) (<= vel_f_1_" << count + 1 << " 8)))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
      ofp << "(assert (and (>= x_1_" << count + 1 << " 0) (< x_1_" << count + 1 << " " << dimension.length_x << ")))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
      ofp << "(assert (and (>= y_1_" << count + 1 << " 0) (< y_1_" << count + 1 << " " << dimension.length_y << ")))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
    for (count1 = 0; count1 < primitives.size(); count1++)
    {
      q_i = primitives[count1].get_q_i();
      q_f = primitives[count1].get_q_f();
      pos_f = primitives[count1].get_pos_f();
      cost = primitives[count1].get_cost();
      swath = primitives[count1].get_swath();
      ofp << "(assert (or (not (= prim_1_" << count + 1 << " " << count1 + 1 << "))" << endl;
      ofp << "(and (= vel_i_1_" << count + 1 << " " << q_i.velocity << ")" << endl;
      ofp << "     (= vel_f_1_" << count + 1 << " " << q_f.velocity << ")" << endl;
      ofp << "     (= x_f_1_" << count + 1 << " " << pos_f.x << ")" << endl;
      ofp << "     (= y_f_1_" << count + 1 << " " << pos_f.y << ")" << endl;
      ofp << "     (= cost_1_" << count + 1 << " " << FloatToReal(cost) << ")" << endl;
     
      // Dealing with static obstacles 
      for (count2 = 0; count2 < swath.size(); count2++)
      {
        ofp << "     (= (obstacle (+ x_1_" << count + 1 << " " << swath[count2].x << ") (+ y_1_" << count + 1 << " " << swath[count2].y << ")) false)" << endl;
      }
      
      // Dealing with trajectories of other robots
      /*for (count2 = 0; count2 < swath.size(); count2++)
      {
        for (count3 = 0; count3 < avoidSize; count3++)
        {
          if (count <= avoidPositions[count3].size - 1)
          {
            FindLocation(dimension, (avoidPositions[count3].PositionsOccupied)[count], x, y);
          }
          else
          {
            FindLocation(dimension, (avoidPositions[count3].PositionsOccupied)[avoidPositions[count3].size - 1], x, y);
          }
          ofp << "     (or (not(= (+ x_1_" << count + 1 << " " << swath[count2].x << ") " << x << ")) (not(= (+ y_1_" << count + 1 << " " << swath[count2].y << ") " << y << ")))" << endl; 
        }
      }*/

      for (count4 = -Delta; count4 <= Delta; count4++)
      { 
        for (count2 = 0; count2 < swath.size(); count2++)
        {
          for (count3 = 0; count3 < avoidSize; count3++)
          {
            if (count <= avoidPositions[count3].size - 1)
            {
              FindLocation(dimension, (avoidPositions[count3].PositionsOccupied)[count + Delta + count4], x, y);
            }
            else
            {
              FindLocation(dimension, (avoidPositions[count3].PositionsOccupied)[avoidPositions[count3].size - 1], x, y);
            }
            ofp << "     (or (not(= (+ x_1_" << count + 1 << " " << swath[count2].x << ") " << x << ")) (not(= (+ y_1_" << count + 1 << " " << swath[count2].y << ") " << y << ")))" << endl;
          }
        }
      }
      
      ofp << ")))" << endl;
      ofp << endl;
    }
  }
  ofp << endl;

  // Dealing with trajectories of other robots
  // If the length of the trajectory of the current robot is less than the trajectories of the other robots
  /*for (count = 0; count < avoidSize; count++)
  {
    for (count1 = number_of_points; count1 <= avoidPositions[count].size; count1++)
    {
      FindLocation(dimension, (avoidPositions[count].PositionsOccupied)[count1 - 1], x, y);      
      ofp << "(assert (or (not(= x_1_" << number_of_points << " " << x << ")) (not (= y_1_" << number_of_points << " " << y << "))))" << endl;
    }
  }
  */
  for (count = 0; count < avoidSize; count++)
  {
    for (count1 = number_of_points + Delta; count1 <= avoidPositions[count].size; count1++)
    {
      FindLocation(dimension, (avoidPositions[count].PositionsOccupied)[count1 - 1], x, y);
      for (count2 = -Delta; count2 <= 0; count2++)
      {
        ofp << "(assert (or (not(= x_1_" << number_of_points + count2 << " " << x << ")) (not (= y_1_" << number_of_points + count2 << " " << y << "))))" << endl;
      }
      for (count2 = 1; count2 <= Delta; count2++)
      {
        ofp << "(assert (or (not(= x_1_" << number_of_points << " " << x << ")) (not (= y_1_" << number_of_points << " " << y << "))))" << endl;
      }
    }
  }
 
  for (count = 1; count < number_of_points; count++)
  {
    ofp << "(assert (= x_1_" << count + 1 << " (+ x_1_" << count << " x_f_1_" << count << ")))" << endl;
    ofp << "(assert (= y_1_" << count + 1 << " (+ y_1_" << count << " y_f_1_" << count << ")))" << endl;
  }
  ofp << endl;

  for (count = 1; count < number_of_points - 1; count++)
  {
    ofp << "(assert (= vel_i_1_" << count + 1 << " vel_f_1_" << count << "))" << endl;
  }
  ofp << endl;
}

/*
void GenerateCostConstraint(ofstream &ofp, int number_of_points, float total_cost)
{
  unsigned int count;

  ofp << "(assert (= total_cost (+";
  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << " cost_1_" << count + 1;
  }
  ofp << ")))" << endl;
  ofp << "(assert (<= total_cost " << FloatToReal(total_cost) << "))" << endl;
  ofp << endl;
}
*/

void GenerateOutputConstraints(ofstream &ofp, int number_of_points)
{
  int count;

  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (prim_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
    ofp << "(get-value (x_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points; count++)
  {
    ofp << "(get-value (y_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;
  
  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (vel_i_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;
   
  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (vel_f_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (x_f_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;

  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (y_f_1_" << count + 1 << "))" << endl;
  }
  ofp << endl;
  
  for (count = 0; count < number_of_points - 1; count++)
  {
    ofp << "(get-value (cost_1_" << count + 1 << "))" << endl;
  }
  ofp << "(get-value (total_cost))" << endl;
  ofp << endl;
}


string FloatToReal(float flf)
{
  string str1, str2;
  long int num, den;
  int length;
  int pos;
  string fls;

  ostringstream s;
  s << flf;
  fls = s.str(); 
  pos = fls.find('.');
  if (pos == -1)
  {
    return fls;
  }
  else
  {
    length = fls.length();
    den = pow(10, (length - pos));
    num = flf * den;
	str1 = ToSTR(num);
	str2 = ToSTR(den);
    return ("(/ " + str1 + " " + str2 + ")");
  }
}


template <typename T> string ToSTR(const T& t)
{ 
  ostringstream os; 
  os << t; 
  return os.str(); 
} 
