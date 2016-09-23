#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <quadrotor_msgs/QuadData.h>
#include <quadrotor_msgs/TrajectoryData.h>
#include <math.h>
#include <std_msgs/Int8.h>

#define USE_JOYSTICK 0

struct TrajectoryInfo
{
    double xcoef[8];
    double ycoef[8];
    double zcoef[8];
    double duration;
};

TrajectoryInfo cur_traj, next_traj;
bool receive_traj = false, buffer = false, init_b = false;
int count = 0;
int mode = 0;
double des_height = 1, addtf = 0;
double des_pos[2] = {0, 0};
double t_takeoff = 3;
double t_goto = 2, t_wait = 20;
Eigen::MatrixXd A_takeoff(6,6);
Eigen::MatrixXd A_goto(6,6);
bool initial_vicon=false, re_init = false, done_init = false, start = false;
double x_init=0,y_init=0,z_init=0;
double tscale = 1;

void startprogram (const std_msgs::Int8::ConstPtr & msg)
{
  if(msg->data == 0){
    start = true;
    ROS_INFO("GET MESSAGE START");
  }
}

void initialize_var()
{
A_takeoff << 1.0,0.0,0.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,0.0,0.0,
0.0,0.0,2.0,0.0,0.0,0.0,
1,t_takeoff,pow(t_takeoff,2),pow(t_takeoff,3),pow(t_takeoff,4),pow(t_takeoff,5),
0,1,2*t_takeoff,3*pow(t_takeoff,2),4*pow(t_takeoff,3),5*pow(t_takeoff,4),
0.0,0.0,2.0,6.0*t_takeoff,12.0*pow(t_takeoff,2),20.0*pow(t_takeoff,3);
A_goto << 1.0,0.0,0.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,0.0,0.0,
0.0,0.0,2.0,0.0,0.0,0.0,
1,t_goto,pow(t_goto,2),pow(t_goto,3),pow(t_goto,4),pow(t_goto,5),
0,1,2*t_goto,3*pow(t_goto,2),4*pow(t_goto,3),5*pow(t_goto,4),
0.0,0.0,2.0,6.0*t_goto,12.0*pow(t_goto,2),20.0*pow(t_goto,3);
}

void cal_takeoff()
{
    Eigen::VectorXd b(6), sol(6);
    b<< z_init,0.0,0.0,des_height+addtf,0.0,0.0;
    sol = A_takeoff.colPivHouseholderQr().solve(b);
    cur_traj.duration = t_takeoff;
    cur_traj.zcoef[0] = 0;
    cur_traj.zcoef[1] = 0;
    for(int i = 0; i < 6; i++){
        cur_traj.zcoef[7-i] = sol(i);
    }
    done_init = true;
    ROS_INFO("solve takeoff with duration = %f and coef (%f,%f,%f,%f,%f,%f)", cur_traj.duration,sol(0),sol(1),sol(2),sol(3),sol(4),sol(5));
}

void cal_goto()
{
    Eigen::VectorXd bx(6),by(6), bz(6), solx(6), soly(6), solz(6);
    bx<< x_init,0.0,0.0,des_pos[0],0.0,0.0;
    solx = A_goto.colPivHouseholderQr().solve(bx);
    by<< y_init,0.0,0.0,des_pos[1],0.0,0.0;
    soly = A_goto.colPivHouseholderQr().solve(by);
    bz<< z_init,0.0,0.0,des_height,0.0,0.0;
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
    done_init = true;
    ROS_INFO("solve goto");
}

void viconCallback(const nav_msgs::Odometry::ConstPtr& vicon)
{
if(!initial_vicon)
{
  x_init = vicon->pose.pose.position.x;
  y_init = vicon->pose.pose.position.y;
  z_init = vicon->pose.pose.position.z;
  initial_vicon = true;
  cal_takeoff();
}
else{
  if(re_init){
  x_init = vicon->pose.pose.position.x;
  y_init = vicon->pose.pose.position.y;
  z_init = vicon->pose.pose.position.z;
  re_init = false;
  cal_goto();
  }
}
}

void updateTrajCallback(const quadrotor_msgs::TrajectoryData::ConstPtr & msg){
    next_traj.xcoef[0] = msg->xcoef[0];
    next_traj.ycoef[0] = msg->ycoef[0];
    next_traj.zcoef[0] = msg->zcoef[0];
    next_traj.xcoef[1] = msg->xcoef[1];
    next_traj.ycoef[1] = msg->ycoef[1];
    next_traj.zcoef[1] = msg->zcoef[1];
    next_traj.xcoef[2] = msg->xcoef[2];
    next_traj.ycoef[2] = msg->ycoef[2];
    next_traj.zcoef[2] = msg->zcoef[2];
    next_traj.xcoef[3] = msg->xcoef[3];
    next_traj.ycoef[3] = msg->ycoef[3];
    next_traj.zcoef[3] = msg->zcoef[3];
    next_traj.xcoef[4] = msg->xcoef[4];
    next_traj.ycoef[4] = msg->ycoef[4];
    next_traj.zcoef[4] = msg->zcoef[4];
    next_traj.xcoef[5] = msg->xcoef[5];
    next_traj.ycoef[5] = msg->ycoef[5];
    next_traj.zcoef[5] = msg->zcoef[5];
    next_traj.xcoef[6] = msg->xcoef[6];
    next_traj.ycoef[6] = msg->ycoef[6];
    next_traj.zcoef[6] = msg->zcoef[6];
    next_traj.xcoef[7] = msg->xcoef[7];
    next_traj.ycoef[7] = msg->ycoef[7];
    next_traj.zcoef[7] = msg->zcoef[7];
    next_traj.duration = msg->duration;
    buffer = true;
    ROS_INFO("seg receive: (%f %f %f)", next_traj.xcoef[7],next_traj.ycoef[7],next_traj.zcoef[7]);
}


double cal_pos(double c[],double t)
{
    return c[0]*pow(t,7.0) +c[1]*pow(t,6.0) + c[2]*pow(t,5.0) + c[3]*pow(t,4.0) + c[4]*pow(t,3.0) + c[5]*pow(t,2.0) + c[6]*t + c[7];
}

double cal_vel(double c[],double t)
{
    return (c[0]*7*pow(t,6.0) +c[1]*6*pow(t,5.0) + c[2]*5*pow(t,4.0) + c[3]*4*pow(t,3.0) + c[4]*3*pow(t,2.0) + c[5]*2*t + c[6])/tscale;
}

double cal_acc(double c[],double t)
{
    return (c[0]*42*pow(t,5.0) +c[1]*30*pow(t,4.0) + c[2]*20*pow(t,3.0) + c[3]*12*pow(t,2.0) + c[4]*6*t + c[5]*2)/(tscale*tscale);
}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"quad_trajectory");
    ros::NodeHandle nh("~");
    ros::Publisher pub = nh.advertise<quadrotor_msgs::QuadData>("trajectory", 10, true);
    ros::Subscriber trajectory_sub = nh.subscribe("trajectoryinfo",10,updateTrajCallback, ros::TransportHints().tcpNoDelay());
    ros::Subscriber vicon_sub = nh.subscribe("odom",10,viconCallback, ros::TransportHints().tcpNoDelay());
    if(USE_JOYSTICK)
        ros::Subscriber switch_sub = nh.subscribe("startsignal",10,startprogram, ros::TransportHints().tcpNoDelay());
    ros::Rate loop_rate(100);
    quadrotor_msgs::QuadData traj;
    nh.param("des_pos/x", des_pos[0], 0.0);
    nh.param("des_pos/y", des_pos[1], 0.0);
    nh.param("des_pos/z", des_height, 0.8);
    nh.param("add_tf", addtf, 0.0);
    nh.param("time/scale", tscale, 1.0);
    nh.param("time/takeoff", t_takeoff, 4.0);
    nh.param("time/goto", t_goto, 4.0);
    nh.param("time/land", t_wait, 20.0);
    initialize_var();
    double t_start = -1;
    double t_end = 0;
    double cur_t;
    double cur_off[3] = {0,0,des_height};
    double t_command = 0, t_hover = 0;
    bool follow_path = false;
    if(USE_JOYSTICK){
     while(!start)
        ros::spinOnce();
    }
    else{
        sleep(3);
        ros::spinOnce();
    }
    // }

    t_command = ros::Time::now().toSec();
    
    while(nh.ok())
    {
        traj.write = 0;
       if(mode == 0 && done_init){
            cur_t = ros::Time::now().toSec();
            t_command = cur_t;
            t_start = cur_t;
            t_end = cur_t + cur_traj.duration*tscale;
            traj.mode = 0;
            while(cur_t <= t_end){
               double t = (cur_t - t_start)/tscale;
               traj.z = cal_pos(cur_traj.zcoef,t)-0.1;
               traj.vz = cal_vel(cur_traj.zcoef,t);
               traj.acc_z = cal_acc(cur_traj.zcoef,t);
               cur_t = ros::Time::now().toSec();
               pub.publish(traj);
               ros::spinOnce();
               loop_rate.sleep();
            }
            mode = 1;
            re_init = true;
            done_init = false;
            t_command = cur_t;
            follow_path = false;
        }

        if(mode == 1 && done_init){
            cur_t = ros::Time::now().toSec();
            t_command = cur_t;
            t_start = cur_t;
            t_end = cur_t + cur_traj.duration*tscale;
            traj.mode = 2;
            while(cur_t <= t_end){
                double t = (cur_t - t_start)/tscale;
                traj.x = cal_pos(cur_traj.xcoef,t);
                traj.vx = cal_vel(cur_traj.xcoef,t);
                traj.acc_x = cal_acc(cur_traj.xcoef,t);
                traj.y = cal_pos(cur_traj.ycoef,t);
                traj.vy = cal_vel(cur_traj.ycoef,t);
                traj.acc_y = cal_acc(cur_traj.ycoef,t);
                traj.z = cal_pos(cur_traj.zcoef,t);
                traj.vz = cal_vel(cur_traj.zcoef,t);
                traj.acc_z = cal_acc(cur_traj.zcoef,t);
                pub.publish(traj);
                ros::spinOnce();
                loop_rate.sleep();
                cur_t = ros::Time::now().toSec();
            }
            mode = 2;
            t_command = cur_t;
            follow_path = false;
        }

        if(mode == 2 && buffer){
            count++;
            cur_traj.duration = next_traj.duration;
            for(int ii = 0; ii < 8; ii++){
                cur_traj.xcoef[ii] = next_traj.xcoef[ii];
                cur_traj.ycoef[ii] = next_traj.ycoef[ii];
                cur_traj.zcoef[ii] = next_traj.zcoef[ii];
            }
            cur_t = ros::Time::now().toSec();
            t_start = cur_t;
            t_end = cur_t + cur_traj.duration*tscale;
            ROS_INFO("Traj: %d from %f %f %f",count,cur_traj.xcoef[7],cur_traj.ycoef[7],cur_traj.zcoef[7]);
            buffer = false;
            while(cur_t < t_end) 
            {
                traj.mode = 2;
                traj.write = 1;
                double t = (cur_t - t_start)/tscale;
                traj.x = cal_pos(cur_traj.xcoef,t);
                traj.y = cal_pos(cur_traj.ycoef,t);
                traj.z = cal_pos(cur_traj.zcoef,t);
                traj.vx = cal_vel(cur_traj.xcoef,t);
                traj.vy = cal_vel(cur_traj.ycoef,t);
                traj.vz = cal_vel(cur_traj.zcoef,t);
                traj.acc_x = cal_acc(cur_traj.xcoef,t);
                traj.acc_y = cal_acc(cur_traj.ycoef,t);
                traj.acc_z = cal_acc(cur_traj.zcoef,t);
                traj.yaw = 0;
                pub.publish(traj);
                // ros::spinOnce();
                loop_rate.sleep();
                cur_t = ros::Time::now().toSec();
            }
            t_command = cur_t;
            printf("end\n");           
        } else {
            t_hover = ros::Time::now().toSec() - t_command;
            if(t_hover > t_wait) {
                traj.mode = 3;
            } else {
                traj.mode = 1;
            }
        }
        pub.publish(traj);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
