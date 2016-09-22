#include "goto_solver.h"
#include <Eigen/Dense>
#include <iostream>

static Eigen::MatrixXd A_goto(6,6);

static double t_goto = 0.5;

inline Eigen::MatrixXd A_from_t(double t)
{
    Eigen::MatrixXd A(6,6);
    A << 1.0,0.0,0.0,0.0,0.0,0.0,
    0.0,1.0,0.0,0.0,0.0,0.0,
    0.0,0.0,2.0,0.0,0.0,0.0,
    1,t,pow(t,2),pow(t,3),pow(t,4),pow(t,5),
    0,1,2*t,3*pow(t,2),4*pow(t,3),5*pow(t,4),
    0.0,0.0,2.0,6.0*t,12.0*pow(t,2),20.0*pow(t,3);
    return A;
}

static TrajectoryInfo cal_goto_with_A(double x_init, double y_init, double z_init, 
                                    double x_dest, double y_dest, double z_dest, 
                                    Eigen::MatrixXd &A, double t)
{
    TrajectoryInfo cur_traj;
    Eigen::VectorXd bx(6),by(6), bz(6), solx(6), soly(6), solz(6);
    bx<< x_init,0.0,0.0,x_dest,0.0,0.0;
    solx = A.colPivHouseholderQr().solve(bx);
    by<< y_init,0.0,0.0,y_dest,0.0,0.0;
    soly = A.colPivHouseholderQr().solve(by);
    bz<< z_init,0.0,0.0,z_dest,0.0,0.0;
    solz = A.colPivHouseholderQr().solve(bz);
    cur_traj.duration = t;
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
    return cur_traj;
}

TrajectoryInfo cal_goto(double x_init, double y_init, double z_init, double x_dest, double y_dest, double z_dest) 
{
    return cal_goto_with_A(x_init, y_init, z_init, x_dest, y_dest, z_dest, A_goto, t_goto);
}

TrajectoryInfo cal_goto_with_t(double x_init, double y_init, double z_init, 
                               double x_dest, double y_dest, double z_dest,
                               double t) 
{
    Eigen::MatrixXd A = A_from_t(t);
    return cal_goto_with_A(x_init, y_init, z_init, x_dest, y_dest, z_dest, A, t);
}

void set_t_goto(double _t_goto)
{
    t_goto = _t_goto;
    A_goto = A_from_t(t_goto);
}

