#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <quadrotor_msgs/TrajectoryData.h>
#include <math.h>

Eigen::MatrixXd A_goto(6,6);

struct TrajectoryInfo
{
    double xcoef[8];
    double ycoef[8];
    double zcoef[8];
    double duration;
};

#define num_seg 3
TrajectoryInfo trajInfo[num_seg];
TrajectoryInfo trajInfo2[num_seg];
TrajectoryInfo trajInfo3[num_seg];
TrajectoryInfo trajInfo4[num_seg];
int count;
double tscale = 1;
double t_goto = 0.5;

double cur_t, t_end = 0;

TrajectoryInfo cal_goto(double x_init, double y_init, double z_init, double x_dest, double y_dest, double z_dest)
{
	TrajectoryInfo cur_traj;
    Eigen::VectorXd bx(6),by(6), bz(6), solx(6), soly(6), solz(6);
    bx<< x_init,0.0,0.0,x_dest,0.0,0.0;
    solx = A_goto.colPivHouseholderQr().solve(bx);
    by<< y_init,0.0,0.0,y_dest,0.0,0.0;
    soly = A_goto.colPivHouseholderQr().solve(by);
    bz<< z_init,0.0,0.0,z_dest,0.0,0.0;
    solz = A_goto.colPivHouseholderQr().solve(bz);
    cur_traj.duration = t_goto;
    cur_traj.xcoef[0] = 0;
    cur_traj.xcoef[1] = 0;
    cur_traj.ycoef[0] = 0;
    cur_traj.ycoef[1] = 0;
    cur_traj.zcoef[0] = 0;
    cur_traj.zcoef[1] = 0;
    for(int i = 0; i < 6; i++){
      cur_traj.xcoef[7-i] = solx(i);
      cur_traj.ycoef[7-i] = soly(i);
      cur_traj.zcoef[7-i] = solz(i);
    }
    ROS_INFO("solve goto 1");
    return cur_traj;
}

void initialize_var()
{
A_goto << 1.0,0.0,0.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,0.0,0.0,
0.0,0.0,2.0,0.0,0.0,0.0,
1,t_goto,pow(t_goto,2),pow(t_goto,3),pow(t_goto,4),pow(t_goto,5),
0,1,2*t_goto,3*pow(t_goto,2),4*pow(t_goto,3),5*pow(t_goto,4),
0.0,0.0,2.0,6.0*t_goto,12.0*pow(t_goto,2),20.0*pow(t_goto,3);
}

double stops[4][3] = { {0.0, 0.0, 0.0}, {0.1, 0.1, 1.2}, {0.2, 0.2, 1.2}, {0.3, 0.3, 1.2}};

void init_traj(){
	for(int i=0; i<num_seg; i++) {
		trajInfo[i] = cal_goto(stops[i][0], stops[i][1], stops[i][2], stops[i+1][0], stops[i+1][1], stops[i+1][2]);
	}
    count = 0;
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
