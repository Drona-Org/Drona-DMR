//////////////////////////////////////////////////////////////////////
// Astar.cpp: implementation of the CAstar class.
//////////////////////////////////////////////////////////////////////

#include "astar.h"


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
    for(count = 0; count < dimension.length_x; count++)
      delete[] obsmap[count];
    delete[] obsmap;
    obsmap = NULL;
  }
}


void CAstar::SetSEpoint(RobotPosition start, RobotPosition end)
{
  this->start = start;
  this->end = end;
}


void CAstar::SetPrimitive(MotionPrimitive_Vector primitives)
{
  this->primitives = primitives;
}


void CAstar::SetDimension(Dimension dimension)
{
  this->dimension = dimension;
}


void CAstar::SetObstacleMap(Dimension dimension, RobotPosition_Vector obstacles)
{
  unsigned int count, count1, count2;

  obsmap = new int*[dimension.length_x];
  
  for(count = 0; count < dimension.length_x ; count++)
  {
    obsmap[count] = new int[dimension.length_y];
  }

  for (count1 = 0; count1 < dimension.length_x; count1++)
  {
    for (count2 = 0; count2 < dimension.length_y; count2++)
    {
      obsmap[count1][count2] = 0;
    }
  }

  for (count = 0; count < obstacles.size(); count++)
  {
    obsmap[obstacles[count].x][obstacles[count].y] = 1;
  }
}


void CAstar::SetAvoidPositions(Dimension dimension, AvoidPositions* avoidPositions, int avoidSize)
{
  unsigned int count1, count2;
  int x, y;
  RobotPosition tmppos;

  cout << "Setting Avoid Trajectories" << endl;
  cout << avoidSize << endl;
  for (count1 = 0; count1 < avoidSize; count1++)
  {
    for (count2 = 0; count2 < avoidPositions[count1].size; count2++)
    {
      FindLocation(dimension, (avoidPositions[count1].PositionsOccupied)[count2], x, y);
      cout << "x= " << x << " " << "y = " << y << endl;
      tmppos.x = x; tmppos.y = y;
      avoidTrajs.resize(count2 + 1);
      avoidTrajs[count2].push_back(tmppos);
    }
  }
}


void CAstar::PrintAvoidPositions()
{
  unsigned int count1, count2;
  
  for (count1 = 0; count1 < avoidTrajs.size(); count1++)
  {
    cout << "Time " << count1 << endl;
    for (count2 = 0; count2 < avoidTrajs[count1].size(); count2++)
    {
      cout << (avoidTrajs[count1][count2]).x << " " << (avoidTrajs[count1][count2]).y << endl;
    }
    cout << endl;
  }
}


int **CAstar::GetObstacleMap()
{
  return obsmap;
}


node CAstar::NodeCreate(double g, double h, double f, RobotPosition p, RobotPosition m, int primid, RobotState q_f, int timestep)
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


double CAstar::Get_H (RobotPosition current, RobotPosition end)
{
  int cost_hX = abs(end.x - current.x);
  int cost_hY = abs(end.y - current.y);
  double cost_h = cost_hX + cost_hY;
  return cost_h;
}


//vector< pair<int, int> > CAstar::ExtractPath(int Ex, int Ey, vector<node> closeList)
RobotPosition_Vector CAstar::ExtractPath(RobotPosition end, vector<node> closeList)
{
  unsigned int count1, count2, count3;
  RobotPosition F;
  RobotPosition tmppos;

  printf("Astar node path building..\n");
  F.x = end.x;
  F.y = end.y;

  int index=0;
  nodePath tempPath;
  tempPath.index = index++;
  tempPath.pos = end;
  tempPath.primID = 0;
  gFindPath.push_back(tempPath);
  while(1)
  {
    for(count3 = 0; count3 < closeList.size(); count3++)
    {
      if( (closeList[count3].selfPos.x==F.x) && (closeList[count3].selfPos.y==F.y))
      {
        F.x = closeList[count3].parentPos.x;
        F.y = closeList[count3].parentPos.y;
        tempPath.index=index++;
        tempPath.pos = F;
        tempPath.primID = closeList[count3].primID;
        gFindPath.push_back(tempPath);
        break;
      }
    }
    if(F.x == start.x && F.y == start.y) break;
  }

  printf("Path building done..\n");

  sort(gFindPath.begin(), gFindPath.end(),compare2);
  //cout << "11111111" << endl;
  for(count1 = 0; count1 < gFindPath.size(); count1++)
  {
    tmppos.x = gFindPath[count1].pos.x;
    tmppos.y = gFindPath[count1].pos.y;
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
  printf("Path contruction done..\n");
  return path;
}


RobotPosition_Vector CAstar::FindCollisionFreePath()
{
  int count1, count2, count3;
  MotionPrimitive_Vector tempPrimF;
  RobotPosition currpos, nextpos;
  RobotPosition tmppos;
  double g,h,f;
  RobotState q;
  int timestep;
  int swathKey, collisionKey;

  printf("In Astar algorithm path function..\n");
  while(1)
  {	
    if(closeList.size()==0)
    {	
      g = 0;
      h = Get_H(start, end);
      f = g+h;
      q.velocity = 0;
      tmppos.x = 0; tmppos.y = 0;
      closeList.push_back(NodeCreate(g,h,f,tmppos, start, 0, q, 0));
    }
    else
    {
      if(openList.size() == 0 )
      {
        printf("These motion primitives are not applicable for this problem..\n");
	exit(0);	
      }
      //OpenList
      sort(openList.begin(), openList.end(),compare);
      closeList.push_back( openList[0] );
      openList.erase(openList.begin());
			
      if(closeList[closeList.size()-1].selfPos.x == end.x && closeList[closeList.size()-1].selfPos.y == end.y)
      {
        printf("Goal Reached..\n");
	break;		
      }
    }

    currpos.x = closeList[closeList.size()-1].selfPos.x;
    currpos.y = closeList[closeList.size()-1].selfPos.y;		
    timestep = closeList[closeList.size()-1].timestep;
	
    cout << currpos.x << " " << currpos.y << " " << timestep << endl;	
    for(count1 = 0; count1 < primitives.size(); count1++)
    {
      if ((closeList[closeList.size()-1].q_f).velocity == (primitives[count1].get_q_i()).velocity)
      {
        RobotPosition pos_f = primitives[count1].get_pos_f();
        RobotPosition_Vector swath = primitives[count1].get_swath();
        float cost = primitives[count1].get_cost();
        
        nextpos.x = currpos.x + pos_f.x;
        nextpos.y = currpos.y + pos_f.y;
        swathKey = 0;
        collisionKey = 0;

        cout << nextpos.x << " " << nextpos.y << endl;	
        if( nextpos.x == currpos.x && nextpos.y == currpos.y) continue;
        if( nextpos.x < 0 || nextpos.x >= dimension.length_x || nextpos.y < 0 || nextpos.y >= dimension.length_y) continue;				
        
        cout << "2222222222" << endl;     
        for(count2 = 0; count2 < swath.size(); count2++)
        {
          // Static Obstacles
          if( obsmap[currpos.x + swath[count2].x][currpos.y + swath[count2].y] == 1 )
	  {
	    swathKey = 1;
            break;
	  }
    	  cout << "444444444" << endl;
          // Other Robots
          for (count3 = 0; count3 < avoidTrajs[timestep].size(); count3++)
          {
            if (currpos.x + swath[count2].x == avoidTrajs[timestep][count3].x && currpos.y + swath[count2].y == avoidTrajs[timestep][count3].y)
            {
	      collisionKey = 1;
              break;
            }
          }
          if (collisionKey) break;
        }				
 
        cout << "33333333333" << endl;
        if(swathKey || collisionKey) continue;

        // Is the new node present in the openlist?
        int key=0;
        for(count3 = 0; count3 < openList.size(); count3++)
        {
          if(openList[count3].selfPos.x == nextpos.x && openList[count3].selfPos.y == nextpos.y)
	  {
	    g = cost + closeList[closeList.size()-1].G;
	    if(g < openList[count3].G)
	    {
	      openList[count3].G = g;
	      openList[count3].F = openList[count3].G+openList[count3].H;
	      openList[count3].parentPos.x = currpos.x;
	      openList[count3].parentPos.y = currpos.y;
	      openList[count3].primID = count1 + 1;
	      openList[count3].timestep = timestep + 1;
            }
	    key=1;
	    break;
          }
        }
      
        if(key) continue;

        // Is the new node present in the closeList?
        key=0;
        for(count3 = 0; count3 < closeList.size(); count3++)
        {
	  if(closeList[count3].selfPos.x == nextpos.x && closeList[count3].selfPos.y == nextpos.y)
          {
	    key=1;
	    break;
          }
        }
        if(key) continue;

        // Add node to the OpenList
        g = cost + closeList[closeList.size()-1].G;
        tmppos.x = nextpos.x; tmppos.y = nextpos.y;
        h = Get_H(tmppos,end);
        f = g + h;
        openList.push_back(NodeCreate(g, h, f, currpos, nextpos, count1 + 1, primitives[count1].get_q_f(), timestep));
      }
    }
  }

  path = ExtractPath(end, closeList);
  return path;
}


//void CAstar::printTrajectory(dimension_t dimension, int **map, position start, position end, vector< pair<int, int > > path)
void CAstar::printTrajectory(int **map,  RobotPosition_Vector path)
{
  printf("Astar path printing on map..\n");

  int count1, count2;

  for(count1 = 0; count1 < path.size(); count1++)
  {
    map[path[count1].x][path[count1].y] = 2;
  }

  /* exporting robot path on file */
  ofstream ofp;
  ofp.open("plan_output");

  for(count1 = 0; count1 < dimension.length_x; count1++)
  {
    for(count2 = 0; count2 < dimension.length_y; count2++)
    {
      if(map[count1][count2] == 0)
        ofp << "  ";
      if(map[count1][count2] == 1)
        ofp << "$ ";
      if(count1 == start.x && count2 == start.y)
        ofp << "S ";
      if(count1 == end.x && count2 == end.y)
        ofp << "G ";
      if(map[count1][count2] == 2)
        ofp << "* ";
    }
    ofp << endl;
  }
  ofp.close();
}
