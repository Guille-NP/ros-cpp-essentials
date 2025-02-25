#include "ros/ros.h"
#include "std_srvs/Empty.h" 

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_move_in_circle_service_client");
  ros::NodeHandle nh;

  ros::ServiceClient move_bb8_in_circle_client = nh.serviceClient<std_srvs::Empty>("/move_bb8_in_circle");
  std_srvs::Empty srv;
  
  if (move_bb8_in_circle_client.call(srv))
  {
    ROS_INFO("Service successfully called. Moving BB8 in a circle.");
  }
  else
  {
    ROS_ERROR("Failed to call service /move_bb8_in_circle");
    return 1;
  }

  return 0;
}