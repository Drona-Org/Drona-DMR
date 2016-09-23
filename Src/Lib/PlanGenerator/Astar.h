#ifndef DRONA_ASTAR_H
#define DRONA_ASTAR_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include "MotionPrimitives.h"
#include "../WorkspaceParser/Workspace.h"

using namespace std;


const int Delta = 1;

const int Max_Traj_Length = 1000;

struct node{
  	double G;
  	double H;
  	double F;
  	WS_Coord parentPos;
  	WS_Coord selfPos;
  	int primID;
  	RobotState q_f;
	int timestep;
};


struct nodePath{
  	WS_Coord pos;
  	int index;
  	int primID;
};


struct A {
        int PositionsOccupied[1000];
        int size;
};

typedef struct A AvoidPositions;


class CAstar  
{
  private:
  	MotionPrimitive_Vector primitives;
  	WS_Dimension dimension;
  	int ***obsmap;
  	WS_Coord start, end;
    vector <RobotPosition_Vector> avoidTrajs;
 
  	vector<node> openList;
  	vector<node> closeList;
  	RobotPosition_Vector path;
  	vector<nodePath> gFindPath;
  	
        double Get_H(WS_Coord , WS_Coord );
  	node NodeCreate(double , double , double , WS_Coord , WS_Coord , int , RobotState , int);
  	RobotPosition_Vector ExtractPath(WS_Coord , vector<node> );
  
  public:
  	CAstar();
  	void SetPrimitive(MotionPrimitive_Vector );
  	void SetDimension(WS_Dimension);
  	void SetObstacleMap(WS_Dimension , RobotPosition_Vector );
  	void SetSEpoint(WS_Coord , WS_Coord );
    void SetAvoidPositions(WS_Dimension, AvoidPositions* , int );
    void PrintAvoidPositions();
  	int ***GetObstacleMap();
    RobotPosition_Vector FindCollisionFreePath();
    void printTrajectory(int *** , RobotPosition_Vector );
  	virtual ~CAstar();
};

#endif
