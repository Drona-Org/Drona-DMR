#include "goto_solver.h"
#include <Eigen/Dense>

static Eigen::MatrixXd A_goto(6,6);

static double t_goto = 0.5;

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
    return cur_traj;
}

void set_t_goto(double _t_goto)
{
t_goto = _t_goto;
A_goto << 1.0,0.0,0.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,0.0,0.0,
0.0,0.0,2.0,0.0,0.0,0.0,
1,t_goto,pow(t_goto,2),pow(t_goto,3),pow(t_goto,4),pow(t_goto,5),
0,1,2*t_goto,3*pow(t_goto,2),4*pow(t_goto,3),5*pow(t_goto,4),
0.0,0.0,2.0,6.0*t_goto,12.0*pow(t_goto,2),20.0*pow(t_goto,3);
}

