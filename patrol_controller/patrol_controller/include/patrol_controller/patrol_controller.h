#include <ros/ros.h>
#include <costmap_2d/costmap_2d.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <nav_msgs/Path.h>
#include <tf/transform_datatypes.h>
#include <vector>
#include <nav_core/base_global_planner.h>
#include <nav_msgs/GetPlan.h>
#include <dynamic_reconfigure/server.h>
#include <iostream>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <patrol_controller/PatrolLoop.h>
#include <string>
#include <sstream>
#include <actionlib/server/simple_action_server.h>
#include <patrol_controller/DoPatrolAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "summa/ack.h"

typedef actionlib::SimpleActionServer<patrol_controller::DoPatrolAction> DoPatrolActionServer;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseActionClient;

class patrolController  {
    public:
       
        patrolController(tf::TransformListener& tf);
        ros::NodeHandle* nh;

    private:       
    
        void executeCb(const patrol_controller::DoPatrolGoalConstPtr& patrolLoop);

        patrol_controller::PatrolLoop  patrolLoop_;
        bool initialized_;       
        tf::TransformListener& tf_;
        DoPatrolActionServer* as_;
        MoveBaseActionClient* ac_;
        ros::ServiceClient* client;
      

};


