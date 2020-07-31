#!/usr/bin/env python

#ros modueles
import copy
import rospkg
import rospy
import geometry_msgs.msg
from geometry_msgs.msg import PoseArray, Pose
from sensor_msgs.msg import JointState
from tf.transformations import quaternion_from_euler, euler_from_quaternion
from std_msgs.msg import String, Bool

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
# import pyemu


moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules_state_validator', anonymous=True)

b_off = 0.066
inf_off = -0.08

def setBin(scene, order = ['blue', 'yellow', 'green'], z = [0, 0, 0], y = [0.3, 0, -0.3]):
    global b_off
    left_bin_pose = geometry_msgs.msg.Pose()
    left_bin_pose.position.x = 0.5+b_off+inf_off
    left_bin_pose.position.y = y[0]
    left_bin_pose.position.z = z[0]-0.46
    left_bin_pose.orientation.w = 1

    mid_bin_pose = geometry_msgs.msg.Pose()
    mid_bin_pose.position.x = 0.5+b_off+inf_off
    mid_bin_pose.position.y = y[1]
    mid_bin_pose.position.z = z[1]-0.46
    mid_bin_pose.orientation.w = 1

    right_bin_pose = geometry_msgs.msg.Pose()
    right_bin_pose.position.x = 0.5+b_off+inf_off
    right_bin_pose.position.y = y[2]
    right_bin_pose.position.z = z[2]-0.46
    right_bin_pose.orientation.w = 1
    
    poses = [left_bin_pose, mid_bin_pose, right_bin_pose]
    for i in range(3):
        scene.addMesh('{}_bin'.format(order[i]), poses[i], package_path+'/meshes/bin_{}.dae'.format(order[i]))
        if z[i] != 0: scene.addBox('{}_stack'.format(order[i]), 0.4, 0.3, z[i]-0.46, 0.5+b_off+inf_off+0.4/2, y[i], (z[i]-0.46)/2)

    scene.setColor('blue_bin', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_bin', 1, 1, 0.3, 1)
    scene.setColor('green_bin', 0.3, 1, 0.3, 1)
    scene.setColor('blue_stack', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_stack', 1, 1, 0.3, 1)
    scene.setColor('green_stack', 0.3, 1, 0.3, 1)

bottle_size = (0.03, 0.12) #radius, height
can_size = (0.025, 0.1)

def genTrash(scene, name, pose_obj):
    t_stand = str(pose_obj.position.z)[0] 
    t_type = str(pose_obj.position.z)[1] 
    q_s = lambda q : [q.x, q.y, q.z, q.w]
    if t_type == '1':
        yaw = euler_from_quaternion(q_s(pose_obj.orientation))[2]
        if t_stand == '1':
            pose_obj.position.z = bottle_size[0]
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, pi/2, yaw))
        elif t_stand == '2':
            pose_obj.position.z = (bottle_size[1]+0.04)/2
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, 0, 0))
        scene.addCylinder(name, bottle_size[1], bottle_size[0], pose_obj)
        scene.setColor(name, 0.3, 0.64, 1, 1)
    elif t_type == '2':
        yaw = euler_from_quaternion(q_s(pose_obj.orientation))[2]
        if t_stand == '1':
            pose_obj.position.z = can_size[0]
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, pi/2, yaw))
        elif t_stand == '2':
            pose_obj.position.z = (can_size[1]+0.04)/2
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, 0, 0))
        scene.addCylinder(name, can_size[1], can_size[0], pose_obj)
        scene.setColor(name, 1, 0, 0, 1)
    elif t_type == '3':
        scene.addBox(name, 0.02, 0.02, 0.00001, pose_obj.position.x, pose_obj.position.y, 0.00001/2)
        scene.setColor(name, 0, 1, 0, 1)

sv = moveit_mod.PlanningSceneInterface("base_link")    

is_ready = (1, 0)

def trashGenCb(pA):
    print ('Adding trashes')
    for num, pose in enumerate(pA.poses):
        genTrash(sv, 'trash_{}'.format(num), pose)
    sv.sendColors()

def binGenCb(js):
    print ('Adding bins')
    setBin(sv, js.name,js.position,js.velocity)
    sv.sendColors()

def pickCb(bool):
    if bool.data == 1:
        print ('Attach object')
        sv.addBox('grasping_handle', 0.18, 0.04, 0.04, 2, 2, 1)
        sv.attachBox('grasping_handle', 0.18, 0.04, 0.04, 0, 0, 0, 'grasp_frame')
    else:
        print ('Detach object')
        sv.removeAttachedObject('grasping_handle')
        sv.removeCollisionObject('grasping_handle') 

base_pose = Pose()
base_pose.position.x = +b_off
base_pose.orientation.w = 1

sv.addMesh('work_plane', base_pose, package_path+'/meshes/work_plane.STL')
sv.setColor('work_plane', 0.9, 0.9, 0.9, 1)

# setBin(sv, z = [0.6, 0.7, 0.5])

sv.sendColors()

rospy.Subscriber('/emu/vision/trash_poses', PoseArray, trashGenCb)
rospy.Subscriber('/emu/vision/bin_poses', JointState, binGenCb)
rospy.Subscriber('/emu/attach_trash', Bool, pickCb)

rospy.spin()