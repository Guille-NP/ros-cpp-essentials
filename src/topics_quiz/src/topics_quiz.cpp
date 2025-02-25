#include <sensor_msgs/LaserScan.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <string>

float spinVel = 0.0; 
float forwardVel = 0.1;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr &laserScan) 
{
  ROS_INFO("Right: %f", laserScan->ranges[0]);
  ROS_INFO("Forward: %f", laserScan->ranges[360]);
  ROS_INFO("Left: %f", laserScan->ranges[719]);
  
  std::string msg;
  if (laserScan->ranges[360] < 1.0)       {forwardVel = 0.1; spinVel = 0.3;}
  else if (laserScan->ranges[0] < 1.0)    {forwardVel = 0.1; spinVel = 0.3;}
  else if (laserScan->ranges[719] < 1.0)  {forwardVel = 0.1; spinVel = -0.3;}
  else                                    {forwardVel = 0.3; spinVel = 0.0;}

  ROS_INFO("Forward; %f, Spin: %f \n", forwardVel, spinVel);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "topics_quiz_node"); // Initiate a Node called 'topics_quiz_node'
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1000);

  ros::Rate loop_rate(25); // Set the publish rate

  ros::Subscriber sub = nh.subscribe(
      "/kobuki/laser/scan", 1000, laserScanCallback); // Create a Subscriber object that will
                                        // listen to the /scan topic and will

  geometry_msgs::Twist twist; // Create a variable of type Twist


  while (ros::ok()) 
  {
    twist.angular.z = spinVel;
    twist.linear.x = forwardVel;

    pub.publish(twist); // Publish the message within the 'twist' variable

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}