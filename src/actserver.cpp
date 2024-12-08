#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>

// Callback function for processing goals
double goalEcludiandistance=0;
double currentEcludiandistance=0;
void executeCB(const move_base_msgs::MoveBaseGoalConstPtr& goal,actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction>* as,ros::Publisher* goal_pub,
move_base_msgs::MoveBaseFeedback *odomFeedback,move_base_msgs::MoveBaseResult *goalResult) 
{

    ROS_INFO("Received goal: x = %f, y = %f", goal->target_pose.pose.position.x, goal->target_pose.pose.position.y);
    ROS_INFO("PROCESSING GOAL");
    geometry_msgs::PoseStamped simple_goal;
    simple_goal.header.frame_id = "map";
    simple_goal.header.stamp = ros::Time::now();
    simple_goal.pose = goal->target_pose.pose;
    goal_pub->publish(simple_goal);

    goalEcludiandistance = sqrt(pow(goal->target_pose.pose.position.x, 2) + pow(goal->target_pose.pose.position.y, 2));
    ROS_INFO("the goal ec distance is %f",goalEcludiandistance);
    ros::Time start_time = ros::Time::now();
    bool isDone=false;
    while (as->isActive() && !isDone)
    {
    currentEcludiandistance=sqrt(pow(goal->target_pose.pose.position.x - odomFeedback->base_position.pose.position.x, 2) + 
                                    pow(goal->target_pose.pose.position.y - odomFeedback->base_position.pose.position.y, 2));

    ROS_INFO("the current ec distance is %f",currentEcludiandistance);
    if (fabs(currentEcludiandistance - goalEcludiandistance) <= 0.2) 
    {
        ROS_INFO("difference is %f",abs(currentEcludiandistance - goalEcludiandistance));
        as->setSucceeded();
        isDone=true;
    }
    ros::Duration processing_time = ros::Time::now() - start_time;
    // Example timeout condition (optional)
    if (processing_time.toSec() > 30.0) { // Timeout after 30 seconds
        ROS_WARN("Goal processing timeout.");
        as->setAborted();
        isDone=true;

    }
    ros::Duration(0.1).sleep();
}
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "action_server");
    ros::NodeHandle nh;

    // Create publisher for sending goals to /move_base_simple/goal
    ros::Publisher goal_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
    move_base_msgs::MoveBaseFeedback odomFeedback;
    move_base_msgs::MoveBaseResult goalResult;
    // Create the Action Server
    actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> as(nh,"goal_action_topic",boost::bind(&executeCB, _1, &as, &goal_pub, &odomFeedback, 
    &goalResult),false);
     // Create the Action Server

    as.start();
    ROS_INFO("Action Server started. Waiting for goals...");

    ros::spin();
    return 0;
}
