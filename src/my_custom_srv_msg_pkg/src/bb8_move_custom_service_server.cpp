#include "ros/ros.h"
#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include <chrono>
#include <thread>


ros::Publisher pub;
geometry_msgs::Twist vel;
bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request  &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res)
{  
  ROS_INFO("move_bb8_in_circle_custom has been called");
  
  vel.linear.x = 0.7;
  vel.angular.z = 1.0;
  pub.publish(vel);

  std::this_thread::sleep_for(std::chrono::seconds(req.duration));

  vel.linear.x = 0.0;
  vel.angular.z = 0.0;
  pub.publish(vel);
  res.success = true;

  ROS_INFO("move_bb8_in_circle_custom has ended");

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_move_custom_service_server");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService("/move_bb8_in_circle_custom", my_callback);

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ROS_INFO("move_bb8_in_circle_custom ready");
  ros::spin();


  return 0;
}