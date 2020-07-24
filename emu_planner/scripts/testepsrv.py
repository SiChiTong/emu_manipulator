#!/usr/bin/env python3

import sys
import rospy
from emu_planner.srv import *
from sensor_msgs.msg import JointState
from math import pi

i = JointState()
i.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
i.position = [0, 0, pi/2, pi/2, 0, pi/4]

g = JointState()
g.name = i.name
g.position = [1, pi/2, pi/2, 0,0,0]

def planner_client(initialState, goalState):
    print ('Waiting for planner service...')
    rospy.wait_for_service('emu_planner')
    try:
        planner = rospy.ServiceProxy('emu_planner', EmuPlanner)
        resp = planner(initialState, goalState)
        return resp.trajectory
    except rospy.ServiceException as e:
        print ("Service call failed: %s"%e)

print (planner_client(i, g))
