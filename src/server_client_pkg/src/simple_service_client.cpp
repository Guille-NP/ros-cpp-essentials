#include "ros/ros.h"
#include "trajectory_by_name_srv/TrajByName.h"      // Ejercicio 5.1
#include "iri_wam_reproduce_trajectory/ExecTraj.h"  // Ejercicio 5.2
#include <ros/package.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_service_client_node"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  // Create the connection to the service /trajectory_by_name
  /*  // Ejercico 5.1
  // Create the connection to the service /trajectory_by_name
  ros::service::waitForService("/trajectory_by_name");  // wait for service to be running
  ros::ServiceClient traj_by_name_service = nh.serviceClient<trajectory_by_name_srv::TrajByName>("/trajectory_by_name");
  trajectory_by_name_srv::TrajByName srv; // Create an object of type TrajByName
  srv.request.traj_name = "release_food"; // Fill the variable traj_name with the desired value
  
  if (traj_by_name_service.call(srv)) // Send through the connection the name of the trajectory to execute
  {
    ROS_INFO("%s", srv.response.status_message.c_str()); // Print the result given by the service called
  }
  else
  {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }
  */

  // Ejercico 5.2
  ros::ServiceClient execute_trajectory_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj srv;
  srv.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
  
  if (execute_trajectory_service.call(srv)) 
  {
    ROS_INFO("%s", "Service successfully called. Executing trajectory.");
  }
  else
  {
    ROS_ERROR("Failed to call service /execute_trajectory");
    return 1;
  }


  return 0;
}