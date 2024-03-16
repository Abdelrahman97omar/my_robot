#include <iostream>
#include"ros/ros.h"
#include"geometry_msgs/PoseStamped.h" 
/*================================================================================
  my node name is "send_goal" over topic "/move_base_simple/goal" to send msg
    of type "geometry_msgs/PoseStamped" 
==================================================================================
geometry_msgs/PoseStamped has two compact msgs
1) head -> seq
        -> time stamp
        -> string frame_id

2) pos -> posetion -> x
                   -> y
                   -> z
        -> orintation -> x
                      -> y
                      -> z
                      -> w     

  to access any value, obj.head.frame_id or obj.pose.posetion.x
====================================================================================      
*/
using namespace std;
int main(int argc,char** argv)
{
  ros::init(argc, argv, "send_goal");

  ros::NodeHandle nh;
    
  ros::Publisher goal_coordinates;
  goal_coordinates = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
  
  ros::Rate loop_rate(1);   //how often we will publish our msg. 1 for 1 second

  while(ros::ok())

  {
    geometry_msgs::PoseStamped set; // set is obj. to use the attributed in posestamp with it
    set.header.frame_id = "map";
    
    cout<<"enter x posetion"<<endl;
    cin>>set.pose.position.x;
    cout<<"enter y posetion"<<endl;
    cin>>set.pose.position.y;
    cout<<"enter orintation"<<endl;
    cin>>set.pose.orientation.z;
    set.pose.orientation.w=1;

//after receiving values, we publish them as follow:
    goal_coordinates.publish(set);
    ros::spinOnce(); // Process any callbacks
    loop_rate.sleep();
  }
  
}