#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include<geometry_msgs/Pose.h>
#include <std_msgs/String.h>

ros::Publisher pub;

// Feedback callback
void feedbackCB(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback) {

    //In this function add condition that if feedback doesn't match goal odom, cancel current goal and send to gui to send new goal

}
// Result callback
void doneCB(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result) {

    ROS_INFO("in call back %s", state.toString().c_str());
    ROS_INFO("in donce");
    if (state == actionlib::SimpleClientGoalState::SUCCEEDED) {
        ROS_INFO("goal succeded");
        std_msgs::String robotresult;
        robotresult.data = "Done";
        pub.publish(robotresult);
}
}

// Active callback
void activeCB() {
    ROS_INFO("Goal is now being processed by the server.");
}
void guiCB(const geometry_msgs::Pose::ConstPtr& my_msg, actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>& ac)
{
        ROS_INFO("I have received a goal");
        move_base_msgs::MoveBaseGoal goal_to_server;
        goal_to_server.target_pose.header.frame_id = "map";
        goal_to_server.target_pose.header.stamp = ros::Time::now();
        goal_to_server.target_pose.pose.position.x= my_msg->position.x;
        goal_to_server.target_pose.pose.position.y= my_msg->position.y;
        goal_to_server.target_pose.pose.orientation.x= my_msg->orientation.x;
        goal_to_server.target_pose.pose.orientation.y= my_msg->orientation.y;
        goal_to_server.target_pose.pose.orientation.z= my_msg->orientation.z;
        goal_to_server.target_pose.pose.orientation.w= my_msg->orientation.w;
        
        ac.sendGoal(goal_to_server,&doneCB, &activeCB, &feedbackCB);
        
}
int main(int argc, char** argv) {


    ros::init(argc, argv, "action_client");
    ros::NodeHandle nh;

    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("goal_action_topic", true);
    ROS_INFO("Waiting for the action server to start...");
    ac.waitForServer();  // Wait until the server is ready
    ROS_INFO("Action server started. Sending goals...");

    ros::Subscriber sub;
    pub = nh.advertise<std_msgs::String>("GUI_Cleint_state_topic",1000);
    sub = nh.subscribe<geometry_msgs::Pose>("gui_action_topic_send_table", 1000,boost::bind(guiCB, _1, boost::ref(ac)));
    ros::spin();
    //====================================================================
    return 0;
}
