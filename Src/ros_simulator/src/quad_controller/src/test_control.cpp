#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <quadrotor_msgs/TRPYCommand.h>
#include <quadrotor_msgs/QuadData.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <algorithm>
#include <stdio.h>

#define USE_JOYSTICK 0

Eigen::Vector3f pos_des,vel_des,acc_des;
Eigen::Vector3f pos,vel;
Eigen::Quaternionf q;
Eigen::Vector3f acc,force_b,g;
float m = 0.084, factor = 2;
float kp_xy = 16, kd_xy = 8, ki_xy = 0.3;
float kp_z = 36, kd_z = 12, ki_z = 6, ki_yaw = 0.2;
ros::Publisher control_pub;
ros::Publisher euler_pub;
float yaw_des;
int mode = -1;
int lock1 = 0, lock2 = 0, lock3 = 0;
bool quit = false;
uint int_count = 0;
double cur_t, prev_t;
float delT;
FILE * fout;
FILE * fout2;
float x_int = 0, y_int = 0, z_int = 0, roll_int = 0, pitch_int = 0, th_int = 0, psi_int = 0, yaw_int = 0, psi_diff;
double time_st;
int iswrite = 0;

#define USE_INT 0

static const double     _PI= 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;
static const double _TWO_PI= 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696;

// Floating-point modulo
// The result (the remainder) has same sign as the divisor.
// Similar to matlab's mod(); Not similar to fmod() -   Mod(-3,4)= 1   fmod(-3,4)= -3
template<typename T>
T Mod(T x, T y)
{
//    static_assert(!std::numeric_limits<T>::is_exact , "Mod: floating-point type expected");

    if (0. == y)
        return x;

    double mm= x - y * floor(x/y);

    // handle boundary cases resulted from floating-point cut off:

    if (y > 0)              // modulo range: [0..y)
    {
        if (mm>=y)           // Mod(-1e-16             , 360.    ): m= 360.
            return 0;

        if (mm<0 )
        {
            if (y+mm == y)
                return 0  ; // just in case...
            else
                return y+mm; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14 
        }
    }
    else                    // modulo range: (y..0]
    {
        if (mm<=y)           // Mod(1e-16              , -360.   ): m= -360.
            return 0;

        if (mm>0 )
        {
            if (y+mm == y)
                return 0  ; // just in case...
            else
                return y+mm; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14 
        }
    }

    return mm;
}


void killprogram(const std_msgs::Int8::ConstPtr & msg)
{
  if(msg->data)
	quit = true;
}

void trajCallback(const quadrotor_msgs::QuadData::ConstPtr & msg)
{
    mode = msg->mode;
    if(msg->write == 1){
        iswrite = 1;
    }
    if(mode == 2){
        pos_des[0] = msg->x;
        pos_des[1] = msg->y;
        pos_des[2] = msg->z;
        vel_des[0] = msg->vx;
        vel_des[1] = msg->vy;
        vel_des[2] = msg->vz;
        acc_des[0] = msg->acc_x;
        acc_des[1] = msg->acc_y;
        acc_des[2] = msg->acc_z;
    }
    if(mode == 0){
        pos_des[2] = msg->z;
        vel_des[2] = msg->vz;
        acc_des[2] = msg->acc_z;
    }
}



void stateCallback(const nav_msgs::Odometry::ConstPtr& state)
{
    pos[0] = state->pose.pose.position.x;
    pos[1] = state->pose.pose.position.y;
    pos[2] = state->pose.pose.position.z;
    vel[0] = state->twist.twist.linear.x;
    vel[1] = state->twist.twist.linear.y;
    vel[2] = state->twist.twist.linear.z;

    q.x() = state->pose.pose.orientation.x;
    q.y() = state->pose.pose.orientation.y;
    q.z() = state->pose.pose.orientation.z;
    q.w() = state->pose.pose.orientation.w;
 
    Eigen::Matrix3f Rbw(q);
    Eigen::Vector3f euler = Rbw.eulerAngles(2,1,0);
    float roll_des = 0;
    float pitch_des = 0;

    if(mode == 0){
	lock2 = 0;
	if(lock1 == 0){
	    lock1 = 1;
	    pos_des[0] = pos[0];
	    vel_des[0] = 0;
	    acc_des[0] = 0;
	    pos_des[1] = pos[1];
	    vel_des[1] = 0;
	    acc_des[1] = 0;	
	    yaw_des = euler(0);
	}
    }
    if(mode == 1){
    	lock1 = 0;
    	if(lock2 == 0){
            iswrite = 0;
    	    lock2 = 1;
    	    vel_des[0] = 0;
    	    acc_des[0] = 0;
    	    vel_des[1] = 0;
    	    acc_des[1] = 0;	
    	    vel_des[2] = 0;
    	    acc_des[2] = 0;
    	}
    }
    if(mode == 2){
    	lock1 = 0;
    	lock2 = 0;
    	lock3 = 0;
    }
    if(mode == 3){
    	if(lock3 == 0){
            iswrite = 0;
    	    lock3 = 1;
    	    pos_des[0] = pos[0];
    	    vel_des[0] = 0;
    	    acc_des[0] = 0;
    	    pos_des[1] = pos[1];
    	    vel_des[1] = 0;
    	    acc_des[1] = 0;	
    	    pos_des[2] = pos[2];
    	    vel_des[2] = 0;
    	    acc_des[2] = 0;	
    	}
    	pos_des[2] = std::max(pos_des[2] - 0.005,-0.15);
    }

    if(USE_INT && mode > 0){
    	cur_t = ros::Time::now().toSec();
    	if(int_count == 0){
    	    pos_des[0] = pos[0];
    	    pos_des[1] = pos[1];
    	    delT = 0;
    	}
    	else{
    	    delT = (float)(cur_t - prev_t);
    	}
    	x_int = delT*(cos(euler[0])*(pos_des[0]-pos[0]) + sin(euler[0])*(pos_des[1]-pos[1]));
    	y_int = delT*(-sin(euler[0])*(pos_des[0]-pos[0]) + cos(euler[0])*(pos_des[1]-pos[1]));
    	z_int = delT*(pos_des[2]-pos[2]);

    	roll_int = roll_int - ki_xy*y_int;
    	pitch_int = pitch_int + ki_xy*x_int;
    	th_int = th_int + ki_z*z_int;
    	psi_diff = yaw_des - euler(0);
    	psi_diff = Mod(psi_diff + _PI, _TWO_PI) - _PI;
    	//ROS_INFO("yaw angle: des %f  cur %f diff: %f",yaw_des, euler(0),psi_diff);
    	psi_int = delT * psi_diff;
    	yaw_int = yaw_int + ki_yaw * psi_int;
    	yaw_int = Mod(yaw_int + _PI, _TWO_PI) - _PI;
    	prev_t = cur_t;
    	//ROS_INFO("int_terms: %f %f %f %f %f %f yaw_diff: %f %f",x_int, y_int, z_int, th_int, roll_int, pitch_int, psi_diff,yaw_int);
	    int_count++;
    }
    else{
    	th_int = 0;
    	roll_int = 0;
    	pitch_int = 0;
    	yaw_int = 0;
    }

    acc[0] = kp_xy*(pos_des[0]-pos[0])+kd_xy*(vel_des[0]-vel[0])+acc_des[0];
    acc[1] = kp_xy*(pos_des[1]-pos[1])+kd_xy*(vel_des[1]-vel[1])+acc_des[1];
    acc[2] = kp_z*(pos_des[2]-pos[2])+kd_z*(vel_des[2]-vel[2])+acc_des[2] + th_int;

    roll_des = (acc[0]*sin(euler[0])-acc[1]*cos(euler[0]))/9.81 + roll_int;
    pitch_des = (acc[0]*cos(euler[0])+acc[1]*sin(euler[0]))/9.81 + pitch_int;
  
    quadrotor_msgs::TRPYCommand command;

    if(quit || (pos_des[2] < -0.148)){
        command.thrust = 0;
        command.roll = 0;
        command.pitch = 0;
        command.yaw = 0;
    }
    else if (mode == -1){
        command.thrust = 0.01;
        command.roll = 0;
        command.pitch = 0;
        command.yaw = 0;
    }
    else{
	if(iswrite == 1){
        fprintf(fout,"Time: %f State: %f %f %f %f %f %f %f %f %f\n",ros::Time::now().toSec() - time_st, pos[0],pos[1],pos[2],vel[0],vel[1],vel[2],euler(0),euler(1),euler(2));
	}
        command.header.stamp = ros::Time::now();
        command.thrust = std::min(std::max(((acc[2]+9.81)*m),0.01),1.3);
        command.roll = roll_des;
        command.pitch = pitch_des;
        command.yaw = yaw_des + yaw_int;
        command.aux.current_yaw = 0;
        command.aux.enable_motors = true;
        command.aux.use_external_yaw = true;
    }

    control_pub.publish(command);

    geometry_msgs::Vector3Stamped Euler;
    Euler.header.stamp = state->header.stamp;
    Euler.vector.x = euler[2];
    Euler.vector.y = euler[1];
    Euler.vector.z = euler[0];
    euler_pub.publish(Euler);
}

int main(int argc, char **argv)
{
  g<<0,
    0,
    9.81;
    std::string fname, fname2; 
    ros::init(argc,argv,"pdcontrol");
    ros::NodeHandle nh("~");
    nh.param<std::string>("output/pos", fname, "out.txt");
    double c_time = ros::Time::now().toSec();
    int time_m = (int)(c_time/10);
    std::stringstream ss;
    ss << time_m;
    fname += ss.str();
    fout = fopen(fname.c_str(),"w");
    fout2 = fopen(fname2.c_str(),"w");
    ros::Subscriber trajectory_sub = nh.subscribe("trajectory",10,trajCallback, ros::TransportHints().tcpNoDelay());
    ros::Subscriber state_sub = nh.subscribe("odom",10,stateCallback, ros::TransportHints().tcpNoDelay());
    ros::Subscriber killsw = nh.subscribe("killsignal",10,killprogram, ros::TransportHints().tcpNoDelay());
    control_pub = nh.advertise<quadrotor_msgs::TRPYCommand>("trpy_cmd",10);
    euler_pub = nh.advertise<geometry_msgs::Vector3Stamped>("euler",10);
    time_st = ros::Time::now().toSec();
    ros::spin();
    fclose(fout);
    fclose(fout2);
   return 0;
}
