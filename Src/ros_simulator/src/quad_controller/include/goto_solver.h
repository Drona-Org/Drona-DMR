#ifdef __cplusplus
extern "C" {
#endif

struct TrajectoryInfo
{
    double xcoef[8];
    double ycoef[8];
    double zcoef[8];
    double duration;
};

void set_t_goto(double _t_goto);
TrajectoryInfo cal_goto(double x_init, double y_init, double z_init, double x_dest, double y_dest, double z_dest);

TrajectoryInfo cal_goto_with_t(double x_init, double y_init, double z_init, 
							   double x_dest, double y_dest, double z_dest,
							   double t);

#ifdef __cplusplus
}
#endif