# Autonomous Mobile Robot

## Introduction
This project is a simulation of fully function Autonomous Mobile Robot (AMR). The Project I created will take you to a full journy of the process of creating AMRs simulation, starting from creating the model, adding sensors, passing throught mapping and localization process and finally the navigation part. You will also be able to send the robot goals using your terminal and the robot will navigate in your environment till it reaches the goal.
## Creating URDF and Gazebo plugins
For the URDF, I have chosen a straightforward model constructed using xacro, consisting of a rectangular base, four wheels, a lidar, and a camera. Additionally, I have supplemented this model with Gazebo plugins in a separate file, to add a functionality and adding specs for sensors and controllers by integrating plugins for the Lidar, Camera, and skid-steering mechanisms. Those plugins will affect the simulation and control of the robot and give them features of the real sensors and controllers.

## Creating world

#### The environment:
I have created the environment using gazebo using different shapes and rooms to test all the functionalty of the robot from sensors functionality object avoidance and path planning.
<div>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/map1.png" width="400" height="400" \>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/map2.png" width="400" height="400" \>
</div>

## Mapping
The robot have to create a map of the environment for the first time in order to use it later for navigation around obstacles Autonomously. using the Slam algorithm along with odometry sensors such as encoders and lidar, a map is created and saved for later use.
The package used for mapping is gmapping pkg which is based on occubancy grid map and MCL filter for mapping and localization.
I used teleop_twist_keyboard package to move the robot with the keyboard and control its speed.


Mapping commands :
```
$ roslaunch my_robot gazebo.launch
$ roslaunch my_robot rviz.launch
$ roslaunch my_robot gmapping.launch
$ rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
```

<div>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/mapping.gif" width="700" height="400" \>
</div>


To save the map
```
 rosrun map_server map_saver -f <directory path>/my_map_name
```
<div>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/my_map.jpg" width="600" height="600" \>
</div>


## Navigation
Navigation is the ability of a robot to autonomously move from one location to another while avoiding obstacles and following predefined paths or instructions. For navigation, the robot needs to create a path to the goal and always localize him self in the map. There are multiple algorithms for path planning such as A*, Dijkstra, Breadth first search and Depth first search. As well, multiple algorithms are avaliable for localization such as KF and MCL.
I used ROS navigation stack for navigation process which is a collection of ROS packages for navigation tasks. It consists of four main components: 
1) Map server
2) Localization system
3) Global planner
4) Local planner.
   
The map server provides the static map of the environment, which I have created using SLAM earlier. The localization system estimates the robot's pose in the map, using sensors such as odometry, IMU, or laser scan besides the AMCL filter. The global planner generates a global path from the robot's current pose to the goal pose, using a costmap that represents the occupancy and cost of the environment. The local planner generates a local trajectory that follows the global path, while avoiding dynamic obstacles and respecting the robot's kinematics and dynamics.
I have created navigation.launch file which launches mapserver, amcl.launch and move_base node.
There were also as well 5 .yaml config files to configure the local and global cost maps, local and global planners and move_base node. In those config files, I configured some parameters that as the raduis of the inflation layer, max speed, choosing Dijkstra's algorithm for path planning.


<p float="left">
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/rviz-nav.gif" width="400" height="350" />
  &nbsp;&nbsp;&nbsp;&nbsp;
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/gaz-nav.gif" width="400" height="350" /> 
</p>

### Publishing goals
I have created a node "send_goal" using c++ to send a goal to the robot without using rviz. This node publish msgs of type ``` geometry_msgs/PoseStamped ``` over the topic ``` move_base_simple/goal ```
<div>
    <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/node-terminal.png" width="500" height="300" /> 
</div>

## Operation:

Write the following commands in your terminal after sourcing your setup
In your catkin workspace
```
$ source devel/setup.bash
```
To launch gazebo
```
$ roslaunch my_robot gazebo.launch
```
To launch rviz
```
$ roslaunch my_robot rviz.launch
```
To launch the navigation stack
```
$ roslaunch my_robot navigation.launch
```
To run send_goal node to send goals to the robot using terminal
```
$ rosrun my_robot send_goal
```
<!-- [YOUTUBE](https://www.youtube.com/watch?v=evz1LqEomTE) -video illust -->

