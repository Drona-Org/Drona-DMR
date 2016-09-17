#include <ros/ros.h>
// #include "swarm_handler.h"
#include "quad_handler.h"

using namespace std;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "swarm_primitive");

  ros::NodeHandle nh("~");

  string template_file;
  // nh.param<std::string>("swarm_template", template_file, "/home/tee/ros_ws/sandbox/primitive_handler/datas/sw_tem.yaml");
  nh.param<std::string>("quad_template", template_file, "/home/tee/ros_ws/sandbox/primitive_handler/datas/quad_tem.yaml");
  MotionTemplate prims;
  // SwarmHandler primhandler;
  QuadHandler primhandler;
  if(!primhandler.ReadMotionTemplate(template_file, prims)){
    ROS_INFO("Can't Read Motion Template");
    return 0;
  }
  // ros::spinonce();
  return 0;
}
