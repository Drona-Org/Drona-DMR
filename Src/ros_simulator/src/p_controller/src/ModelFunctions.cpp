#include <map>
#include <sstream>
#include "Workspace.h"
#include "PrtUser.h"
#include "PrtExecution.h"
#include "goto_solver.h"
#include <Eigen/Dense>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include "InitRos.h"
#include "Compat.h"
#include <pthread.h>

using namespace std;

extern "C" {
PRT_VALUE *P_FUN_RosInit_IMPL(PRT_MACHINEINST *context);
PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context);
}

pthread_mutex_t publishers_map_lock = PTHREAD_MUTEX_INITIALIZER;
std::map<int, ros::Publisher> publishers;

double t_goto = 0.5;
double tscale = 1.0;

#ifndef USE_EMPTY
PRT_VALUE *P_FUN_RosInit_IMPL(PRT_MACHINEINST *context)
{
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    p_tmp_params = NULL;
    //remm to pop frame
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    //create a tuple value
    int robot_id = (int)PrtPrimGetInt(p_tmp_frame.locals[0]);
    std::ostringstream channel_name;
    channel_name << "odom" << robot_id;
    ros::Publisher pub = node_handle->advertise<nav_msgs::Odometry>(channel_name.str(), 10, true);
    pthread_mutex_lock(&publishers_map_lock);
    publishers[robot_id] = pub;
    pthread_mutex_unlock(&publishers_map_lock);
    SleepMs(1000); // Wait for publisher to register...
    printf("Registered robot %d at channel ", robot_id);
    std::cout << channel_name.str() << std::endl;
    //remm to free the frame
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
}

static Eigen::Vector3d ReadVectorCoord(PRT_VALUE* trajSeq, PRT_UINT32 i)
{
    int loc = (int)PrtPrimGetInt(PrtSeqGetNCIntIndex(trajSeq, i));
    WS_Coord coord = ExtractCoordFromGridLocation(loc, WORKSPACE_INFO->dimension);
    return Eigen::Vector3d(coord.x, coord.y, coord.z);
}

static double cal_pos(double c[],double t)
{
    return c[0]*pow(t,7.0) +c[1]*pow(t,6.0) + c[2]*pow(t,5.0) + c[3]*pow(t,4.0) + c[4]*pow(t,3.0) + c[5]*pow(t,2.0) + c[6]*t + c[7];
}

static double cal_vel(double c[],double t)
{
    return (c[0]*7*pow(t,6.0) +c[1]*6*pow(t,5.0) + c[2]*5*pow(t,4.0) + c[3]*4*pow(t,3.0) + c[4]*3*pow(t,2.0) + c[5]*2*t + c[6])/tscale;
}

static double cal_acc(double c[],double t)
{
    return (c[0]*42*pow(t,5.0) +c[1]*30*pow(t,4.0) + c[2]*20*pow(t,3.0) + c[3]*12*pow(t,2.0) + c[4]*6*t + c[5]*2)/(tscale*tscale);
}

static void publish_straight_traj(int robot_id, Eigen::Vector3d start, Eigen::Vector3d end, double duration)
{
    nav_msgs::Odometry odom;
    odom.header.frame_id = "/simulator";
    odom.child_frame_id = "/quadrotor";
    
    double resolution;
    node_handle->param("/map/res", resolution, 1.0);
    start *= resolution;
    end *= resolution;
    
    ros::Rate odom_pub_duration(100);
    double t_start = ros::Time::now().toSec();
    double t_end = t_start + duration * tscale;

    Eigen::Vector3d vel = (end - start) / (duration / tscale);

    for(double cur_t = t_start; cur_t < t_end; cur_t = ros::Time::now().toSec()) {
        odom.header.stamp = ros::Time::now();

        double t = (cur_t - t_start) / tscale;
        Eigen::Vector3d loc = t * vel + start;
        odom.pose.pose.position.x = loc[0];
        odom.pose.pose.position.y = loc[1];
        odom.pose.pose.position.z = loc[2];

        odom.pose.pose.orientation.x = 0;
        odom.pose.pose.orientation.y = 0;
        odom.pose.pose.orientation.z = 0;
        odom.pose.pose.orientation.w = 0;

        odom.twist.twist.linear.x = vel[0];
        odom.twist.twist.linear.y = vel[1];
        odom.twist.twist.linear.z = vel[2];

        odom.twist.twist.angular.x = 0;
        odom.twist.twist.angular.y = 0;
        odom.twist.twist.angular.z = 0;

        publishers[robot_id].publish(odom);
        odom_pub_duration.sleep();
    }
}


static const double     _PI= 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;
static const double _TWO_PI= 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696;

static void publish_turn_traj(int robot_id, Eigen::Vector3d start, Eigen::Vector3d turning, Eigen::Vector3d end, double duration)
{
    nav_msgs::Odometry odom;
    odom.header.frame_id = "/simulator";
    odom.child_frame_id = "/quadrotor";
    
    double resolution;
    node_handle->param("/map/res", resolution, 1.0);
    start *= resolution;
    end *= resolution;
    turning *= resolution;

    Eigen::Vector3d origin = end + (start - turning);
    
    ros::Rate odom_pub_duration(100);
    double t_start = ros::Time::now().toSec();
    double t_end = t_start + duration * tscale;

    double omega = (_PI / 2) / (duration / tscale);

    for(double cur_t = t_start; cur_t < t_end; cur_t = ros::Time::now().toSec()) {
        odom.header.stamp = ros::Time::now();

        double t = (cur_t - t_start) / tscale;
        double theta = (omega * t); 
        Eigen::Vector3d loc = sin(theta) * (end - origin) + cos(theta) * (start - origin) + origin;
        odom.pose.pose.position.x = loc[0];
        odom.pose.pose.position.y = loc[1];
        odom.pose.pose.position.z = loc[2];

        odom.pose.pose.orientation.x = 0;
        odom.pose.pose.orientation.y = 0;
        odom.pose.pose.orientation.z = 0;
        odom.pose.pose.orientation.w = 0;

        odom.twist.twist.linear.x = 0;
        odom.twist.twist.linear.y = 0;
        odom.twist.twist.linear.z = 0;

        odom.twist.twist.angular.x = 0;
        odom.twist.twist.angular.y = 0;
        odom.twist.twist.angular.z = 0;

        publishers[robot_id].publish(odom);
        odom_pub_duration.sleep();
    }
}

bool time_initialized = false;
ros::Time initial_time;

PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context)
{
    PRT_MACHINEINST_PRIV *p_tmp_mach_priv = (PRT_MACHINEINST_PRIV *)context;
    PRT_VALUE *p_tmp_ret = NULL;
    PRT_FUNSTACK_INFO p_tmp_frame;
    PRT_VALUE *p_tmp_params;
    p_tmp_params = NULL;
    //remm to pop frame
    PrtPopFrame(p_tmp_mach_priv, &p_tmp_frame);
    //create a tuple value
    PRT_VALUE* trajSeq = p_tmp_frame.locals[0];
    int start_time = (int)PrtPrimGetInt(p_tmp_frame.locals[1]);
    int robot_id = (int)PrtPrimGetInt(p_tmp_frame.locals[2]);

    if(!time_initialized) {
        initial_time = ros::Time::now() - ros::Duration(t_goto * start_time);
        time_initialized = true;
    }

    ros::Time::sleepUntil(initial_time + ros::Duration(start_time * t_goto));

    PRT_UINT32 count = PrtSeqSizeOf(trajSeq);
    if(count >= 2) {
        Eigen::Vector3d diff;
        PRT_UINT32 i = 1;
        Eigen::Vector3d current_step = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
        bool done = false;
        int traj_count = 0;
        while(!done) {
            int step_count = 0;
            Eigen::Vector3d start_coord = ReadVectorCoord(trajSeq, i - 1);
            do {
                i++;
                step_count++;
                if(i == count) {
                    done = true;
                    break;
                }
                diff = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
            } while (diff == current_step);
            traj_count++;
            double duration = step_count * t_goto;
            Eigen::Vector3d straight_step = current_step * step_count;
            printf("robot %d move in (%f, %f, %f)\n", robot_id, straight_step[0], straight_step[1], straight_step[2]);
            Eigen::Vector3d end_coord = straight_step + start_coord;
            if(traj_count != 1) {
                start_coord += (current_step / 2);
                duration -= t_goto / 2;
            }
            if(i != count) {
                end_coord -= (current_step / 2);
                duration -= t_goto / 2;
            }
            if(start_coord != end_coord) {
                publish_straight_traj(robot_id, start_coord, end_coord, duration);
            } 
            if(i != count) {
                publish_turn_traj(robot_id, end_coord, end_coord + current_step / 2, end_coord + (current_step + diff) / 2, t_goto);
            }
            current_step = diff;
        }
    }
    //remm to free the frame
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
}
#endif