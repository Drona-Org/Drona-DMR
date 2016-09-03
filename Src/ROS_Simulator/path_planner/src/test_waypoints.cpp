#include <iostream>
#include "ros/ros.h"
#include <path_planner/State.h>

using namespace std;



int main(int argc, char **argv)
{
    ros::init(argc, argv, "testwaypoints");
    ros::NodeHandle nh("~");
    path_planner::State q_f;

    ros::Publisher waypoints_pub = nh.advertise<path_planner::State>("waypoints", 10, true);
    q_f.x = 45;
    q_f.y = 45;
    q_f.z = 10;
    q_f.v = 0;
    waypoints_pub.publish(q_f);
    sleep(10);
    q_f.x = 50;
    q_f.y = 50;
    q_f.z = 10;
    waypoints_pub.publish(q_f);
    ros::spin();
}
