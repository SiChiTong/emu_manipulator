#!/usr/bin/env python

#ros modueles
import copy
import rospkg
import rospy
import geometry_msgs.msg
from std_msgs.msg import Header
from sensor_msgs.msg import JointState
from tf.transformations import quaternion_from_euler
from std_msgs.msg import String

#python modules
import sys
import os
from math import pi, cos, sin
import time

#moveit modules
import moveit_commander
from moveit_msgs.msg import RobotState
import moveit_msgs.srv
from moveit_commander.conversions import pose_to_list
import moveit_mod

from collisionCheck import StateValidity

#add share pyemu
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_planner')
# import pyemu





moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules_state_space', anonymous=True)

NAME = 'emu_planner_server'

from emu_planner.srv import *




robot = moveit_commander.RobotCommander()
ss = moveit_commander.MoveGroupCommander('arm')
sv = StateValidity()


def plan(initialState, goalState):
	global ss
	initial_joint_state = JointState()
	initial_joint_state.header = Header()
	initial_joint_state.header.stamp = rospy.Time.now()
	initial_joint_state.name = self.joint_msg.name
	initial_joint_state.position = start_state
	robot_initial_state = RobotState()
	robot_initial_state.joint_state = initial_joint_state
	ss.set_start_state(robot_initial_state)
	path = ss.plan(goal_state)
	p,v,t = [],[],[]
	lt = 0
	for point in path.joint_trajectory.points:
		p.append(point.positions)
		v.append(point.velocities)
		t_now = point.time_from_start.secs+(1e-9*point.time_from_start.nsecs)
		t.append(t_now-lt)
		lt = t_now
	return p,v,t

