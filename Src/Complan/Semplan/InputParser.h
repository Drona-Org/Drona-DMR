/*
File: InputParser.h
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for parsing the inputs to complan.
*/

struct _Workspace
{
  	unsigned int length_x;
  	unsigned int length_y;
  	unsigned int number_of_uavs;
  	RobotPosition *pos_start;
  	RobotPosition *pos_end;
  	unsigned int number_of_points;
  	string total_cost;
};

typedef struct _Workspace Workspace;


struct _Dimension
{  
  	unsigned int length_x;
  	unsigned int length_y;
};

typedef struct _Dimension Dimension;

struct _MotionPrimitive_Cost
{
  	float max_cost;
  	float min_cost;
  	float min_cost_diff;
};

typedef struct _MotionPrimitive_Cost MotionPrimitive_Cost;

 
typedef std::vector<MotionPrimitive> MotionPrimitive_Vector;


void ReadMotionPrimitives(MotionPrimitive_Vector &);
void WriteMotionPrimitives(MotionPrimitive_Vector);
void GetMotionPrimitiveCost(MotionPrimitive_Vector, MotionPrimitive_Cost &);
void WriteMotionPrimitiveCost(MotionPrimitive_Cost);
void ReadDimension(Dimension &);
void WriteDimension(Dimension);
void FindLocation(Dimension, int, int &, int &);
void FindIndex(Dimension, int, int, int &);
