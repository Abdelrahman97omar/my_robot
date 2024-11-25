#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

int main(int argc, char** argv) {
    
    ros::init(argc, argv, "action_client");
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("goal_action_topic", true);

    ROS_INFO("Waiting for the action server to start...");
    ac.waitForServer();  // Wait until the server is ready
    ROS_INFO("Action server started. Sending goals...");

        // geometry_msgs::Pose goals = goal_msg;

        move_base_msgs::MoveBaseGoal goal_msg;

        goal_msg.target_pose.header.frame_id = "map";
        goal_msg.target_pose.header.stamp = ros::Time::now();
        goal_msg.target_pose.pose.position.x = 2;
        goal_msg.target_pose.pose.position.y = 2;
        goal_msg.target_pose.pose.orientation.x = 0.0;
        goal_msg.target_pose.pose.orientation.y = 0.0;
        goal_msg.target_pose.pose.orientation.z = 0.6;
        goal_msg.target_pose.pose.orientation.w = -0.75;

        ac.sendGoal(goal_msg);
        // ac.getState().toString().c_str()
        bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

        if (finished_before_timeout) {
            if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                ROS_INFO("Goal reached successfully.");
            else
                ROS_WARN("Goal failed with state:");
        } else {
            ROS_ERROR("Goal timed out.");
        }
    

    ROS_INFO("All goals processed.");
    return 0;
}
