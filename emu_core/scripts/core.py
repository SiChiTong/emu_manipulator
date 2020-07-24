#!/usr/bin/env python3

import numpy as np
from math import sin, cos, tan, pi, ceil
import time
import logging
import threading

#add share pyemu
import sys, time
import copy
import rospkg
import rospy

from std_msgs.msg import String, Float64, Float32, Header
from geometry_msgs.msg import Twist, PoseArray, PoseStamped, Pose
from sensor_msgs.msg import JointState,Image

rospack = rospkg.RosPack()
this_pkg = rospack.get_path('emu_core')
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

import pyemu


rospy.init_node('core')

class Core:
	def __init__(self, _port = '/dev/ttyTHS1', vision = 0):
		self.preconfig_pose = {'home': [0, 0, pi/2, pi/2, 0, -pi/4], 
			'bin_snap': [0, 1.2, -0.05, pi/2-0.05, 0, 0], 
			'tray_left_1': [pi/2, 0.09, 0.1503, 1.6, 0, 0],
			'tray_left_2': [pi/2, 0.09, 0.1503, 1.45, 0, 0],
			'tray_left_3': [pi/2, 0.09, 0.1503, 1.25, 0, 0],
			'tray_right_1': [-pi/2, 0.09, 0.1503, 1.7, 0, 0],
			'tray_right_2': [-pi/2, 0.09, 0.1503, 1.5, 0, 0],
			'tray_right_3': [-pi/2, 0.09, 0.1503, 1.2, 0, 0],
			'zero': [0, 0, 0, 0, 0, 0]}
		self.lock = 0
		self.port = _port
		self.emulator = pyemu.Emuart(self.port)
		self.kin_solver = pyemu.EmuRobot()
		while not self.emulator.established():
			pass

		self.joint_rate = rospy.Rate(5)
		self.joint_msg = JointState()
		self.joint_msg.header.frame_id = "base_link"
		self.joint_msg.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']

		self.__initPublisher()
		self.__initSubscriber()
		if vision: self.__initVision()

		
	def __initVison(self):
		self.vision = pyemu.Vision(debug = False)

	def __initPublisher(self):
		self.emu_log = rospy.Publisher('emu/log', String, queue_size = 20)
		self.joint_states_publisher = rospy.Publisher('emu/joint_states', JointState, queue_size = 20)
		self.bin_pose_publisher = rospy.Publisher('emu/vision/bin_poses',JointState,queue_size = 20)
		self.trash_poses_publisher = rospy.Publisher('emu/vision/trash_poses', PoseArray, queue_size = 20)
		self.left_tray_publisher = rospy.Publisher('emu/vision/left_tray', Image, queue_size = 0,latch=True)
		self.right_tray_publisher = rospy.Publisher('/emu/vision/right_tray', Image, queue_size = 20,latch=True)

	def __initSubscriber(self):
		rospy.Subscriber('emu/jog/configuration', JointState, self.configJogCallback)
		rospy.Subscriber('emu/jog/cartesian', Twist, self.cartesianJogCallback)
		rospy.Subscriber('emu/command', String, self.__execute)
	
	def pickTrashCfg(self,trashMsgList):
		listCfg=[]
		for trashMsg in trashMsgList.poses :
			Hi = np.matrix(np.eye(4))
			x = trashMsg.position.x
			y = trashMsg.position.y
			z = 0.3
			r = pyemu.EmuRobot.quat2rotm([trashMsg.orientation.x,trashMsg.orientation.y,trashMsg.orientation.z,trashMsg.orientation.w])
			Hi[0:3,0:3]=r
			Hi[0:3,3]=np.matrix([[x],[y],[z]])
			trashCfg = self.kin_solver.computeIK(tf = Hi,q_now=[0, 0, pi/2, pi/2, 0, pi/4], method = 'least_dist')
			listCfg.append(trashCfg)
		return listCfg


	def log(self, text, msg_type = None):
		text = str(text)
		msg = String()
		if msg_type == None:
			rospy.loginfo(text)
			head = 'd_'
		elif msg_type == 'warn':
			rospy.logwarn(text)
			head = 'w_'
		elif msg_type == 'error':
			rospy.logerr(text)
			head = 'e_'
		msg.data = head+text
		self.emu_log.publish(msg)

	def getStates(self):
		return self.joint_msg.position

	def notMoving(self, start_pose, goal_pose, tol, joint = None):
		if len(start_pose) == 6:
			pose_now = self.getStates()
			d = [0]*6
			dtm = [0]*6
			for i in range(0,6):
				dtm[i] = abs(abs(goal_pose[i]) - abs(start_pose[i]))
				d[i] = abs(abs(pose_now[i]) - abs(start_pose[i]))
			return 1 if sum(d) < tol*sum(dtm) else 0
		elif len(start_pose) == 1:
			pose_now = self.getStates()[joint-1]
			d = abs(abs(goal_pose) - abs(start_pose))
			dtm = abs(abs(pose_now) - abs(start_pose))
			return 1 if d < tol*dtm else 0
	
	def __execute(self, cmd):
		cmd_object = 'ret = self.'+cmd.data
		cmd_static = 'ret = '+cmd.data
		ret = None
		print (cmd.data)
		try:
			exec(cmd_object)
		except AttributeError:
			exec(cmd_static)
		except Exception as e:
			print (e)
			rospy.logerr(e)
		if ret is None:
				pass
		else:
			rospy.logdebug('Return: '+str(ret))

	def moveTo(self, pose, t, timeout = 60):
		print ('Starting to move to' +  str(pose))
		s_pose = self.getStates()
		self.emulator.moveAbsolute('all', pose, t)
		start_time = time.time()
		while self.notMoving(s_pose, pose, 0.05):
			time.sleep(0.2)
			self.log('1')
			self.emulator.moveAbsolute('all', pose, t)
		return 1
  
	def moveOne(self, joint, goal, t):
		print ('Starting to move '+str(joint)+' to ' +  str(goal))
		s_pose = self.getStates()[joint-1]
		self.emulator.moveAbsolute(joint, goal, t)
		while self.notMoving(s_pose, goal, 0.05):
			time.sleep(0.2)
			self.log('1')
			self.emulator.moveAbsolute(joint, goal, t)
		return 1
  
	def run(self, script):
		script_path = this_pkg+'/scripts/'+script
		script_in = open(script_path)
		data = script_in.read()
		script_in.close()
		try:
			exec(data)
		except Exception as e:
			rospy.logerr('Wrong Input: %s'%e)


	def publishJointStates(self):
		while 1:
			if not self.lock:
				joint_states = self.emulator.requestJointStates()
				if not joint_states == -1:
					joint_states = joint_states[0]
					now = rospy.get_rostime()
					self.joint_msg.header.stamp = now
					self.joint_msg.position = joint_states
					self.joint_states_publisher.publish(self.joint_msg)

	def cartesianJogCallback(self, s_twist):
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

	def configJogCallback(self, state):
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

if __name__ == "__main__":
	emu = Core(vision = 0)
	emu.log('emu core initialized successfully', None)
	rospy.logdebug('emu core initialized successfully')
	joint_pub_thread = threading.Thread(target=emu.publishJointStates, daemon = 1)
	joint_pub_thread.start()
	while not rospy.is_shutdown():
		time.sleep(1)
