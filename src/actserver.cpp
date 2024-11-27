#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>

// Callback function for processing goals
void executeCB(const move_base_msgs::MoveBaseGoalConstPtr& goal,
               actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction>* as,
               ros::Publisher* goal_pub) {
    ROS_INFO("Received goal: x = %f, y = %f", goal->target_pose.pose.position.x, goal->target_pose.pose.position.y);
    geometry_msgs::PoseStamped simple_goal;
    simple_goal.header.frame_id = "map";
    simple_goal.header.stamp = ros::Time::now();
    simple_goal.pose = goal->target_pose.pose;

    goal_pub->publish(simple_goal);
    ROS_INFO("Goal sent to move_base.");

    as->setSucceeded();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "action_server");
    ros::NodeHandle nh;

    // Create publisher for sending goals to /move_base_simple/goal
    ros::Publisher goal_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);

    // Create the Action Server
    actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> as(nh,"goal_action_topic",boost::bind(&executeCB, _1, &as, &goal_pub),false);
    as.start();
    ROS_INFO("Action Server started. Waiting for goals...");

    ros::spin();
    return 0;
}
