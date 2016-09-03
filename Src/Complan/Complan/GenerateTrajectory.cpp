/*
File: GenerateTrajectory.cpp
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for generating the trajectory, as a sequence of the motion primitives.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "MotionPrimitives.h"
#include "InputParser.h"
#include "GenerateConstraints.h"
#include "Z3OutputParser.h"
#include "Complan.h"
#ifdef PLAT_WINDOWS
#include <Windows.h>
#endif

using namespace std;

//const unsigned int max_traj_length = 30;



void GenerateZ3File(MotionPrimitive_Vector primitives, Dimension dimension, RobotPosition_Vector obstacles, AvoidPositions* avoidPositions, int avoidSize, RobotPosition pos_start, RobotPosition pos_end, int number_of_points, float total_cost)
{
  ofstream ofp;

  ofp.open("constraints.smt2");

  /* Declare the variables */
  GenerateVariableDeclarations(ofp, number_of_points);


  /* Write the General Constraints */
  GenerateInitialLocationConstraints(ofp, pos_start);
  ofp << endl;

  GenerateObstacleConstraints(ofp, dimension, obstacles);
  ofp << endl;

  GenerateTransitionConstraints(ofp, primitives, dimension, obstacles, avoidPositions, avoidSize, number_of_points);
  ofp << endl;

  //GenerateCostConstraint(ofp, number_of_points, total_cost);
  //ofp << endl;

  /* Write the specification constraints */
  GenerateFinalDestinationConstraints(ofp, pos_end, number_of_points);

  /* Check the satisfiability of the constraints and output the model */
  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  GenerateOutputConstraints(ofp, number_of_points);

  ofp.close();
}


bool GenerateTrajectory(MotionPrimitive_Vector primitives, MotionPrimitive_Cost prim_cost, Dimension dimension, RobotPosition_Vector obstacles, AvoidPositions* avoidPositions, int avoidSize, RobotPosition pos_start, RobotPosition pos_end, int* trajectory_length)
{
  ifstream ifp;
  string line;
  unsigned int count;
  float cost;
  ofstream ofp;

  //count = 2;
  count = abs(pos_end.x - pos_start.x) + abs(pos_end.y - pos_start.y);
  cout << "Initial Trajectory Length = " << count << endl;
  while (true)
  {
    cost = count * prim_cost.max_cost;
    GenerateZ3File(primitives, dimension, obstacles, avoidPositions, avoidSize, pos_start, pos_end, count, cost);
    system("z3 constraints.smt2 > z3_output");

    ifp.open("z3_output");
    if (ifp.is_open())
    {
      getline(ifp, line);
      ifp.close();
    }
    if (line == "unsat")
    {
      count = count + 1;
      if (count > max_traj_length)
      {
        cout << "Complan Error: Trajectory does not exist.." << endl;
        return false;
      }
    }
    else if (line == "sat")
    {
#ifdef PLAT_WINDOWS
	CopyFile(L"z3_output", L"z3_output_sat", FALSE);
#else 
	system("cp z3_output z3_output_sat");
#endif // PLAT_WINDOWS
      break;
    }
    else
    {
      cout << "Complan Error : unknown output from z3.." << endl;
      count = count + 1;
      if (count > max_traj_length)
      {
        return false;
      }
    }
    if (count > max_traj_length)
      break;
  }
  
  //system("perl processoutputfile.pl");
  //system("mv planner_output plan_noopt");


  *trajectory_length = count;

  return true;
}


void OptimizeTrajectory(MotionPrimitive_Vector primitives, MotionPrimitive_Cost prim_cost, Dimension dimension, RobotPosition_Vector obstacles, AvoidPositions* avoidPositions, int avoidSize, RobotPosition pos_start, RobotPosition pos_end, int trajectory_length)
{
  float max_total_cost, min_total_cost, current_cost;
  ifstream ifp;
  string line;
  ofstream ofp;

  max_total_cost = trajectory_length * prim_cost.max_cost;
  min_total_cost = trajectory_length * prim_cost.min_cost;
  current_cost = (max_total_cost + min_total_cost) / 2;
#ifdef PLAT_WINDOWS
  DeleteFile(L"z3_output_sat");
  MoveFile(L"z3_output", L"z3_output_sat");
#else
  system("mv z3_output z3_output_sat");
#endif // PLAT_WINDOWS

  while (max_total_cost - min_total_cost > prim_cost.min_cost_diff)
  {
    GenerateZ3File(primitives, dimension, obstacles, avoidPositions, avoidSize, pos_start, pos_end, trajectory_length, current_cost);
    system("z3 constraints.smt2 > z3_output");

    ifp.open("z3_output");
    getline(ifp, line);
    ifp.close();

    if (line == "unsat")
    {
      min_total_cost = current_cost;
    }
    else if (line == "sat")
    {
      //max_total_cost = ExtractTrajectoryCostInformation();
      max_total_cost = current_cost;
#ifdef PLAT_WINDOWS
	  DeleteFile(L"z3_output_sat");
	  MoveFile(L"z3_output", L"z3_output_sat");
#else
	  system("mv z3_output z3_output_sat");
#endif // PLAT_WINDOWS
    }
    else
    {
      cout << "unknown output from z3.." << endl;
      min_total_cost = current_cost;
    }
    current_cost = (max_total_cost + min_total_cost) / 2;
    //cout << "max cost = " << max_total_cost << endl;
    //cout << "min cost = " << min_total_cost << endl;
    //cout << "current cost = " << current_cost << endl;
  }

#ifdef PLAT_WINDOWS
  DeleteFile(L"z3_output");
  MoveFile(L"z3_output_sat", L"z3_output");
#else
  system("mv z3_output_sat z3_output");
#endif // PLAT_WINDOWS
  //system("perl processoutputfile.pl");
  //system("mv planner_output plan_opt");

  //cout << "Cost  = " << ExtractTrajectoryCostInformation() << endl << endl;
}
