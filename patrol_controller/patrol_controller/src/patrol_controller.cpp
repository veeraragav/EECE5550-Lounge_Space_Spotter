#include <patrol_controller/patrol_controller.h>
#include <unistd.h>

patrolController::patrolController(tf::TransformListener& tf): tf_(tf){

    as_ = new DoPatrolActionServer(ros::NodeHandle(), "patrol_controller", boost::bind(&patrolController::executeCb, this, _1), false);
    as_->start();

    ac_ = new MoveBaseActionClient("move_base", false);
    nh = new ros::NodeHandle("nh");
    static ros::ServiceClient cli;
    cli = nh->serviceClient<summa::ack>("/darknet_ros/count_lounge");
    client = &cli;
}

void patrolController::executeCb(const patrol_controller::DoPatrolGoalConstPtr& patrolLoop){

    patrolLoop_ = patrolLoop->loop; 
    

    ros::NodeHandle n;
    int rounds = 3;

    patrol_controller::DoPatrolFeedback feedback;

    

    int start_node = 0;

    int goal_node_index = start_node;
    int jump = 1;
    int x = patrolLoop_.loop.size() * rounds;

    while(n.ok() && rounds){

        ROS_DEBUG("Round: %d", rounds);

        goal_node_index = start_node;
        
        for(int i=0; i < patrolLoop_.loop.size(); i++){
            
            
            move_base_msgs::MoveBaseGoal goal;
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();

            geometry_msgs::Pose pos;
            pos = patrolLoop_.loop[goal_node_index];
            goal.target_pose.pose.position = pos.position;

            goal.target_pose.pose.orientation = pos.orientation;

            ROS_DEBUG("Sending goal");
            ac_->sendGoal(goal);
            ac_->waitForResult();
            if(ac_->getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
                ROS_DEBUG("Hooray, the base executed goal %d", i);
            }

            usleep(10000000); //10sec sleep
            summa::ack srv;
            srv.request.lounge = goal_node_index;
            std::cout<<"Gonna call Arvind's service";
            if (client->call(srv))
            {
                ROS_INFO("Free Space in loung %d: %d",goal_node_index, (int)srv.response.count);
            }
            else
            {
                
                ROS_ERROR("Failed to call service ");
            
            }
            
            goal_node_index = (goal_node_index+1) % patrolLoop_.loop.size();

            

        }

        rounds--;


    }
    patrol_controller::DoPatrolResult result;
    result.result = 1; 

   as_->setSucceeded(result);
   
}
