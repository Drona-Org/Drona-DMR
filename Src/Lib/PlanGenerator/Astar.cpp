//////////////////////////////////////////////////////////////////////
// Astar.cpp: implementation of the CAstar class.
//////////////////////////////////////////////////////////////////////


#include "Astar.h"


bool compare(const node &a, const node &b )
{
   	return a.F < b.F; 
}


bool compare2(const nodePath &a, const nodePath &b )
{
  	return a.index > b.index;
}


CAstar::CAstar()
{
  	obsmap = NULL;
}


CAstar::~CAstar()
{
  	unsigned int count;
 
  	if(obsmap != NULL)
  	{
		for (count = 0; count < dimension.x_dim; count++)
		{
			delete[] obsmap[count];
		}
    	delete[] obsmap;
    	obsmap = NULL;
  	}
}


void CAstar::SetSEpoint(WS_Coord start, WS_Coord end)
{
  	this->start = start;
 	this->end = end;
}


void CAstar::SetPrimitive(MotionPrimitive_Vector primitives)
{
  	this->primitives = primitives;
}


void CAstar::SetDimension(WS_Dimension dimension)
{
  	this->dimension = dimension;
}


void CAstar::SetObstacleMap(WS_Dimension dimension, RobotPosition_Vector obstacles)
{
	unsigned int count, count1, count2, count3;

	obsmap = new int**[dimension.x_dim];

	for (count = 0; count < dimension.x_dim; count++)
	{
		obsmap[count] = new int*[dimension.y_dim];
		for (count1 = 0; count1 < dimension.y_dim; count1++)
		{
			obsmap[count][count1] = new int[dimension.z_dim];
		}
	}

	for (count1 = 0; count1 < dimension.x_dim; count1++)
	{
		for (count2 = 0; count2 < dimension.y_dim; count2++)
		{
			for (count3 = 0; count3 < dimension.z_dim; count3++)
			{
				obsmap[count1][count2][count3] = 0;
			}
		}
	}

	for (count = 0; count < obstacles.size(); count++)
	{
		obsmap[obstacles[count].x][obstacles[count].y][obstacles[count].z] = 1;
	}
}


void CAstar::SetAvoidPositions(WS_Dimension dimension, AvoidPositions* avoidPositions, int avoidSize)
{
  	unsigned int count1, count2, count3;
  	int original_size;
  	WS_Coord tmp_pos;
  	RobotPosition_Vector tmp_pos_vec;
	
  	for (count1 = 0; count1 < avoidSize; count1++)
  	{
 		// If the current trajectory size is greater than the size of avoidTrajs,
		// extend avoidTrajs up to the length of the current trajectory by repeating
		// the final locations
		if (avoidTrajs.size() < avoidPositions[count1].size)
   		{
			original_size = avoidTrajs.size();
			avoidTrajs.resize(avoidPositions[count1].size);
			tmp_pos_vec = avoidTrajs[avoidTrajs.size() - 1];
			for (count2 = original_size; count2 < avoidPositions[count1].size; count2++)
			{
				for (count3 = 0; count3 < tmp_pos_vec.size(); count3++)
				{
					avoidTrajs[count2].push_back(tmp_pos_vec[count3]);
				}
			}
		}

		// Add the positions in the current trajectories to avoidTrajs
    		for (count2 = 0; count2 < avoidPositions[count1].size; count2++)
    		{
				WS_Coord coord;
      			coord = ExtractCoordFromGridLocation(avoidPositions[count1].PositionsOccupied[count2], dimension);
				SetCoordTo(&tmp_pos, coord);
      			//avoidTrajs.resize(count2 + 1);
      			avoidTrajs[count2].push_back(tmp_pos);
    		}

		// If the current trajectory size is less than the size of avoidTrajs,
		// extend the current trajectory upto the length of avoidTrajs by 
		// repeating the final position of the current trajectory
		if (avoidPositions[count1].size < avoidTrajs.size())
		{
			for (count2 = avoidPositions[count1].size; count2 < avoidTrajs.size(); count2++)
			{
				avoidTrajs[count2].push_back(tmp_pos);
			}
		}
  	}
}


void CAstar::PrintAvoidPositions()
{
	unsigned int count1, count2;
	cout << "Avoids Trajectories:" << endl;
	for (count1 = 0; count1 < avoidTrajs.size(); count1++)
	{
		cout << "Time : " << count1 << endl;
		for (count2 = 0; count2 < avoidTrajs[count1].size(); count2++)
		{
			cout << ConvertCoordToGridLocation(avoidTrajs[count1][count2], dimension) << " ";
		}
		cout << endl;
	}
}


int ***CAstar::GetObstacleMap()
{
  	return obsmap;
}


node CAstar::NodeCreate(double g, double h, double f, WS_Coord p, WS_Coord m, int primid, RobotState q_f, int timestep)
{
  	node temp;
  	temp.G = g;
  	temp.H = h;
  	temp.F = f;
  	temp.parentPos = p;
  	temp.selfPos = m;
  	temp.primID = primid;
  	temp.q_f = q_f;
  	temp.timestep = timestep;
  	return temp;
}


double CAstar::Get_H (WS_Coord current, WS_Coord end)
{
	int cost_hX = abs(end.x - current.x);
	int cost_hY = abs(end.y - current.y);
	int cost_hZ = abs(end.z - current.z);
	double cost_h = cost_hX + cost_hY + cost_hZ;
	return cost_h;
}


RobotPosition_Vector CAstar::ExtractPath(WS_Coord end, vector<node> closeList)
{
  	unsigned int count1, count2, count3;
  	WS_Coord F;
  	WS_Coord tmppos;

	SetCoordTo(&F, end);

  	int index=0;
  	nodePath tempPath;
  	tempPath.index = index++;
  	tempPath.pos = end;
  	tempPath.primID = 0;
  	gFindPath.push_back(tempPath);
  	while(1)
  	{
		for (count3 = 0; count3 < closeList.size(); count3++)
		{
			if ((closeList[count3].selfPos.x == F.x) && (closeList[count3].selfPos.y == F.y) && (closeList[count3].selfPos.z == F.z))
			{
				SetCoordTo(&F, closeList[count3].parentPos);
				tempPath.index = index++;
				tempPath.pos = F;
				tempPath.primID = closeList[count3].primID;
				gFindPath.push_back(tempPath);
				break;
			}
		}
		if (CoordAreEqual(F, start)) break;
  	}

  	sort(gFindPath.begin(), gFindPath.end(),compare2);
  	for(count1 = 0; count1 < gFindPath.size(); count1++)
  	{
		SetCoordTo(&tmppos, gFindPath[count1].pos);
    	path.push_back(tmppos);
    	/*
    	RobotPosition_Vector swath = primitives[gFindPath[count1].primID - 1].get_swath();
    	for(count2 = 0; count2 < swath.size(); count2++)
    	{
      		tmppos.x = gFindPath[count1].pos.x + swath[count2].x;
      		tmppos.y = gFindPath[count1].pos.y + swath[count2].y;
      		path.push_back(tmppos);
      		//path.push_back( make_pair(gFindPath[count1].x + swath[count2].x,  gFindPath[count1].y  + swath[count2].y) );
    	}
    	*/
  	}
  	return path;
}


bool isBlocked(WS_Coord pos, int timestep, int ***obsmap, vector <RobotPosition_Vector> avoidTrajs)
{
	int count1, count2;
	bool collisionKey = false;	

	// Static Obstacles
	if ( obsmap[pos.x][pos.y][pos.z] == 1 )
        {
                return true;
       	}
        
	// Other Robots
    for (count1 = -Delta; count1 <= Delta; count1++)
    {
        if (timestep + count1 >=0 && timestep + count1 < avoidTrajs.size())
        {
            for (count2 = 0; count2 < avoidTrajs[timestep + count1].size(); count2++)
            {
				if (CoordAreEqual(pos, avoidTrajs[timestep + count1][count2]))
                {
                        collisionKey = true;
                        break;
                }
            }
        }

        // The final positions of the other robots should not interfere with the trajectory
        // of the current robot
        if (timestep + count1 > avoidTrajs.size())
        {
            for (count2 = 0; count2 < avoidTrajs[avoidTrajs.size()-1].size(); count2++)
                {
                    if (CoordAreEqual(pos, avoidTrajs[avoidTrajs.size() - 1][count2]))
                    {
                            collisionKey = true;
                            break;
                    }
                }
        }
        if (collisionKey) 
			break;
    }
	return collisionKey;
}



RobotPosition_Vector CAstar::FindCollisionFreePath()
{
  	int count1, count2, count3;
  	MotionPrimitive_Vector tempPrimF;
	WS_Coord currpos, nextpos;
	WS_Coord tmppos;
  	double g,h,f;
  	RobotState q;
  	int timestep;
	bool key, blockedKey;

  	while(1)
  	{	
    		if(closeList.size()==0)
    		{	
      			g = 0;
      			h = Get_H(start, end);
      			f = g+h;
      			q.velocity = 0;
				tmppos.x = 0; tmppos.y = 0; tmppos.z = 0;
      			closeList.push_back(NodeCreate(g,h,f,tmppos, start, 0, q, 0));
    		}
    		else
    		{
      			if(openList.size() == 0 )
      			{
        			cout << "These motion primitives are not applicable for this problem.." << endl;
					exit(0);	
      			}
      			
				sort(openList.begin(), openList.end(),compare);
      			closeList.push_back( openList[0] );
      			openList.erase(openList.begin());
			
				if (closeList[closeList.size()-1].timestep > Max_Traj_Length)
				{
					cout << "No trajectory of length less than " << Max_Traj_Length << " exists.." << endl;
					exit(0);
				}
				
      			if(CoordAreEqual(closeList[closeList.size()-1].selfPos, end))
      			{
					break;		
      			}
    		}

			SetCoordTo(&currpos, closeList[closeList.size() - 1].selfPos);
    		timestep = closeList[closeList.size()-1].timestep;
	
    		//cout << currpos.x << " " << currpos.y << " " << timestep << endl;	
    		for(count1 = 0; count1 < primitives.size(); count1++)
    		{
      			if ((closeList[closeList.size()-1].q_f).velocity == (primitives[count1].get_q_i()).velocity)
      			{
        			WS_Coord pos_f = primitives[count1].get_pos_f();
        			RobotPosition_Vector swath = primitives[count1].get_swath();
        			float cost = primitives[count1].get_cost();
        
        			nextpos.x = currpos.x + pos_f.x;
        			nextpos.y = currpos.y + pos_f.y;
					nextpos.z = currpos.z + pos_f.z;
					blockedKey = false;

        			//cout << nextpos.x << " " << nextpos.y << endl;	
        			//if( nextpos.x == currpos.x && nextpos.y == currpos.y) continue;
					if (nextpos.x < 0 || nextpos.x >= dimension.x_dim || nextpos.y < 0 || nextpos.y >= dimension.y_dim || nextpos.z < 0 || nextpos.z >= dimension.z_dim) continue;
        
        			for(count2 = 0; count2 < swath.size(); count2++)
        			{
						tmppos.x = currpos.x + swath[count2].x;
						tmppos.y = currpos.y + swath[count2].y;
						tmppos.z = currpos.z + swath[count2].z;
						blockedKey = isBlocked(tmppos, timestep, obsmap, avoidTrajs);
						if (blockedKey) break;
					}				
        			if (blockedKey) continue;

        			// Is the new node present in the openlist?
        			key = false;
        			for(count3 = 0; count3 < openList.size(); count3++)
        			{
						if (openList[count3].selfPos.x == nextpos.x && openList[count3].selfPos.y == nextpos.y && openList[count3].selfPos.z == nextpos.z && openList[count3].timestep == timestep + 1)
						{
							g = closeList[closeList.size() - 1].G + cost + timestep + 1;
							if (g < openList[count3].G)
							{
								openList[count3].G = g;
								openList[count3].F = openList[count3].G + openList[count3].H;
								openList[count3].parentPos.x = currpos.x;
								openList[count3].parentPos.y = currpos.y;
								openList[count3].parentPos.z = currpos.z;
								openList[count3].primID = count1 + 1;
								openList[count3].timestep = timestep + 1;
							}
							key = true;
							break;
						}
        			}
        			if(key) continue;

					// Is the new node present in the closeList?
					key = false;
					for (count3 = 0; count3 < closeList.size(); count3++)
					{
						if (closeList[count3].selfPos.x == nextpos.x && closeList[count3].selfPos.y == nextpos.y && closeList[count3].selfPos.z == nextpos.z && closeList[count3].timestep == timestep + 1)
						{
							key = true;
							break;
						}
					}
					if (key) continue;

					// Add node to the OpenList
					g = closeList[closeList.size() - 1].G + cost + timestep + 1;
					h = Get_H(nextpos, end);
					f = g + h;
					openList.push_back(NodeCreate(g, h, f, currpos, nextpos, count1 + 1, primitives[count1].get_q_f(), timestep + 1));
      			}
    		}
  	}

  	path = ExtractPath(end, closeList);
  	return path;
}


//void CAstar::printTrajectory(dimension_t dimension, int **map, position start, position end, vector< pair<int, int > > path)
void CAstar::printTrajectory(int ***map,  RobotPosition_Vector path)
{
	int count1, count2, count3;

	cout << "Path Size = " << path.size() << endl;
	for (count1 = 0; count1 < path.size(); count1++)
	{
		map[path[count1].x][path[count1].y][path[count1].z] = 2;
	}

	/* exporting robot path on file */
	ofstream ofp;
	ofp.open("plan_output");

	for (count3 = 0; count3 < dimension.z_dim; count3++)
	{
		ofp << "z = " << count3 << endl;
		for (count2 = 0; count2 < dimension.y_dim; count2++)
		{
			for (count1 = 0; count1 < dimension.x_dim; count1++)
			{
				if (map[count1][count2][count3] == 0)
					ofp << "  ";
				else if (map[count1][count2][count3] == 1)
					ofp << "$ ";
				else if (count1 == start.x && count2 == start.y && count3 == start.z)
					ofp << "S ";
				else if (count1 == end.x && count2 == end.y && count3 == end.z)
					ofp << "G ";
				else if (map[count1][count2][count3] == 2)
					ofp << "* ";
			}
			ofp << endl;
		}
		ofp << endl << endl;
	}
	ofp.close();
}
