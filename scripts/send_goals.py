#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Odometry
import math

current_pose=Odometry()
x=input()
y=input()
yaw=input()
int(x)
int(y)
int(yaw)

def create_goal(x, y, yaw):

    goal = PoseStamped()
    goal.header.frame_id = "map"  # Use "map" or "odom" based on your setup
    goal.header.stamp = rospy.Time.now()

    # Set position
    goal.pose.position.x = x
    goal.pose.position.y = y
    goal.pose.position.z = 0.0

    # Set orientation (convert yaw to quaternion)
    goal.pose.orientation.x = 0.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = math.sin(yaw / 2.0)
    goal.pose.orientation.w = math.cos(yaw / 2.0)

    return goal
def callback(msg):
    rospy.loginfo("Received goal: x=%f, y=%f, yaw=%f", 
                  msg.pose.position.x, 
                  msg.pose.position.y, 
                  msg.pose.orientation.z)  # For simplicity, just print the pose

def publish_goals():
    """
    Publishes a series of goals to the robot.
    """
    rospy.init_node('goal_publisher', anonymous=True)
    pub = rospy.Publisher('/move_base_simple/goal', PoseStamped, queue_size=10)
    rospy.subscribers('/odom',)
    # Wait for subscribers
    rospy.loginfo("Waiting for subscribers...")
    rospy.sleep(1)

    rate = rospy.Rate(1)  # Publish rate in Hz

    # List of goals: [(x, y, yaw)]
    goals = [
        (2.0, 3.0, 0.0),  # x=2.0, y=3.0, facing forward
        (-1.0, 2.0, math.pi / 2),  # x=-1.0, y=2.0, facing 90 degrees
        (0.0, 0.0, math.pi)  # x=0.0, y=0.0, facing backward
    ]

    for x, y, yaw in goals:
        goal = create_goal(x, y, yaw)
        rospy.loginfo(f"Publishing goal: x={x}, y={y}, yaw={yaw}")
        pub.publish(goal)
        rospy.sleep(5)  # Wait for the robot to process the goal

    rospy.loginfo("All goals sent!")

if __name__ == "__main__":
    try:
        publish_goals()
    except rospy.ROSInterruptException:
        rospy.logerr("Goal publisher interrupted.")
