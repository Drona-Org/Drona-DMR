#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <quadrotor_msgs/TrajectoryData.h>
#include <math.h>
#include "goto_solver.h"

#define num_seg 3
TrajectoryInfo trajInfo[num_seg];
TrajectoryInfo trajInfo2[num_seg];
TrajectoryInfo trajInfo3[num_seg];
TrajectoryInfo trajInfo4[num_seg];
int count;
double tscale = 1;

double cur_t, t_end = 0;

double stops[4][3] = { {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.2, 0.6, 0}, {0.2, 0.2, 0}};

void init_traj(){
	for(int i=0; i<num_seg; i++) {
		trajInfo[i] = cal_goto(stops[i][0], stops[i][1], stops[i][2], stops[i+1][0], stops[i+1][1], stops[i+1][2]);
	}
    count = 0;
}

void initialize_var()
{
    set_t_goto(6);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"gen_trajectory");
    initialize_var();
    init_traj();
    ros::NodeHandle nh("~");
    ros::Publisher pub = nh.advertise<quadrotor_msgs::TrajectoryData>("trajectoryinfo", 10, true);
    ros::Publisher pub2 = nh.advertise<quadrotor_msgs::TrajectoryData>("trajectoryinfo2", 10, true);
    ros::Publisher pub3 = nh.advertise<quadrotor_msgs::TrajectoryData>("trajectoryinfo3", 10, true);
    ros::Publisher pub4 = nh.advertise<quadrotor_msgs::TrajectoryData>("trajectoryinfo4", 10, true);
    ros::Rate loop_rate(200);
    quadrotor_msgs::TrajectoryData seg;
    quadrotor_msgs::TrajectoryData seg2;
    quadrotor_msgs::TrajectoryData seg3;
    quadrotor_msgs::TrajectoryData seg4;
    double t_start = 0;
    double t_end = 0;
    TrajectoryInfo cur_traj,cur_traj2,cur_traj3,cur_traj4;
    ROS_INFO("Before getchar");
    char c = getchar();
    ROS_INFO("Start sending trajectory");
    ros::spinOnce();
    cur_traj = trajInfo[count];
    cur_traj2 = trajInfo2[count]; 
    cur_traj3 = trajInfo3[count]; 
    cur_traj4 = trajInfo4[count]; 
    cur_t = ros::Time::now().toSec();
    t_end = cur_t + cur_traj.duration*tscale;
    for(int i = 0; i<8 ; i++){
	seg.xcoef[i] = cur_traj.xcoef[i];
	seg.ycoef[i] = cur_traj.ycoef[i];
	seg.zcoef[i] = cur_traj.zcoef[i];
	seg2.xcoef[i] = cur_traj2.xcoef[i];
	seg2.ycoef[i] = cur_traj2.ycoef[i];
	seg2.zcoef[i] = cur_traj2.zcoef[i];
	seg3.xcoef[i] = cur_traj3.xcoef[i];
	seg3.ycoef[i] = cur_traj3.ycoef[i];
	seg3.zcoef[i] = cur_traj3.zcoef[i];
	seg4.xcoef[i] = cur_traj4.xcoef[i];
	seg4.ycoef[i] = cur_traj4.ycoef[i];
	seg4.zcoef[i] = cur_traj4.zcoef[i];
    }
    seg.duration = cur_traj.duration;
    seg2.duration = cur_traj2.duration;
    seg3.duration = cur_traj3.duration;
    seg4.duration = cur_traj4.duration;
    pub.publish(seg);
    pub2.publish(seg2);
    pub3.publish(seg3);
    pub4.publish(seg4);
    ROS_INFO("seg publish: dur %f", seg.duration);
    while(count < num_seg){
        cur_t = ros::Time::now().toSec();
        ros::spinOnce();
        loop_rate.sleep();
    	if(cur_t >= t_end){
    	    count = count+1;
    	    if(count < num_seg){
            	cur_traj = trajInfo[count]; 
            	cur_traj2 = trajInfo2[count]; 
            	cur_traj3 = trajInfo3[count]; 
            	cur_traj4 = trajInfo4[count]; 
     		t_end = cur_t + cur_traj.duration*tscale;
    		for(int i = 0; i<8 ; i++){
    		    seg.xcoef[i] = cur_traj.xcoef[i];
    		    seg.ycoef[i] = cur_traj.ycoef[i];
    		    seg.zcoef[i] = cur_traj.zcoef[i];
    		    seg2.xcoef[i] = cur_traj2.xcoef[i];
    		    seg2.ycoef[i] = cur_traj2.ycoef[i];
    		    seg2.zcoef[i] = cur_traj2.zcoef[i];
    		    seg3.xcoef[i] = cur_traj3.xcoef[i];
    		    seg3.ycoef[i] = cur_traj3.ycoef[i];
    		    seg3.zcoef[i] = cur_traj3.zcoef[i];
    		    seg4.xcoef[i] = cur_traj4.xcoef[i];
    		    seg4.ycoef[i] = cur_traj4.ycoef[i];
    		    seg4.zcoef[i] = cur_traj4.zcoef[i];
    		}
    		seg.duration = cur_traj.duration;
    		seg2.duration = cur_traj2.duration;
    		seg3.duration = cur_traj3.duration;
    		seg4.duration = cur_traj4.duration;
 	        pub.publish(seg);
 	        pub2.publish(seg2);
 	        pub3.publish(seg3);
 	        pub4.publish(seg4);
        	ROS_INFO("seg publish: dur %f", seg.duration);
      	    }
	   }
    }
    sleep(50);
    return 0;
}
