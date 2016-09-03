#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "ros/ros.h"
#include <std_msgs/Int8.h>
#include <path_planner/State.h>
#include <quadrotor_msgs/TrajectoryData.h>
#include <path_planner/PathPackage.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>

using namespace std;

vector<quadrotor_msgs::TrajectoryData> cur_path;
ros::Publisher t_pub;
double tscale = 1, start_t = -1;

nav_msgs::Path path_set;
int counting = 0;


void updatePath(const path_planner::PathPackage::ConstPtr & msg)
{
    cur_path.clear();
    cur_path = msg->path;
    counting = 0;
    start_t = -1;
    path_set.poses.clear();

}

double cal_pos(boost::array<double, 8> c,double t)
{
    return c[0]*pow(t,7.0) +c[1]*pow(t,6.0) + c[2]*pow(t,5.0) + c[3]*pow(t,4.0) + c[4]*pow(t,3.0) + c[5]*pow(t,2.0) + c[6]*t + c[7];
}

int main(int argc, char **argv)
{
    double t_end = 0, cur_t;

    ros::init(argc, argv, "path_publisher");
    ros::NodeHandle nh("~");
    t_pub = nh.advertise<quadrotor_msgs::TrajectoryData>("trajectoryinfo", 10, true);
//    ros::Publisher state_pub = nh.advertise<planner::State>("cur_state",10,true);
    ros::Subscriber path_sub = nh.subscribe("pathpackage", 10,updatePath, ros::TransportHints().tcpNoDelay());
    ros::Publisher pub_path = nh.advertise<nav_msgs::Path>("path", 10, true);

    ros::Rate loop_rate(100);
    path_set.header.frame_id = "/simulator";

    double  init_pos[3];
    nh.param("time/scale", tscale, 1.0);
    nh.param("init_pos/x", init_pos[0], 0.0);
    nh.param("init_pos/y", init_pos[1], 0.0);
    nh.param("init_pos/z", init_pos[2], 0.0);
    quadrotor_msgs::TrajectoryData cur_seg, cal_seg;
    double cur_off[3];
    bool init_b = false;
    while(nh.ok())
    {
    	ros::spinOnce();
        loop_rate.sleep();
        cur_t = ros::Time::now().toSec();
    	if((cur_t >= t_end) && (cur_path.size() > 0)){    	    
            if(start_t >0){
                geometry_msgs::PoseStamped p;
                double tt = (cur_t-start_t)/tscale;
                p.pose.position.x = cal_pos(cal_seg.xcoef,tt);
                p.pose.position.y = cal_pos(cal_seg.ycoef,tt);
                p.pose.position.z = cal_pos(cal_seg.zcoef,tt);
                cur_off[0] = p.pose.position.x;
                cur_off[1] = p.pose.position.y;
                cur_off[2] = p.pose.position.z;
                p.pose.orientation.x = 0;
                p.pose.orientation.y = 0;
                p.pose.orientation.z = 0;
                p.pose.orientation.w = 1;
                path_set.poses.push_back(p);
            }
            cur_seg = cur_path.front();
            cal_seg = cur_seg;
    	    cur_path.erase(cur_path.begin());
            start_t = cur_t;
        	t_end = cur_t + cur_seg.duration*tscale;
    	    t_pub.publish(cur_seg);
    	    // state_pub.publish(cur_seg.q_f);
            ROS_INFO("seg publish: dur %f", cur_seg.duration*tscale);
            if(init_b){
                cal_seg.xcoef[7] = cur_off[0];
                cal_seg.ycoef[7] = cur_off[1];
                cal_seg.zcoef[7] = cur_off[2];
            }
            else{
                cal_seg.xcoef[7] += init_pos[0];
                cal_seg.ycoef[7] += init_pos[1];
                cal_seg.zcoef[7] += init_pos[2];
                init_b = true;
            }
    	}
        if(counting % 10 == 0 && init_b && (cur_t <= t_end))
        {
            geometry_msgs::PoseStamped p;
            double tt = (cur_t-start_t)/tscale;
            p.pose.position.x = cal_pos(cal_seg.xcoef,tt);
            p.pose.position.y = cal_pos(cal_seg.ycoef,tt);
            p.pose.position.z = cal_pos(cal_seg.zcoef,tt);
            cur_off[0] = p.pose.position.x;
            cur_off[1] = p.pose.position.y;
            cur_off[2] = p.pose.position.z;
            p.pose.orientation.x = 0;
            p.pose.orientation.y = 0;
            p.pose.orientation.z = 0;
            p.pose.orientation.w = 1;
            path_set.poses.push_back(p);

            pub_path.publish(path_set);
        }
        counting++;
    }
    return 0;
}
