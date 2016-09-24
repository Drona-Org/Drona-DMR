#include "PathSearchNode.h"

bool PathSearchNode::IsSameState( PathSearchNode &rhs , void* context)
{
  return CoordAreEqual(coord, rhs.coord) && timestamp == rhs.timestamp;
}

float PathSearchNode::GoalDistanceEstimate( PathSearchNode &nodeGoal , void* context)
{
  int cost_hX = abs(coord.x - nodeGoal.coord.x);
  int cost_hY = abs(coord.y - nodeGoal.coord.y);
  int cost_hZ = abs(coord.z - nodeGoal.coord.z);
  float cost_h = cost_hX + cost_hY + cost_hZ;
  return cost_h;
}

bool PathSearchNode::IsGoal( PathSearchNode &nodeGoal , void* context)
{
  return CoordAreEqual(coord, nodeGoal.coord);
}

bool isBlocked(WS_Coord pos, int timestep, int ***obsmap, vector <RobotPosition_Vector> avoidTrajs)
{
  int count1, count2;
  bool collisionKey = false;  

  // Static Obstacles
  if (obsmap[pos.x][pos.y][pos.z] == 1 )
    {
      return true;
    }
  if (avoidTrajs.size() == 0)
    return false;

  // Other Robots
    for (count1 = -Delta; count1 <= Delta; count1++)
    {
      for (count2 = 0; count2 < avoidTrajs.size(); count2++)
      {
        if (timestep + count1 >=0 && timestep + count1 < avoidTrajs[count2].size())
        {
        if (CoordAreEqual(pos, avoidTrajs[count2][timestep + count1]))
            {
              collisionKey = true;
              break;
            }
        }
    }

      // The final positions of the other robots should not interfere with the trajectory
      // of the current robot
      if (timestep + count1 > avoidTrajs[0].size())
      {
          for (count2 = 0; count2 < avoidTrajs.size(); count2++)
          {
              if (CoordAreEqual(pos, avoidTrajs[count2][avoidTrajs[0].size() - 1]))
              {
                collisionKey = true;
                break;
            }
        }
        if (collisionKey) 
        break;
      }
  }
  return collisionKey;
}

bool PathSearchNode::GetSuccessors( AStarSearch<PathSearchNode> *astarsearch, PathSearchNode *parent_node, void* _context) 
{
  CAstar* context = (CAstar*)_context;
  #define add_if_not_blocked(side, step) {                                                          \
    WS_Coord neighbor = coord;                                                                      \
    neighbor.side += (step);                                                                        \
    if(neighbor.side >= 0 && neighbor.side < context->GetDimension().side##_dim &&                  \
      !isBlocked(neighbor, timestamp + 1, context->GetObstacleMap(), context->GetAvoidTrajs())) {   \
      PathSearchNode newNode(neighbor, timestamp + 1);                                              \
      astarsearch->AddSuccessor(newNode);                                                           \
    }                                                                                               \
  }

  add_if_not_blocked(x, -1);
  add_if_not_blocked(x, +1);
  add_if_not_blocked(y, -1);
  add_if_not_blocked(y, +1);
  add_if_not_blocked(z, -1);
  add_if_not_blocked(z, +1);

  return true;
}

float PathSearchNode::GetCost( PathSearchNode &successor , void* context)
{
  return 1.0;
}

void PathSearchNode::PrintNodeInfo()
{
  printf("(%d, %d %d)@t=%d\n", coord.x, coord.y, coord.z, timestamp);
}