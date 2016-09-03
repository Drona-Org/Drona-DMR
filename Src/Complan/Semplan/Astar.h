#include <memory>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include "MotionPrimitives.h"
#include "InputParser.h"


using namespace std;


struct node{
  	double G;
  	double H;
  	double F;
  	RobotPosition parentPos;
  	RobotPosition selfPos;
  	int primID;
  	RobotState q_f;
	int timestep;
};


struct nodePath{
  	RobotPosition pos;
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
  	Dimension dimension;
  	int **obsmap;
  	RobotPosition start, end;
        vector <RobotPosition_Vector> avoidTrajs;
 
  	vector<node> openList;
  	vector<node> closeList;
  	RobotPosition_Vector path;
  	vector<nodePath> gFindPath;
  	
        double Get_H(RobotPosition , RobotPosition );
  	node NodeCreate(double , double , double , RobotPosition , RobotPosition , int , RobotState , int);
  	RobotPosition_Vector ExtractPath(RobotPosition , vector<node> );
  
  public:
  	CAstar();
  	void SetPrimitive(MotionPrimitive_Vector );
  	void SetDimension(Dimension );
  	void SetObstacleMap(Dimension , RobotPosition_Vector );
  	void SetSEpoint(RobotPosition , RobotPosition );
        void SetAvoidPositions(Dimension, AvoidPositions* , int );
        void PrintAvoidPositions();
  	int **GetObstacleMap();
        RobotPosition_Vector FindCollisionFreePath();
        void printTrajectory(int ** , RobotPosition_Vector );
  	virtual ~CAstar();
};

