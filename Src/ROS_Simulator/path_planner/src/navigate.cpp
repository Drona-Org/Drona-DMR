#include <iostream>
#include <boost/foreach.hpp>
#include <string>
#include <sstream>
#include "sbpl/headers.h"
#include "environment_quad.h"
#include "ros/ros.h"
#include <path_planner/State.h>
#include <quadrotor_msgs/TrajectoryData.h>
#include <path_planner/PathPackage.h>
#include <path_planner/CostMapInfo.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>

using namespace std;


const char * debug_file = "/home/tee/ros_ws/sandbox/path_planner/datas/debug.txt";
double cur_t;
EnvironmentQuad env;
ros::Publisher path_pub,pub_swath;
double time_al = 60.0;
int status;
ARAPlanner * planner_ptr;
std::vector<geometry_msgs::Point32> swath;
int offset[3];
double res = 0.2;
EnvQuadStateCell q_i, q_f;
bool available = false;
bool fwd;

void genTrajectory(vector<int> cur_path)
{
    int path_length = cur_path.size() - 1;
    path_planner::PathPackage path_info;
    int ite = 0;
    ROS_INFO("path length = %d",path_length);
    while(ite < path_length)
    {
        EnvQuadStateCell q_f, q_current;
        env.id2state(cur_path[ite+1], q_f);
        env.id2state(cur_path[ite], q_current);
        ROS_INFO("%d %d %d %d",q_f.get(0),q_f.get(1),q_f.get(2),q_f.get(3));
        EnvQuadAction cur_action = env.GetAction(cur_path[ite],cur_path[ite+1]);
        std::vector<EnvQuadVoxel> cswath = cur_action.getSwath();
        vector<EnvQuadVoxel>::const_iterator vox_it = cswath.begin();
        for (; vox_it != cswath.end(); ++vox_it) {
            EnvQuadVoxel cur_vox = q_current + *vox_it;
            geometry_msgs::Point32 p;
            p.x = (cur_vox.get<0>() + offset[0])*res;
            p.y = (cur_vox.get<1>() + offset[1])*res;
            p.z = (cur_vox.get<2>() + offset[2])*res;
            swath.push_back(p);
        } // end for

        EnvQuadAction::EnvQuadParam coefs = cur_action.getCoeffs();
        quadrotor_msgs::TrajectoryData td;
        for(int j = 0;j < 8; j++){
            td.xcoef[j] = coefs.x_coeffs[j];
            td.ycoef[j] = coefs.y_coeffs[j];
            td.zcoef[j] = coefs.z_coeffs[j];
        }
        td.duration = coefs.time; 
 //       ROS_INFO("state: %d %d %d %d %d", q_f.get(0), q_f.get(1), q_f.get(2), q_f.get(3), q_f.get(4));
        path_info.path.push_back(td); 
        ite++;
    }
    sensor_msgs::PointCloud swath_array; 
    swath_array.header.frame_id = "/simulator";
    swath_array.points = swath;
    pub_swath.publish(swath_array);
    path_pub.publish(path_info);
    ROS_INFO("done with this trajectory");
    available = true;
    q_i = q_f;
}


void do_planning(const path_planner::State::ConstPtr & msg){
    if(available){
        // ROS_INFO("Start planning\n");
        q_f.get(0) = msg->x;    
        q_f.get(1) = msg->y;    
        q_f.get(2) = msg->z;    
        q_f.get(3) = msg->v;    
        env.set_start(q_i);
        env.set_goal(q_f);

        MDPConfig MDPCfg;
        env.InitializeMDPCfg(&MDPCfg);

        if ((*planner_ptr).set_start(MDPCfg.startstateid) == 0) {
        ROS_ERROR("ERROR: failed to set start state\n");
        throw new SBPL_Exception();
        }
        if ((*planner_ptr).set_goal(MDPCfg.goalstateid) == 0) {
        ROS_ERROR("ERROR: failed to set goal state\n");
        throw new SBPL_Exception();
        }

        ROS_INFO("start planning...\n");
        vector<int> path;

        (*planner_ptr).force_planning_from_scratch();
        bool status = (*planner_ptr).replan(time_al, &path);  // time allotted
        ROS_INFO("done planning\n");
        if (status) {
     //       env.PrintParam(path);
            available = false;
            genTrajectory(path);
        }
    }
    else{
        ROS_INFO("Quadrotor is not available");
    }
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "navigate");
    ros::NodeHandle nh("~");

    env.InitializeEnv((const char *)debug_file);
    int qi[4], qf[4];
    nh.param("start/x", qi[0], 20);
    nh.param("start/y", qi[1], 0);
    nh.param("start/z", qi[2], 22);
    nh.param("start/v", qi[3], 0);
    nh.param("forward", fwd, true);

    for(int i = 0; i<4; i++){
        q_i.get(i) = qi[i];
    }
    available = true;

    path_pub = nh.advertise<path_planner::PathPackage>("pathpackage", 10, true);
    pub_swath = nh.advertise<sensor_msgs::PointCloud>("swath", 10, true);
    ros::Subscriber goals = nh.subscribe("waypoints", 10,do_planning, ros::TransportHints().tcpNoDelay());
    time_al = 100.0;

    ARAPlanner planner(&env, fwd); // true for forward search
    planner.set_search_mode(true); // for search until first solution
    planner.set_initialsolution_eps(1.0);
    planner_ptr = &planner;

    offset[0] = env.getMapoffset(0);
    offset[1] = env.getMapoffset(1);
    offset[2] = env.getMapoffset(2);

    geometry_msgs::Point32 start_point, goal_point;
    start_point.x = (qi[0]+offset[0])*res;
    start_point.y = (qi[1]+offset[1])*res;
    start_point.z = (qi[2]+offset[2])*res;
    goal_point.x = (qf[0]+offset[0])*res;
    goal_point.y = (qf[1]+offset[1])*res;
    goal_point.z = (qf[2]+offset[2])*res;
    ros::spin();
}
