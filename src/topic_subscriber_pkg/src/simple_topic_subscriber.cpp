#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

// Ejercicio 4.3
/*
void counterCallback(const std_msgs::Int32::ConstPtr& msg) // Define a function
called 'callback' that receives a parameter named 'msg'
{
  ROS_INFO("%d", msg->data); // Print the value 'data' inside the 'msg'
parameter
}
*/
// Ejercicio 4.4
void counterCallback(const nav_msgs::Odometry::ConstPtr
                         &msg) // Define a function called 'callback' that
                               // receives a parameter named 'msg'
{
  // ROS_INFO("%s", msg->header.frame_id.c_str());
  // ROS_INFO("x: %f", msg->pose.pose.position.x);
  ROS_INFO("%f", msg->twist.twist.linear.x);
}

int main(int argc, char **argv) {

  ros::init(argc, argv,
            "odom_sub_node"); // Initiate a Node called 'odom_sub_node'
  ros::NodeHandle nh;

  // Ejercicio 4.3
  // ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback); //
  // Create a Subscriber object that will listen to the /counter topic and will
  // Ejercicio 4.4
  ros::Subscriber sub = nh.subscribe(
      "odom", 1000, counterCallback); // Create a Subscriber object that will
                                      // listen to the /counter topic and will

  // call the 'callback' function each time it reads something from the topic

  ros::spin(); // Create a loop that will keep the program in execution

  return 0;
}