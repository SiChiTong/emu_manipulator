#!/usr/bin/env python

#ros modueles
import copy
import rospkg
import rospy
import geometry_msgs.msg
from tf.transformations import quaternion_from_euler
from std_msgs.msg import String

#python modules
import sys
import os
from math import pi, cos, sin
import time

#moveit modules
import moveit_commander
import moveit_msgs.msg
import moveit_msgs.srv
from moveit_commander.conversions import pose_to_list
import moveit_mod

#add share pyemu
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_planner')
import pyemu


moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules state space', anonymous=True)

robot = moveit_commander.RobotCommander()
ss = moveit_commander.MoveGroupCommander('arm')

# print (move_group.get_planning_frame())

# print (move_group.get_end_effector_link())

# print (robot.get_group_names())

# print (robot.get_current_state())



# joint_goal = move_group.get_current_joint_values()
# joint_goal[0] = 0.907571
# joint_goal[1] = -0.89011
# joint_goal[2] = 0.64577
# joint_goal[3] = 1.37881
# joint_goal[4] = 0.925025
# joint_goal[5] = -1.27409

# path = move_group.plan(joint_goal)

# print (len(path.joint_trajectory.points))
# # print path.joint_trajectory.points
# move_group.go(joint_goal, wait = True)

# move_group.stop()