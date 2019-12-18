#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <patrol_controller/DoPatrolAction.h>
#include <patrol_controller/PatrolLoop.h>
#include <geometry_msgs/Pose.h>

int main (int argc, char **argv)
{
  ros::init(argc, argv, "fakee");
  std::cout<<"fakee"<<std::endl;
  actionlib::SimpleActionClient<patrol_controller::DoPatrolAction> ac("patrol_controller", true);
  std::cout<<"fakee"<<std::endl;
  ros::NodeHandle n;


  std::vector<geometry_msgs::Pose> loop;

 
  geometry_msgs::Pose pose;
  
  pose.position.x = -16.25;
  pose.position.y = -19.28;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = -0.311;
  pose.orientation.w = 0.95;
  loop.push_back(pose);

  pose.position.x = 3.486;
  pose.position.y = -2.115;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.397;
  pose.orientation.w = 0.918;
  loop.push_back(pose);



  pose.position.x = -22.163;
  pose.position.y = 23.183;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.504;
  pose.orientation.w = 0.864;
  loop.push_back(pose);





 /* 
  pose.position.x = 15.833;
  pose.position.y = 0.861;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);

  pose.position.x = 23.5;
  pose.position.y = 1;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);



  pose.position.x = 36.653;
  pose.position.y = 9.631;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);


  pose.position.x = 43.64;
  pose.position.y = 13.2;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);

  pose.position.x = 51;
  pose.position.y = 34;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = 0.956;
  pose.orientation.w = -0.295;
  loop.push_back(pose);

  pose.position.x = 35.9;
  pose.position.y = 33.9;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = -0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);

  pose.position.x = 24.5;
  pose.position.y = 25.1;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = -0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);

  pose.position.x = 14.7;
  pose.position.y = 23.9;
  pose.position.z = 0;  
  pose.orientation.x = 0;
  pose.orientation.y = 0;
  pose.orientation.z = -0.7071068;
  pose.orientation.w = 0.7071068;
  loop.push_back(pose);

*/
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  patrol_controller::DoPatrolGoal goal;
  goal.loop.loop = loop;

  ac.sendGoal(goal);

  //wait for the action to return
  bool finished_before_timeout = ac.waitForResult();

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");

  //exit
  return 0;
}