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
from moveit_commander.conversions import pose_to_list
import moveit_mod

#add share pyemu
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_planner')
import pyemu


moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules state validator', anonymous=True)


def setBin(scene, order = ['blue', 'yellow', 'green'], z = [0, 0, 0], y = [0.3, 0, -0.3]):
    left_bin_pose = geometry_msgs.msg.Pose()
    left_bin_pose.position.x = 0.5
    left_bin_pose.position.y = y[0]
    left_bin_pose.position.z = z[0]
    left_bin_pose.orientation.w = 1

    mid_bin_pose = geometry_msgs.msg.Pose()
    mid_bin_pose.position.x = 0.5
    mid_bin_pose.position.y = y[1]
    mid_bin_pose.position.z = z[1]
    mid_bin_pose.orientation.w = 1

    right_bin_pose = geometry_msgs.msg.Pose()
    right_bin_pose.position.x = 0.5
    right_bin_pose.position.y = y[2]
    right_bin_pose.position.z = z[2]
    right_bin_pose.orientation.w = 1
    
    poses = [left_bin_pose, mid_bin_pose, right_bin_pose]
    for i in range(3):
        scene.addMesh('{}_bin'.format(order[i]), poses[i], package_path+'/meshes/bin_{}.dae'.format(order[i]))
        if z[i] != 0: scene.addBox('{}_stack'.format(order[i]), 0.4, 0.3, z[i], 0.5+0.4/2, y[i], z[i]/2)

    scene.setColor('blue_bin', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_bin', 1, 1, 0.3, 1)
    scene.setColor('green_bin', 0.3, 1, 0.3, 1)
    scene.setColor('blue_stack', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_stack', 1, 1, 0.3, 1)
    scene.setColor('green_stack', 0.3, 1, 0.3, 1)

sv = moveit_mod.PlanningSceneInterface("base_link")
base_pose = geometry_msgs.msg.Pose()
base_pose.orientation.w = 1
sv.addMesh('work_plane', base_pose, package_path+'/meshes/work_plane.STL')
sv.setColor('work_plane', 0.9, 0.9, 0.9, 1)
setBin(sv, ['yellow', 'blue', 'green'],[0.1, 0, 0.2],[0.32, -0.01, -0.33])
sv.sendColors()