#include <ros/ros.h>
#include "sbpl/headers.h"
#include "environment_swarm.h"
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>

#define THRESHOLD 150
using namespace std;
EnvCostMap costmap;
const static double wall_color_r = 1, wall_color_g = 0, wall_color_b = 0, wall_color_a = 0.15;
double res;
int off_map[3];
std::vector<geometry_msgs::Point32> obs;

void generate_obstable_list()
{
  size_t sizex = costmap.get_size(0);
  size_t sizey = costmap.get_size(1);
  size_t sizez = costmap.get_size(2);
  int offx = costmap.get_offset(0);
  int offy = costmap.get_offset(1);
  int offz = costmap.get_offset(2);
  int count = 0, c2 = 0;
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int k = 0; k < sizez; k++){
        EnvQuadVoxel t(i,j,k);
        c2++;
        if(costmap.get_cost(t) > THRESHOLD)
        {
          geometry_msgs::Point32 p;
          p.x = (i+offx+off_map[0])*res;
          p.y = (j+offy+off_map[1])*res;
          p.z = (k+offz+off_map[2])*res;
          obs.push_back(p);
          count++;
        }
      }
    }
  }
  ROS_INFO("%d, %d", count, c2);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "map_visualization");

  ros::NodeHandle nh("~");

  ros::Publisher pub_obs = nh.advertise<sensor_msgs::PointCloud>("obs_array", 10, true);
  string cmap_file;
  nh.param<std::string>("map/cmap", cmap_file, "/home/tee/fuerte_workspace/sandbox/planner/datas/mri2_0.2.yaml");

//  string cmap_file("/home/tee/fuerte_workspace/sandbox/planner/datas/map_random_dots3.yaml");
  if(!costmap.read_cost_map(cmap_file))
    ROS_INFO("Can't Read CostMap");
  nh.param("map/offx", off_map[0], 0);
  nh.param("map/offy", off_map[1], 0);
  nh.param("map/offz", off_map[2], 0);
  nh.param("map/res", res, 0.2);
  generate_obstable_list();
  ros::Rate r(1);
  sensor_msgs::PointCloud obs_array; 
  obs_array.header.frame_id = "/simulator";
  obs_array.points = obs;
  pub_obs.publish(obs_array);
  ros::spin();
  return 0;
}
