#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>

ros::Publisher pub;
geometry_msgs::Twist vel;

bool my_callback(std_srvs::Empty::Request  &req,
                 std_srvs::Empty::Response &res)
{  
  ROS_INFO("move_bb8_in_circle_custom called");

  vel.linear.x = 1; 
  vel.angular.z = 0.7;
  vel_pub.publish(vel);

  ROS_INFO("move_bb8_in_circle_custom has ended");
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_move_in_circle_service_server_node");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService("/move_bb8_in_circle", my_callback);
  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ROS_INFO("/move_bb8_in_circle_custom ready");
  ros::spin();

  return 0;
}