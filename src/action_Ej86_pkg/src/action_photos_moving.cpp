#include <ros/ros.h>
#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>

int nImage = 0;


void take_off()
{
  ros::NodeHandle nh_;
  ros::Publisher takeoff = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
  std_msgs::Empty takeoff_msg;
  ros::Rate loop_rate(1);

  int i = 0;
  while(i < 4)
  {
    takeoff.publish(takeoff_msg);
    ROS_INFO("Taking Off Drone...");
    loop_rate.sleep();
    i++;
  }
}

void land_drone()
{
    ros::NodeHandle nh_;
    ros::Publisher land = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
    std_msgs::Empty land_msg;
    ros::Rate loop_rate(1);

    int i = 0;
    while (i < 4)
    {
        land.publish(land_msg);
        ROS_INFO("Landing Drone...");
        loop_rate.sleep();
        i++;
    }
}

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
  ROS_INFO("[State Result]: %s", state.toString().c_str());
  ROS_INFO("The Action has been completed");

  //ros::shutdown();
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback)
{
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "action_photos_moving_client");
  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
  client.waitForServer();

  ardrone_as::ArdroneGoal goal;
  goal.nseconds = 10;
  
  client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
  //client.waitForResult();
  
  ros::Rate loop_rate(2);
  actionlib::SimpleClientGoalState state_result = client.getState();
  ROS_INFO("[State Result]: %s", state_result.toString().c_str());

  // Vel Publisher
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  geometry_msgs::Twist vel_msg;

  take_off();

  while ( state_result == actionlib::SimpleClientGoalState::ACTIVE || state_result == actionlib::SimpleClientGoalState::PENDING )
  {
    ROS_INFO("Moving while waiting for the Server to give a result...");

    vel_msg.linear.x = 0.5;
    vel_msg.angular.z = 0.1;
    vel_pub.publish(vel_msg);

    loop_rate.sleep();
    state_result = client.getState();
    ROS_INFO("[State Result]: %s", state_result.toString().c_str());
  }

  vel_msg.linear.x = 0.0;
  vel_msg.angular.z = 0.0;
  vel_pub.publish(vel_msg);

  land_drone();
    
  return 0;
}