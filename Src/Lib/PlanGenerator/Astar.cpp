//////////////////////////////////////////////////////////////////////
// Astar.cpp: implementation of the CAstar class.
//////////////////////////////////////////////////////////////////////


#include "Astar.h"
#include "PathSearchNode.h"
#include "stlastar.h"

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

void CAstar::SetDimension(WS_Dimension dimension)
{
  	this->dimension = dimension;
}

WS_Dimension CAstar::GetDimension()
{
    return this->dimension;
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

int ***CAstar::GetObstacleMap()
{
    return obsmap;
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
		if (count1 > 0 && avoidTrajs[count1-1].size() < avoidPositions[count1].size)
   		{
			original_size = avoidTrajs[count1-1].size();
			for (count2 = 0; count2 <= count1 - 1; count2++)
			{
			        tmp_pos = (avoidTrajs[count2])[original_size -1];
				for (count3 = original_size + 1; count3 <= avoidPositions[count1].size; count3++)
				{
					avoidTrajs[count2].push_back(tmp_pos);
				}
			}
		}

		// Add the positions in the current trajectories to avoidTrajs
    		for (count2 = 0; count2 < avoidPositions[count1].size; count2++)
    		{
			WS_Coord coord;
      			coord = ExtractCoordFromGridLocation(avoidPositions[count1].PositionsOccupied[count2], dimension);
			SetCoordTo(&tmp_pos, coord);
      			avoidTrajs.resize(count1 + 1);
      			avoidTrajs[count1].push_back(tmp_pos);
    		}

		// If the current trajectory size is less than the size of avoidTrajs,
		// extend the current trajectory upto the length of avoidTrajs by 
		// repeating the final position of the current trajectory
		if (count1 > 0 && avoidPositions[count1].size < avoidTrajs[count1-1].size())
		{
			for (count2 = avoidPositions[count1].size; count2 < avoidTrajs[count1-1].size(); count2++)
			{
				avoidTrajs[count1].push_back(tmp_pos);
			}
		}
  	}
}

vector <RobotPosition_Vector> CAstar::GetAvoidTrajs()
{
  return avoidTrajs;
}


void CAstar::PrintAvoidPositions()
{
	unsigned int count1, count2;
	cout << "Avoids Trajectories:" << endl;
	for (count1 = 0; count1 < avoidTrajs.size(); count1++)
	{
		cout << "Robot : " << count1 << endl;
		for (count2 = 0; count2 < avoidTrajs[count1].size(); count2++)
		{
			cout << ConvertCoordToGridLocation(avoidTrajs[count1][count2], dimension) << " ";
		}
		cout << endl;
	}
}

RobotPosition_Vector CAstar::FindCollisionFreePath()
{
    RobotPosition_Vector ret;

    AStarSearch<PathSearchNode> astarsearch(1000000, this);
    
    PathSearchNode nodeStart(this->start, 0);
    PathSearchNode nodeEnd(this->end, this->dimension.x_dim * this->dimension.y_dim * this->dimension.z_dim);

    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

    unsigned int SearchState;
    unsigned int SearchSteps = 0;

    do
    {
      SearchState = astarsearch.SearchStep();
      SearchSteps++;
    }
    while( SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_SEARCHING );

    if( SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_SUCCEEDED )
    {
      for(PathSearchNode *node = astarsearch.GetSolutionStart(); node != NULL; node = astarsearch.GetSolutionNext())
      {
        ret.push_back(node->coord);
      }
      astarsearch.FreeSolutionNodes();
    }
    else if( SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_FAILED ) 
    {
      printf("Failed to search!\n");
      assert(false);
    }
    else if( SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_OUT_OF_MEMORY ) 
    {
      cout << "Search terminated. Out of memory\n";    
    }


    astarsearch.EnsureMemoryFreed();
    return ret;
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
