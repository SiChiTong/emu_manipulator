#!/usr/bin/env python

import sys
import os
import copy
import rospkg
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from tf.transformations import quaternion_from_euler
from math import pi
import time
from std_msgs.msg import String
from moveit_commander.conversions import pose_to_list
import moveit_python

rospack = rospkg.RosPack()

package_path = rospack.get_path('emu_planner')
print (package_path)

moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_test', anonymous=True)

robot = moveit_commander.RobotCommander()
move_group = moveit_commander.MoveGroupCommander('arm')

planning_frame = move_group.get_planning_frame()
print "============ Planning frame: %s" % planning_frame

# We can also print the name of the end-effector link for this group:
eef_link = move_group.get_end_effector_link()
print "============ End effector link: %s" % eef_link

# We can get a list of all the groups in the robot:
group_names = robot.get_group_names()
print "============ Available Planning Groups:", robot.get_group_names()

# Sometimes for debugging it is useful to print the entire state of the
# robot:
print "============ Printing robot state"
print robot.get_current_state()
print ""

bin_pose = geometry_msgs.msg.Pose()
bin_pose.position.x = 0.5
bin_pose.orientation.w = 1
sv = moveit_python.PlanningSceneInterface("base_link")
# sv.addBox("my_box", 0.1, 1, 2, 0.6, 0, 0.5)
sv.addMesh('bin', bin_pose, package_path+'/meshes/bin_blue.dae')

joint_goal = move_group.get_current_joint_values()
joint_goal[0] = 0.907571
joint_goal[1] = -0.89011
joint_goal[2] = 0.64577
joint_goal[3] = 1.37881
joint_goal[4] = 0.925025
joint_goal[5] = -1.27409

path = move_group.plan(joint_goal)

print len(path.joint_trajectory.points)
# print path.joint_trajectory.points
move_group.go(joint_goal, wait = True)

move_group.stop()