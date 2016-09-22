#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>
#include <Eigen/Dense>
#include <Eigen/Core>

static std::string mesh_resource;
static ros::Publisher pub_vis;
static double color_r, color_g, color_b, color_a;

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
  visualization_msgs::Marker marker;
  marker.header.frame_id = msg->header.frame_id;
  marker.header.stamp = ros::Time(); // time 0 so that the marker will be displayed regardless of the current time
  marker.ns = "mesh_visualization";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::MESH_RESOURCE;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = msg->pose.pose.position.x;
  marker.pose.position.y = msg->pose.pose.position.y;
  marker.pose.position.z = msg->pose.pose.position.z;
  Eigen::Quaternionf q;
  q.x() = msg->pose.pose.orientation.x;
  q.y() = msg->pose.pose.orientation.y;
  q.z() = msg->pose.pose.orientation.z;
  q.w() = msg->pose.pose.orientation.w;
  Eigen::Matrix3f R(q),R_c;
  R_c<<sqrt(2)/2,-sqrt(2)/2,0,
       sqrt(2)/2,sqrt(2)/2,0,
       0,0,1;
  R = R_c*R;
  Eigen::Quaternionf q_c(R);
  marker.pose.orientation.x = q_c.x();
  marker.pose.orientation.y = q_c.y();
  marker.pose.orientation.z = q_c.z();
  marker.pose.orientation.w = q_c.w();
  marker.scale.x = 0.001;
  marker.scale.y = 0.001;
  marker.scale.z = 0.001;
  marker.color.a = color_a;
  marker.color.r = color_r;
  marker.color.g = color_g;
  marker.color.b = color_b;
  marker.mesh_resource = mesh_resource;
  pub_vis.publish(marker);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mesh_visualization");

  ros::NodeHandle nh("~");

  nh.param("mesh_resource", mesh_resource, std::string("package://mesh_visualization/meshes/hummingbird.mesh"));
  nh.param("color/r", color_r, 1.0);
  nh.param("color/g", color_g, 0.0);
  nh.param("color/b", color_b, 0.0);
  nh.param("color/a", color_a, 1.0);

  ros::Subscriber odom_sub = nh.subscribe("odom", 10, &odom_callback, ros::TransportHints().tcpNoDelay());
  pub_vis = nh.advertise<visualization_msgs::Marker>("robot", 10);

  ros::spin();

  return 0;
}
