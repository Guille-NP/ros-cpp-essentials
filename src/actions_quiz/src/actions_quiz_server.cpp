#include "actions_quiz/CustomActionMsgActionFeedback.h"
#include "actions_quiz/CustomActionMsgActionGoal.h"
#include "actions_quiz/CustomActionMsgActionResult.h"
#include "actions_quiz/CustomActionMsgGoal.h"
#include "std_msgs/String.h"
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <actionlib/TestAction.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <string>

#include <actions_quiz/CustomActionMsgAction.h>

#include <chrono>
#include <string>
#include <thread>
#include <math.h>

class DroneLandTakeoff
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise a strange error occurs.
  actionlib::SimpleActionServer<actions_quiz::CustomActionMsgAction> as_; 
  std::string action_name_;

  // create messages that are used to publish feedback and result
  actions_quiz::CustomActionMsgActionFeedback feedback_;
  actions_quiz::CustomActionMsgActionResult result_;

  // Publishers
  ros::Publisher takeoff;
  std_msgs::Empty takeoff_msg;
  ros::Publisher land;
  std_msgs::Empty land_msg;

  ros::Rate *loop_rate;
  bool success;


public:
  DroneLandTakeoff(std::string name) : 
    as_(nh_, name, boost::bind(&DroneLandTakeoff::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();

    takeoff = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    land = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
    loop_rate = new ros::Rate(1);
    success = true;
  }

  ~DroneLandTakeoff(void)
  {
  }

  void executeCB(const actions_quiz::CustomActionMsgGoalConstPtr &goal)
  {
    std::string cmd = goal->goal;

    if (cmd == "LAND")
    {
        land_drone();
    }
    else if (cmd ==  "TAKEOFF")
    {
        take_off();
    }

    if(success)
    {      
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      //as_.setSucceeded(result_);
    }
  }

  void take_off()
  {
    ROS_INFO("Taking Off Drone...");
    int i = 0;
    while(i < 4)
    {
        takeoff.publish(takeoff_msg);
        loop_rate->sleep();
        i++;
    }
  }

  void land_drone()
  {
    ROS_INFO("Landing Drone...");
    int i = 0;
    while (i < 4)
    {
        land.publish(land_msg);
        loop_rate->sleep();
        i++;
    }
  }

};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "custom_action_msg_as");

  DroneLandTakeoff drone_land_takeoff("action_custom_msg_as");
  ros::spin();

  return 0;
}