#ifdef __cplusplus
#include <ros/ros.h>
extern ros::NodeHandle *node_handle;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void init_ros(const char* program_name, int *argc, char *argv[]);

#ifdef __cplusplus
}
#endif