#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include<geometry_msgs/Pose.h>

void guiCB(const geometry_msgs::Pose::ConstPtr& my_msg, actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>& ac)
{
        ROS_INFO("entered the call baack functiooon");
        double x=my_msg->position.x;
        double y=my_msg->position.y;
        double Q_x=my_msg->orientation.x;
        double Q_y=my_msg->orientation.y;
        double Q_z=my_msg->orientation.z;
        double Q_w=my_msg->orientation.w;
        move_base_msgs::MoveBaseGoal goal_to_server;
        goal_to_server.target_pose.header.frame_id = "map";
        goal_to_server.target_pose.header.stamp = ros::Time::now();
        goal_to_server.target_pose.pose.position.x= x;
        goal_to_server.target_pose.pose.position.y= y;
        goal_to_server.target_pose.pose.orientation.x= Q_x;
        goal_to_server.target_pose.pose.orientation.y= Q_y;
        goal_to_server.target_pose.pose.orientation.z= Q_z;
        goal_to_server.target_pose.pose.orientation.w= Q_w;

        ac.sendGoal(goal_to_server);
}
int main(int argc, char** argv) {
    
    ros::init(argc, argv, "action_client");
    ros::NodeHandle nh;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("goal_action_topic", true);
    ROS_INFO("Waiting for the action server to start...");
    ac.waitForServer();  // Wait until the server is ready
    ROS_INFO("Action server started. Sending goals...");

        //================== Add subscriber and publisher to gui==============
        ros::Publisher pub;
        ros::Subscriber sub;
        ROS_INFO("done sub init");
        // pub=nh.advertise("",1000);
        sub = nh.subscribe<geometry_msgs::Pose>("gui_action_topic_send_table", 1000,boost::bind(guiCB, _1, boost::ref(ac)));
        ROS_INFO("Done CB init");
        ros::spin();
        //====================================================================
        // ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED

    return 0;
}
