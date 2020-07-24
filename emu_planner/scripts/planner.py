#!/usr/bin/env python

#ros modueles
import copy
import rospkg
import rospy
import geometry_msgs.msg
from std_msgs.msg import Header
from sensor_msgs.msg import JointState
# from tf.transformations import quaternion_from_euler
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

from emu_planner.srv import EmuPlanner, EmuPlannerResponse 

#add share pyemu
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_planner')
# import pyemu

moveit_commander.roscpp_initialize(sys.argv)

NAME = 'emu_planner_server'

from emu_planner.srv import *




robot = moveit_commander.RobotCommander()
ss = moveit_commander.MoveGroupCommander('arm')
sv = StateValidity()


def planner_handle(request):
	global ss
	# request.initialState = JointState()
	# request.initialState.header = Header()
	# request.initialState.header.stamp = rospy.Time.now()
	# request.initialState.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
	# request.initialState.position = start_state
	robot_initial_state = RobotState()
	robot_initial_state.joint_state = request.initialState
	ss.set_start_state(robot_initial_state)
	path = ss.plan(request.goalState.position)
	# p,v,t = [],[],[]
	# lt = 0
	# for point in path.joint_trajectory.points:
	# 	p.append(point.positions)
	# 	v.append(point.velocities)
	# 	t_now = point.time_from_start.secs+(1e-9*point.time_from_start.nsecs)
	# 	t.append(t_now-lt)
	# 	lt = t_now
	return EmuPlannerResponse(path.joint_trajectory)

def planner_server():
	rospy.init_node('emu_sampling_planner', anonymous=True)
	s = rospy.Service('emu_planner', EmuPlanner,planner_handle)
	print ('Planner is readey to plan.')
	rospy.spin()


if __name__ == '__main__':
	planner_server()