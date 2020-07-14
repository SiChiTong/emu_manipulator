# eμ 6-Axis Manipulator's ROS Melodic Morenia Package

## General Commands
Action | ROS Topic | Message Type
------------ | ------------- | -------------
Call methods in Core.py | emu/command | std_msgs/String
Print data in GUI | emu/log | std_msgs/String
Emu's actuators speed (10%-120%) | emu/speed_ratio | std_msgs/int8
Emu's actuators acceleration (10%-120%) | emu/accel_ratio | std_msgs/int8
Jog in configuration space | emu/jog/configuration | trajectory_msgs/JointTrajectoryPoint
Jog in cartesian space | emu/jog/cartesian | geometry_msgs/Twist
Emu's joint states | emu/joint_states | sensor_msgs/JointStates
Emu's multi joint trajectory | emu/planner/joint_trajectory/all | trajectory_msgs/JointTrajectory
Emu's single joint trajectory | emu/planner/joint_trajectory/single | trajectory_msgs/JointTrajectoryPoint

## Module 8-9 2020 Related Commands
Action | ROS Topic | Message Type
------------ | ------------- | -------------
Predicted image of the right tray| emu/vision/right_tray | sensors_msgs/Image
Predicted image of the left tray | emu/vision/left_tray | sensors_msgs/Image
Trashes positions | emu/vision/trash_poses | geometry_msgs/PoseArray 
