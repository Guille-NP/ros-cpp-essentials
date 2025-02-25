
#include <geometry_msgs/Twist.h> // Ejercicio 3.2
#include <ros/ros.h>
#include <std_msgs/Int32.h> // Ejercicio 3.1

// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

int main(int argc, char **argv) {

  ros::init(argc, argv,
            "topic_publisher"); // Initiate a Node named 'topic_publisher'
  ros::NodeHandle nh;

  // Ejercicio 3.1
  // ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000); //
  // Create a Publisher object, that will publish on the /counter topic messages
  
  // Ejercicio 3.2
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1000); // Create a Publisher object, that will publish on the
                                                            // /cmd_vel topic messages

  // of type Int32
  ros::Rate loop_rate(2); // Set a publish rate of 2 Hz

  // Ejercicio 3.1
  // std_msgs::Int32 count; // Create a variable of type Int32
  // count.data = 0; // Initialize 'count' variable

  // Ejercicio 3.2
  geometry_msgs::Twist twist; // Create a variable of type Twist
  twist.angular.z = 0.2;
  twist.linear.x = 0.3;

  while (ros::ok()) // Create a loop that will go until someone stops the
                    // program execution
  {
    // Ejercicio 3.1
    // pub.publish(count); // Publish the message within the 'count' variable

    // Ejercicio 3.2
    pub.publish(twist); // Publish the message within the 'twist' variable

    ros::spinOnce();
    loop_rate.sleep(); // Make sure the publish rate maintains at 2 Hz
    
    // Ejercicio 3.1
    //++count.data;      // Increment 'count' variable
  }

  return 0;
}