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

from collisionCheck import StateValidity

#add share pyemu
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_planner')
# import pyemu


moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules_state_space', anonymous=True)

robot = moveit_commander.RobotCommander()
ss = moveit_commander.MoveGroupCommander('arm')
sv = StateValidity()

joint_goal = ss.get_current_joint_values()
joint_goal[0] = -0.907571
joint_goal[1] = -1.25
joint_goal[2] = 0.94
joint_goal[3] = -0.907
joint_goal[4] = -0.768
joint_goal[5] = -1.309

path = ss.plan(joint_goal)

# print (path)
print (len(path.joint_trajectory.points))
p,v,t = [],[],[]
lt = 0
for point in path.joint_trajectory.points:
    p.append(point.positions)
    v.append(point.velocities)
    t_now = point.time_from_start.secs+(1e-9*point.time_from_start.nsecs)
    t.append(t_now-lt)
    lt = t_now
    print (lt)
print (p,v, t)
# path_len = len(path.joint_trajectory.points)
# simple_path = [path.joint_trajectory.points[0].positions]
# last_point = path.joint_trajectory.points[0].positions
# for point in path.joint_trajectory.points[1:path_len]:
#     if sv.checkCollision(point.positions):
#         pass
#     else:
#         simple_path.append(last_point)
#     last_point = point.positions

# simple_path.append(path.joint_trajectory.points[path_len-1].positions)

# print(simple_path)

