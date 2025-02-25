#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include <chrono>
#include <thread>
#include <math.h>


ros::Publisher pub;
geometry_msgs::Twist vel;
bool my_callback(services_quiz::BB8CustomServiceMessage::Request  &req,
                 services_quiz::BB8CustomServiceMessage::Response &res)
{  
  ROS_INFO("move_bb8_in_square_custom has been called");
  
  int count = 0;
  vel.linear.x = 0.0;
  vel.angular.z = 0.0;

  while (count < req.repetitions*4)
  {
    vel.linear.x = 0.5;
    vel.angular.z = 0.0;
    pub.publish(vel);
    std::this_thread::sleep_for(std::chrono::milliseconds((long int)(2000*req.side)));
   
    vel.linear.x = 0.0;
    vel.angular.z = 0.54;
    pub.publish(vel);
    std::this_thread::sleep_for(std::chrono::milliseconds((long int)(2000.0*M_PI/2.0)));

    vel.linear.x = 0.0;
    vel.angular.z = 0.0;
    pub.publish(vel);

    count++;
  }
  vel.linear.x = 0.0;
  vel.angular.z = 0.0;
  pub.publish(vel);
  res.success = true;

  ROS_INFO("move_bb8_in_square_custom has ended");

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_move_custom_service_server");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService("/move_bb8_in_square_custom", my_callback);

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ROS_INFO("move_bb8_in_square_custom ready");
  ros::spin();


  return 0;
}