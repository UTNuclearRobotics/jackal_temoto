
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *  The basis of this file has been automatically generated
 *  by the TeMoto action package generator. Modify this file
 *  as you wish but please note:
 *
 *    WE HIGHLIY RECOMMEND TO REFER TO THE TeMoto ACTION
 *    IMPLEMENTATION TUTORIAL IF YOU ARE UNFAMILIAR WITH
 *    THE PROCESS OF CREATING CUSTOM TeMoto ACTION PACKAGES
 *    
 *  because there are plenty of components that should not be
 *  modified or which do not make sence at the first glance.
 *
 *  See TeMoto documentation & tutorials at: 
 *    https://temoto-telerobotics.github.io
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <class_loader/class_loader.hpp>
#include "ta_navigation_arl/temoto_action.h"
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <arl_nav_msgs/GotoRegionAction.h>
#include "tf/tf.h"

/* 
 * ACTION IMPLEMENTATION of TaNavigationArl 
 */
class TaNavigationArl : public TemotoAction
{
public:

/*
 * Function that gets invoked only once (when the action is initialized) throughout the action's lifecycle
 */
void initializeTemotoAction()
{
  /* * * * * * * * * * * * * * * * * * * * * * *
   *                          
   * ===> YOUR INITIALIZATION ROUTINES HERE <===
   *                          
   * * * * * * * * * * * * * * * * * * * * * * */

  TEMOTO_INFO_STREAM("Action initialized");
}

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
{
  getInputParameters();
  actionlib::SimpleActionClient<arl_nav_msgs::GotoRegionAction> gotoregion_client_(in_param_robot_name + "/goto_region", true);
  
  geometry_msgs::PoseStamped target_pose;
  target_pose.pose.position.x = in_param_pose_2d_x;
  target_pose.pose.position.y = in_param_pose_2d_y;
  target_pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, in_param_pose_2d_yaw);
  target_pose.header.frame_id = in_param_ref_frame;

  bool goal_reached = false;
  while (!goal_reached && actionOk())
  try
  {
    // TEMOTO_INFO_STREAM_("Sending a navigation goal to " << in_param_robot_name << " ...");
    // rmi_.navigationGoal(in_param_robot_name, "map", target_pose);

    arl_nav_msgs::GotoRegionGoal goal;

    goal.region_center = target_pose;
    
    nav_attempts_made_ = 1;
    goal.radius = 1.0 * nav_attempts_made_;
    goal.angle_threshold = 30.0 * nav_attempts_made_ / 180.0 * M_PI;


    typedef actionlib::SimpleActionClient<arl_nav_msgs::GotoRegionAction> Client;
    // gotoregion_client_.sendGoal(goal,
    //                             boost::bind(&Supervisor::waypointDoneCb, this, _1, _2),
    //                             Client::SimpleActiveCallback(),
    //                             Client::SimpleFeedbackCallback());
    ROS_INFO("Waiting for server");
    gotoregion_client_.waitForServer();
    ROS_INFO("Sending goal.");
    gotoregion_client_.sendGoal(goal);    

    // while(gotoregion_client_.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
    // {
    //   // TEMOTO_INFO_STREAM(gotoregion_client_.getState());
    //   std::cout << gotoregion_client_.getState() << std::endl;
    //   gotoregion_client_.sendGoal(goal);
    //   ros::Duration(20).sleep();
    // }


    //wait for the action to return
    bool finished_before_timeout = gotoregion_client_.waitForResult(ros::Duration(30.0));

    if (finished_before_timeout)
    {    
      ROS_INFO("Action finished: %s",gotoregion_client_.getState().toString().c_str());
    }
    else
    {
      ROS_INFO("Action did not finish before the time out. %s",gotoregion_client_.getState().toString().c_str());

    }
      



      goal_reached = true;
      TEMOTO_INFO_STREAM("Done navigating");
    
    
  }
  catch(int e)
  {
    TEMOTO_WARN_STREAM("Caught an error: ");
  }

  setOutputParameters();
}

// Destructor
~TaNavigationArl()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_ref_frame = GET_PARAMETER("ref_frame", std::string);
  in_param_pose_2d_x = GET_PARAMETER("pose_2d::x", double);
  in_param_pose_2d_y = GET_PARAMETER("pose_2d::y", double);
  in_param_pose_2d_yaw = GET_PARAMETER("pose_2d::yaw", double);
  in_param_robot_name = GET_PARAMETER("robot_name", std::string);
}

// Sets the output parameters which can be passed to other actions
void setOutputParameters()
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Declaration of input parameters
std::string in_param_ref_frame;
double in_param_pose_2d_x;
double in_param_pose_2d_y;
double in_param_pose_2d_yaw;
std::string in_param_robot_name;

ros::NodeHandle nh_;
int nav_attempts_made_ = 1;

}; // TaNavigationArl class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaNavigationArl, ActionBase);
