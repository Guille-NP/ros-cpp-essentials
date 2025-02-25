#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <actionlib/TestAction.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <chrono>
#include <thread>
#include <math.h>

class DroneSquareMove
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise a strange error occurs.
  actionlib::SimpleActionServer<actionlib::TestAction> as_; 
  std::string action_name_;

  // create messages that are used to publish feedback and result
  actionlib::TestFeedback feedback_;
  actionlib::TestResult result_;

  // Publishers
  ros::Publisher takeoff;
  std_msgs::Empty takeoff_msg;
  ros::Publisher land;
  std_msgs::Empty land_msg;
  ros::Publisher vel_pub;
  geometry_msgs::Twist vel_msg;
  ros::Rate *loop_rate;
  bool success;


public:
  DroneSquareMove(std::string name) : 
    as_(nh_, name, boost::bind(&DroneSquareMove::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();

    takeoff = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    land = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
    vel_pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    loop_rate = new ros::Rate(1);
    success = true;
  }

  ~DroneSquareMove(void)
  {
  }

  void executeCB(const actionlib::TestGoalConstPtr &goal)
  {
    int side = goal->goal;

    this->take_off();

    for(int i=0; i<4; i++)
    {
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }

      this->move_forward(side);
      this->turn_left();

      this->feedback_.feedback = i;
      this->as_.publishFeedback(feedback_);

      loop_rate->sleep();
    }

    this->stop_moving();

    if(success)
    {
      result_.result = side*4 + (long int)(4.0*M_PI);     // Tiempo por cada lado + Tiempo por cada giro
      
      ROS_INFO("The total time was %i seconds", result_.result);
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);

      this->land_drone();
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

  void move_forward(int side)
  {
    ROS_INFO("Moving forward...");
    vel_msg.linear.x = 1;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
    std::this_thread::sleep_for(std::chrono::seconds(side));
  }

  void turn_left()
  {
    ROS_INFO("Turning left...");
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.54;
    vel_pub.publish(vel_msg);
    std::this_thread::sleep_for(std::chrono::milliseconds((long int)(2000.0*M_PI/2.0)));
  }

  void stop_moving()
  {
    ROS_INFO("Stopping moving...");
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
  }

};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "drone_square_move");

  DroneSquareMove drone_square_move("drone_square_move_as");
  ros::spin();

  return 0;
}