#!/usr/bin/env python3

import numpy as np
from math import sin, cos, tan, pi
import time
import logging
import threading

#add share pyemu
import sys, time
import copy
import rospkg
import rospy

from std_msgs.msg import String, Float64, Float32
from geometry_msgs.msg import Twist, PoseArray, PoseStamped, Pose
from sensor_msgs.msg import JointState,Image

rospack = rospkg.RosPack()
this_pkg = rospack.get_path('emu_core')
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

import pyemu


rospy.init_node('core')


class Core:
	def __init__(self, _port = '/dev/ttyTHS1'):
		self.preconfig_pose = {'home': [0, 0, pi/2, pi/2, 0, -pi/4], 
			'bin_snap': [0, 1.2, -0.02, pi/2, 0, 0], 
			'tray_left_1': [pi/2, 0.09, 0.1503, (pi/2)+0.2, 0, 0],
			'tray_left_2': [pi/2, 0.09, 0.1503, pi/2, 0, 0],
			'tray_left_3': [pi/2, 0.09, 0.1503, (pi/2)-0.2, 0, 0],
			'tray_right_1': [-pi/2, 0.09, 0.1503, (pi/2)+0.2, 0, 0],
			'tray_right_2': [-pi/2, 0.09, 0.1503, pi/2, 0, 0],
			'tray_right_3': [-pi/2, 0.09, 0.1503, (pi/2)-0.2, 0, 0],
			'zero': [0, 0, 0, 0, 0, 0]}
		self.lock = 0
		self.vision = pyemu.Vision(debug = False)
		self.port = _port
		self.emulator = pyemu.Emuart(self.port)
		self.kin_solver = pyemu.EmuRobot()
		while not self.emulator.established():
			pass

		self.joint_rate = rospy.Rate(3)
		self.joint_msg = JointState()
		self.joint_msg.header.frame_id = "base_link"
		self.joint_msg.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']

		self.emu_log = rospy.Publisher('emu/log', String, queue_size = 20)
		self.joint_states_publisher = rospy.Publisher('emu/joint_states', JointState, queue_size = 20)
		self.bin_pose_publisher = rospy.Publisher('emu/vision/bin_poses',JointState,queue_size = 20)
		self.trash_poses_publisher = rospy.Publisher('emu/vision/trash_poses', PoseArray, queue_size = 20)
		self.left_tray_publisher = rospy.Publisher('emu/vision/left_tray', Image, queue_size = 0,latch=True)
		self.right_tray_publisher = rospy.Publisher('/emu/vision/right_tray', Image, queue_size = 20,latch=True)
  
		rospy.Subscriber('emu/jog/configuration', JointState, self.configJogCallback)
		rospy.Subscriber('emu/jog/cartesian', Twist, self.cartesianJogCallback)
		rospy.Subscriber('emu/command', String, self.__execute)
	
	# def initVison(self):
	# 	self.vision = pyemu.Vision(debug = False)
  
	def log(self, text, msg_type = None):
		msg = String()
		if msg_type == None:
			rospy.logdebug(text)
			head = 'd_'
		elif msg_type == 'warn':
			rospy.logwarn(text)
			head = 'w_'
		elif msg_type == 'error':
			rospy.logerr(text)
			head = 'e_'
		msg.data = head+text
		self.emu_log.publish(msg)

	def __execute(self, cmd):
		cmd_object = 'ret = self.'+cmd.data
		cmd_static = 'ret = '+cmd.data
		ret = None
		print (cmd.data)
		try:
			exec(cmd_object)
			if ret is None:
				pass
			else:
				rospy.logdebug('Return: '+str(ret))
		except AttributeError:
			exec(cmd_static)
		except Exception as e:
			print (e)
			rospy.logerr('Wrong Input: '+e)
		if ret is None:
				pass
		else:
			rospy.logdebug('Return: '+str(ret))

	def moveTo(self, pose, t):
		self.lock = 1
		time.sleep(0.1)
		self.emulator.moveAbsolute('all', pose, t)
		time.sleep(0.1)
		self.emulator.moveAbsolute('all', pose, t)
		time.sleep(0.1)
		self.emulator.moveAbsolute('all', pose, t)
		time.sleep(0.1)
		# print (self.emulator.read())
		self.lock = 0
  
	def moveOne(self, joint, goal, t):
		self.lock = 1
		time.sleep(0.1)
		self.emulator.moveAbsolute(joint, goal, t)
		time.sleep(0.1)
		self.emulator.moveAbsolute(joint, goal, t)
		time.sleep(0.1)
		self.emulator.moveAbsolute(joint, goal, t)
		time.sleep(0.1)
		# print (self.emulator.read())
		self.lock = 0
 
	def run(self, script):
		self.log('Hello There!')
		self.moveTo(self.preconfig_pose['bin_snap'],8)
		time.sleep(11)
		self.log('Start snap bin')

		self.vision.snapBinImg()
		self.log('Snap bin finish')
		self.log('find bin pose')
		binMsg = self.vision.getBin()
		self.bin_pose_publisher.publish(binMsg)
		self.log('Bin position: Done!')

		self.log('Moving to left tray 1')
		self.moveTo(self.preconfig_pose['tray_left_1'],20)
		time.sleep(23)
		self.log('snap pano left 1')
		self.vision.snapPano('l')
		self.log('Moving to left tray 2')
		self.moveOne(4, pi/2, 3)
		time.sleep(3.5)
		self.log('snap pano left 2')
		self.vision.snapPano('l')
		self.log('Moving to left tray 3')
		self.moveOne(4, (pi/2)-0.2, 3)
		time.sleep(3.5)
		self.log('snap pano left 3')
		self.vision.snapPano('l')
		self.log('start Predict')
		leftTrashMsg,leftTrayImg,leftTrashNum = self.vision.findTrash('l',panomode=0,persmode=0)
		self.log('Left tray: Done!')

		self.log('Moving to right tray 1')
		self.moveTo(self.preconfig_pose['tray_right_1'],10)
		time.sleep(13)
		self.log('snap pano right 1')
		self.vision.snapPano('r')
		self.log('Moving to right tray 2')
		self.moveOne(4, pi/2, 3)
		time.sleep(3.5)
		self.log('snap pano right 2')
		self.vision.snapPano('r')
		self.log('Moving to right tray 3')
		self.moveOne(4, (pi/2)-0.2, 3)
		time.sleep(3.5)
		self.log('snap pano right 3')
  
		self.vision.snapPano('r')
		self.log('start Predict')

		rightTrashMsg,rightTrayImg,rightTrashNum = self.vision.findTrash('r',panomode=0,persmode=0)
		self.log('Right tray: Done!')
  
		if leftTrashNum + rightTrashNum == 0:
			pass
		else:
			if leftTrashNum != 0:
				self.left_tray_publisher.publish(leftTrayImg)
				self.trash_poses_publisher.publish(leftTrashMsg)

				time.sleep(0.1)
			else:
				self.left_tray_publisher.publish(leftTrayImg)
				pass
			time.sleep(0.1)
			if rightTrashNum != 0:
				self.right_tray_publisher.publish(rightTrayImg)
				self.trash_poses_publisher.publish(rightTrashMsg)		

				time.sleep(0.1)
			else:
				self.right_tray_publisher.publish(rightTrayImg)
		


		time.sleep(1)
		print ('Moving to home')
		self.moveTo(self.preconfig_pose['home'], 15)
		time.sleep(16)
		print ('Done!')
		
		# script_path = this_pkg+'/scripts/'+script
		# script_in = open(script_path)
		# data = script_in.read()
		# script_in.close()
		# cmd_list = data.split('\n')
		# ret = None
		# for cmd in cmd_list:
		# 	cmd_object = 'ret = self.'+cmd
		# 	cmd_static = 'ret = '+cmd
		# 	try:
		# 		exec(cmd_object)
		# 		if ret is None:
		# 			pass
		# 		else:
		# 			rospy.logdebug('Return: '+str(ret))
		# 	except AttributeError:
		# 		exec(cmd_static)
		# 	except Exception as e:
		# 		print (e)
		# 		rospy.logerr('Wrong Input: '+e)
		# 	if ret is None:
		# 			pass
		# 	else:
		# 		rospy.logdebug('Return: '+str(ret))


	def publishJointStates(self):
		while 1:
			if not self.lock:
				joint_states = self.emulator.requestJointStates('simple')
				if not joint_states == -1:
					joint_states = joint_states[0]
					now = rospy.get_rostime()
					self.joint_msg.header.stamp = now
					self.joint_msg.position = joint_states
					self.joint_states_publisher.publish(self.joint_msg)
					self.joint_rate.sleep()

	def cartesianJogCallback(self, s_twist):
		self.lock = 1
		time.sleep(0.01)
		t_ang = s_twist.angular
		t_lin = s_twist.linear
		twist = [t_ang.x, t_ang.y, t_ang.z, t_lin.x, t_lin.y, t_lin.z]
		qk = self.joint_msg.position
		dq = []
		if not qk == []:
			dq =  list(np.array(self.kin_solver.getCartesianJog(np.array(qk), np.array(twist), 6)).reshape(6))
		else:
			print ('Joint states is not published yet!')
			self.log('Joint states is not published yet!', 'error')
		print (dq)
		self.log('Input twist: '+str(twist))
		time.sleep(0.05)
		self.log('Output joint increment: '+str(dq))
		self.emulator.moveRelative('all', dq, 5)
		self.lock = 0

	def configJogCallback(self, state):
		self.lock = 1
		time.sleep(0.01)
		position_array = [state.position[0], state.position[1], state.position[2], state.position[3], state.position[4], state.position[5]]
		for n,i in enumerate(position_array):
			if i == 0:
				pass
			else:
				jointNum = n+1
				increment = i	
		print (jointNum, increment)
		self.log('Input joint increments: '+str(position_array))
		self.emulator.moveRelative(jointNum, increment, 3)
		self.lock = 0

if __name__ == "__main__":
	emu = Core()
	# emu.initVison()
	emu.log('emu core initialized successfully', None)
	rospy.logdebug('emu core initialized successfully')
	joint_pub_thread = threading.Thread(target=emu.publishJointStates, daemon = 1)
	joint_pub_thread.start()
	while not rospy.is_shutdown():
		# print ('in while')
		time.sleep(1)
