#include <ros/ros.h>

#include "InitRos.h"
#include "goto_solver.h"

ros::NodeHandle *node_handle;

void init_ros(const char* program_name, int *argc, char *argv[]) {
    ros::init(*argc, argv, program_name);
    node_handle = new ros::NodeHandle("~");
    set_t_goto(1);
}