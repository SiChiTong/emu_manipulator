#!/usr/bin/env python

#ros modueles
import copy
import rospkg
import rospy
import geometry_msgs.msg
from geometry_msgs.msg import PoseArray, Pose
from sensor_msgs.msg import JointState
from tf.transformations import quaternion_from_euler, euler_from_quaternion
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
# import pyemu


moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('modules_state_validator', anonymous=True)


def setBin(scene, order = ['blue', 'yellow', 'green'], z = [0, 0, 0], y = [0.3, 0, -0.3]):
    left_bin_pose = geometry_msgs.msg.Pose()
    left_bin_pose.position.x = 0.5
    left_bin_pose.position.y = y[0]
    left_bin_pose.position.z = z[0]-0.46
    left_bin_pose.orientation.w = 1

    mid_bin_pose = geometry_msgs.msg.Pose()
    mid_bin_pose.position.x = 0.5
    mid_bin_pose.position.y = y[1]
    mid_bin_pose.position.z = z[1]-0.46
    mid_bin_pose.orientation.w = 1

    right_bin_pose = geometry_msgs.msg.Pose()
    right_bin_pose.position.x = 0.5
    right_bin_pose.position.y = y[2]
    right_bin_pose.position.z = z[2]-0.46
    right_bin_pose.orientation.w = 1
    
    poses = [left_bin_pose, mid_bin_pose, right_bin_pose]
    for i in range(3):
        scene.addMesh('{}_bin'.format(order[i]), poses[i], package_path+'/meshes/bin_{}.dae'.format(order[i]))
        if z[i] != 0: scene.addBox('{}_stack'.format(order[i]), 0.4, 0.3, z[i]-0.46, 0.5+0.4/2, y[i], (z[i]-0.46)/2)

    scene.setColor('blue_bin', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_bin', 1, 1, 0.3, 1)
    scene.setColor('green_bin', 0.3, 1, 0.3, 1)
    scene.setColor('blue_stack', 0.3, 0.64, 1, 1)
    scene.setColor('yellow_stack', 1, 1, 0.3, 1)
    scene.setColor('green_stack', 0.3, 1, 0.3, 1)

bottle_size = (0.03, 0.12) #radius, height
can_size = (0.025, 0.1)

def gen_trash(scene, name, pose_obj):
    t_stand = str(pose_obj.position.z)[0] 
    t_type = str(pose_obj.position.z)[1] 
    q_s = lambda q : [q.x, q.y, q.z, q.w]
    if t_type == '1':
        yaw = euler_from_quaternion(q_s(pose_obj.orientation))[2]
        if t_stand == '1':
            pose_obj.position.z = bottle_size[0]
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, pi/2, yaw))
        elif t_stand == '2':
            pose_obj.position.z = bottle_size[1]/2
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, 0, 0))
        scene.addCylinder(name, bottle_size[1], bottle_size[0], pose_obj)
        scene.setColor(name, 0.3, 0.64, 1, 1)
    elif t_type == '2':
        yaw = euler_from_quaternion(q_s(pose_obj.orientation))[2]
        if t_stand == '1':
            pose_obj.position.z = can_size[0]
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, pi/2, yaw))
        elif t_stand == '2':
            pose_obj.position.z = can_size[1]/2
            pose_obj.orientation = geometry_msgs.msg.Quaternion(*quaternion_from_euler(0, 0, 0))
        scene.addCylinder(name, can_size[1], can_size[0], pose_obj)
        scene.setColor(name, 1, 0, 0, 1)
    elif t_type == '3':
        scene.addBox(name, 0.05, 0.05, 0.02, pose_obj.position.x, pose_obj.position.y, 0.05/2)
        scene.setColor(name, 0, 1, 0, 1)

sv = moveit_mod.PlanningSceneInterface("base_link")    

is_ready = (1, 0)

def trashGenCb(pA):
    print ('Adding trashes')
    for num, pose in enumerate(pA.poses):
        gen_trash(sv, 'trash_{}'.format(num), pose)
    sv.sendColors()

def binGenCb(js):
    print ('Adding bins')
    setBin(sv, js.name,js.position,js.velocity)
    sv.sendColors()

base_pose = Pose()
base_pose.orientation.w = 1

sv.addMesh('work_plane', base_pose, package_path+'/meshes/work_plane.STL')
sv.setColor('work_plane', 0.9, 0.9, 0.9, 1)


poseList = [[0.10599999999999998, 0.525, 11, -0.004222495939768292, 0.9999910852242827, -6.123179408479028e-17, -2.585533068524967e-19],
[-0.361, 0.5760000000000001, 11, 0.5650443717528625, 0.825060517750312, -5.0520386108288877e-17, 3.4598989062168507e-17],
[-0.03999999999999998, 0.543, 22, 1.0, 0.0, 0.0, 6.123233995736766e-17],
[0.30600000000000005, 0.529, 13, -0.002238052132716429, 0.9999974955581895, -6.123218660453532e-17, -1.3704116903280412e-19],
[-0.07500000000000001, 0.684, 13, -0.3738952804399497, 0.927470926371674, -5.679121506416506e-17, -2.2894482920354318e-17],
[-0.275, 0.651, 13, 0.4103722017889784, 0.9119181191306959, -5.583888028389407e-17, 2.5128050168996203e-17],
[-0.258, 0.544, 13, 0.24973214185491485, 0.9683149577098129, -5.929219067629136e-17, 1.5291683408341713e-17],
[-0.356, 0.663, 13, 0.3411705121299028, 0.9400014264100985, -5.755848690235367e-17, 2.0890668782167435e-17],
[0.10799999999999998, 0.6020000000000001, 13, -0.045283614368823215, 0.9989741709722507, -6.116952604560238e-17, -2.772821669530122e-18]]
trashMsg = PoseArray()
trashMsg.header.frame_id="base_link"
now = rospy.get_rostime()
trashMsg.header.stamp = now
for trash in range(len(poseList)):
    trash_i = Pose()
    trash_i.position.x = poseList[trash][0]
    trash_i.position.y = poseList[trash][1]
    trash_i.position.z = poseList[trash][2]
    trash_i.orientation.x = poseList[trash][3]
    trash_i.orientation.y = poseList[trash][4]
    trash_i.orientation.z = poseList[trash][5]
    trash_i.orientation.w = poseList[trash][6]
    trashMsg.poses.append(trash_i)
setBin(sv, z = [0.6, 0.7, 0.5])
trashGenCb(trashMsg)


sv.sendColors()

rospy.Subscriber('/emu/vision/trash_poses', PoseArray, trashGenCb)
rospy.Subscriber('/emu/vision/bin_poses', JointState, binGenCb)
rospy.spin()