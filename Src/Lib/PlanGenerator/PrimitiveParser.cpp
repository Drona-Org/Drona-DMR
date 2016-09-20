/*
File: InputParser.cpp
Authors:
Indranil Saha (isaha@cse.iitk.ac.in)
Ankush Desai(ankush@eecs.berkeley.edu)

This file is used for parsing the inputs to complan.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "MotionPrimitives.h"
using namespace std;

void ReadMotionPrimitives(MotionPrimitive_Vector &primitives)
{
	ifstream ifp;

	string line;
	string str, str1;
	int location, location1, location2, location3, location4;
	WS_Coord pos_tmp;
	int xmin, ymin, xmax, ymax, zmax, zmin;

	RobotState q_i, q_f;
	WS_Coord pos_f;
	string fls;
	float cost;
	RobotPosition_Vector swath;
	WS_Coord pos_min;
	WS_Coord pos_max;

	ifp.open("primitive.txt");

	if (ifp.is_open())
	{
		while (getline(ifp, line))
		{
			location = line.find(":");

			if (line.substr(0, location) == "q_i")
			{
				istringstream(line.substr(location + 2, 1)) >> q_i.velocity;
			}

			if (line.substr(0, location) == "q_f")
			{
				istringstream(line.substr(location + 2, 1)) >> q_f.velocity;
			}

			if (line.substr(0, location) == "pos_f")
			{
				location1 = line.find('[');
				location2 = line.find(',');
				location3 = line.find(']');
				istringstream(line.substr(location1 + 1, location2 - location1 - 1)) >> pos_f.x;
				str = line.substr(location2 + 2, location3 - location2 - 2);
				location4 = str.find(',');
				istringstream(str.substr(0, location4)) >> pos_f.y;
				istringstream(str.substr(location4 + 2)) >> pos_f.z;
			}

			if (line.substr(0, location) == "cost")
			{
				fls = line.substr(location + 1);
				istringstream(fls) >> cost;
			}

			if (line.substr(0, location) == "swath")
			{
				str = line.substr(location + 1);
				xmin = 10000; ymin = 10000; zmin = 10000; xmax = -10000; ymax = -10000; zmax = -10000;
				location = str.find(';');
				while (location != -1)
				{
					location1 = str.find('[');
					location2 = str.find(',');
					location3 = str.find(']');
					istringstream(str.substr(location1 + 1, location2 - location1 - 1)) >> pos_tmp.x;
					str1 = str.substr(location2 + 2, location3 - location2 - 2);
					location4 = str1.find(',');
					istringstream(str1.substr(0, location4)) >> pos_tmp.y;
					istringstream(str1.substr(location4 + 2)) >> pos_tmp.z;
					swath.push_back(pos_tmp);
					if (pos_tmp.x < xmin)
						xmin = pos_tmp.x;
					if (pos_tmp.y < ymin)
						ymin = pos_tmp.y;
					if (pos_tmp.z < zmin)
						zmin = pos_tmp.z;
					if (pos_tmp.x > xmax)
						xmax = pos_tmp.x;
					if (pos_tmp.y > ymax)
						ymax = pos_tmp.y;
					if (pos_tmp.z > zmax)
						zmax = pos_tmp.z;
					str = str.substr(location + 1);
					location = str.find(';');
				}
				location1 = str.find('[');
				location2 = str.find(',');
				location3 = str.find(']');
				istringstream(str.substr(location1 + 1, location2 - location1 - 1)) >> pos_tmp.x;
				str1 = str.substr(location2 + 2, location3 - location2 - 2);
				location4 = str1.find(',');
				istringstream(str1.substr(0, location4)) >> pos_tmp.y;
				istringstream(str1.substr(location4 + 2)) >> pos_tmp.z;
				swath.push_back(pos_tmp);
				if (pos_tmp.x < xmin)
					xmin = pos_tmp.x;
				if (pos_tmp.y < ymin)
					ymin = pos_tmp.y;
				if (pos_tmp.z < zmin)
					zmin = pos_tmp.z;
				if (pos_tmp.x > xmax)
					xmax = pos_tmp.x;
				if (pos_tmp.y > ymax)
					ymax = pos_tmp.y;
				if (pos_tmp.z > zmax)
					zmax = pos_tmp.z;
				pos_min.x = xmin;
				pos_min.y = ymin;
				pos_min.z = zmin;
				pos_max.x = xmax;
				pos_max.y = ymax;
				pos_max.z = zmax;
				MotionPrimitive prim(q_i, q_f, pos_f, cost, swath, pos_min, pos_max);
				primitives.push_back(prim);
				swath.erase(swath.begin(), swath.end());
			}
		}
		ifp.close();
	}
}



void GetMotionPrimitiveCost(MotionPrimitive_Vector primitives, MotionPrimitive_Cost & prim_cost)
{
  	unsigned int count1, count2;
  	float str1, str2;
 
  	prim_cost.max_cost = 0;
  	prim_cost.min_cost = 100000;
  	prim_cost.min_cost_diff = 100000;

  	for (count1 = 0; count1 < primitives.size(); count1++)
  	{
    		str1 = primitives[count1].get_cost();
    		if (str1 > prim_cost.max_cost)
      			prim_cost.max_cost = str1;
    		if (str1 < prim_cost.min_cost)
      			prim_cost.min_cost = str1;

    		for (count2 = count1 + 1; count2 < primitives.size(); count2++)
    		{
      			str2 = primitives[count2].get_cost();
      			if (fabs(str1 - str2) > 0.0001 && fabs(str1 - str2) < prim_cost.min_cost_diff)
        			prim_cost.min_cost_diff = fabs(str1 - str2);
    		}
  	}
}


