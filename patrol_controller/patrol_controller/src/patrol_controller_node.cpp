#include <patrol_controller/patrol_controller.h>

int main(int argc, char** argv){

  ros::init(argc, argv, "patrol_controller_node");  

  tf::TransformListener tf(ros::Duration(10)); //check this

  patrolController pc( tf );

  ros::spin();

  return(0);
}