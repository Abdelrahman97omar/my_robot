# Autonomous Mobile Robot

## Introduction

## Creating URDF and Gazebo plugins

## Creating world

## Mapping
The robot have to create a map of the environment for the first time in order to use it later for navigation around obstacles Autonomously. using the Slam algorithm along with odometry sensors such as encoders and lidar, a map is created and saved for later use.
The package used for mapping is gmapping pkg which is based on occubancy grid map and MCL filter for mapping and localization.
I used teleop_twist_keyboard package to move the robot with the keyboard and control its speed.

#### The environment:

<div>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/map1.png" width="600" height="400" \>
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/map2.png" width="600" height="400" \>
</div>

Mapping commands :
```
roslaunch my_robot gmapping.launch
rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
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

<p float="left">
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/rviz-nav.gif" width="480" height="350" />
  &nbsp;&nbsp;&nbsp;&nbsp;
  <img src="https://github.com/Abdelrahman97omar/my_robot/blob/master/pictures/gaz-nav.gif" width="480" height="350" /> 
</p>



### AMCL
### Path Planning

## Operation
```
roslaunch my_robot gazebo.launch
roslaunch my_robot rviz.launch
roslaunch my_robot navigation.launch
rosrun my_robot send_goal
```
[YOUTUBE](https://www.youtube.com/watch?v=evz1LqEomTE) -video illust


