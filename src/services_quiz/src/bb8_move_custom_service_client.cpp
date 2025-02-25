#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_move_custom_service_client");
  ros::NodeHandle nh;

  ros::ServiceClient move_bb8_in_square_client = nh.serviceClient<services_quiz::BB8CustomServiceMessage>("/move_bb8_in_square_custom");
  services_quiz::BB8CustomServiceMessage srv;
  
  srv.request.side = 1;
  srv.request.repetitions = 2;
  if (move_bb8_in_square_client.call(srv))
  {
    ROS_INFO("Service successfully called. Moving BB8 in a square.");
  }
  else
  {
    ROS_ERROR("Failed to call service /move_bb8_in_square_custom");
    return 1;
  }

  srv.request.side = 3;
  srv.request.repetitions = 1;
  if (move_bb8_in_square_client.call(srv))
  {
    ROS_INFO("Service successfully called. Moving BB8 in a square.");
  }
  else
  {
    ROS_ERROR("Failed to call service /move_bb8_in_square_custom");
    return 1;
  }

  return 0;
}