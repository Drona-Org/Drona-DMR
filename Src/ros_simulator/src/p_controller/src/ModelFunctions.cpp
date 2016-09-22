#include <map>
#include <sstream>
#include "Workspace.h"
#include "PrtUser.h"
#include "PrtExecution.h"
#include "goto_solver.h"
#include <Eigen/Dense>
#include <quadrotor_msgs/TrajectoryData.h>
#include <ros/ros.h>
#include "InitRos.h"
#include "Compat.h"

using namespace std;

extern "C" {
PRT_VALUE *P_FUN_RosInit_IMPL(PRT_MACHINEINST *context);
PRT_VALUE *P_FUN_StartExecutingPath_IMPL(PRT_MACHINEINST *context);
}

std::map<int, ros::Publisher> publishers;

double t_goto = 3;

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
    channel_name << "trajectoryinfo" << robot_id;
    ros::Publisher pub = node_handle->advertise<quadrotor_msgs::TrajectoryData>(channel_name.str(), 10, true);
    publishers[robot_id] = pub;
    SleepMs(1000); // Wait for publisher to register...
    printf("Registered robot %d at channel ", robot_id);
    std::cout << channel_name.str() << std::endl;
    //remm to free the frame
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
}

static Eigen::Vector3i ReadVectorCoord(PRT_VALUE* trajSeq, PRT_UINT32 i)
{
    int loc = (int)PrtPrimGetInt(PrtSeqGetNCIntIndex(trajSeq, i));
    WS_Coord coord = ExtractCoordFromGridLocation(loc, WORKSPACE_INFO->dimension);
    return Eigen::Vector3i(coord.x, coord.y, coord.z);
}

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
    int robot_id = (int)PrtPrimGetInt(p_tmp_frame.locals[1]);
    PRT_UINT32 count = PrtSeqSizeOf(trajSeq);
    if(count >= 2) {
        Eigen::Vector3i diff;
        PRT_UINT32 i = 1;
        Eigen::Vector3i current_step = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
        bool done = false;
        while(!done) {
            int step_count = 0;
            Eigen::Vector3i start_coord = ReadVectorCoord(trajSeq, i - 1);
            do {
                i++;
                step_count++;
                if(i == count) {
                    done = true;
                    break;
                }
                diff = ReadVectorCoord(trajSeq, i) - ReadVectorCoord(trajSeq, i - 1);
            } while (diff == current_step);
            Eigen::Vector3i straight_step = current_step * step_count;
            current_step = diff;
            printf("robot %d move in (%d, %d, %d)\n", robot_id, straight_step[0], straight_step[1], straight_step[2]);
            Eigen::Vector3i end_coord = straight_step + start_coord;
            Eigen::Vector3d start = start_coord.cast<double>() * 0.8;
            Eigen::Vector3d end = end_coord.cast<double>() * 0.8;
            TrajectoryInfo traj = cal_goto_with_t(start[0], start[1], start[2], end[0], end[1], end[2], t_goto * step_count);
            quadrotor_msgs::TrajectoryData seg;
            for(int j = 0; j < 8; j++) {
                seg.xcoef[j] = traj.xcoef[j];
                seg.ycoef[j] = traj.ycoef[j];
                seg.zcoef[j] = traj.zcoef[j];
            }
            seg.duration = traj.duration;
            publishers.at(robot_id).publish(seg);
            ros::Duration(t_goto * step_count + 3).sleep();
        }
    }
    //remm to free the frame
    PrtFreeLocals(p_tmp_mach_priv, &p_tmp_frame);
    return p_tmp_ret;
}
#endif