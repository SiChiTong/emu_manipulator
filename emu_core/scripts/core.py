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

from emu_planner.srv import *
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
		self.log('emuVision initialized successfully.')

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
			
			trashCfg = self.kin_solver.computeIK(pose = trashMsg,q_now=[0, 0, pi/2, pi/2, 0, pi/4], method = 'least_dist')
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
		if type(start_pose) == list:
			pose_now = self.getStates()
			d = [0,0,0,0,0,0]
			dtm = [0,0,0,0,0,0]
			for i in range(0,6):
				dtm[i] = abs(abs(goal_pose[i]) - abs(start_pose[i]))
				d[i] = abs(abs(pose_now[i]) - abs(start_pose[i]))
			return 1 if sum(d) < tol*sum(dtm) else 0
		else:
			pose_now = self.getStates()[joint-1]
			dtm = abs(abs(goal_pose) - abs(start_pose))
			d = abs(abs(pose_now) - abs(start_pose))
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
			self.log('%s'%e, 'error')
		if ret is None:
				pass
		else:
			self.log('Return: '+str(ret))

	def moveOne(self, joint, goal, t, relative = 0, blocking = 0):
		self.log('Moving '+str(joint)+' to ' +  str(goal))
		s_pose = self.getStates()[joint-1]
		if relative:
			self.emulator.moveAbsolute(joint, goal, t)
		else:
			self.emulator.moveRelative(joint, goal, t)
		while self.notMoving(s_pose, goal, 0.02, joint):
			time.sleep(0.2)
			self.log('Not moving..')
			if relative:
				self.emulator.moveAbsolute(joint, goal, t)
			else:
				self.emulator.moveRelative(joint, goal, t)
		if blocking: time.sleep(t)
		return 1

	def moveTo(self, pose, t, relative = 0, blocking = 0):
		self.log('Moving to ' +  str(pose))
		s_pose = self.getStates()
		if relative:
			self.emulator.moveRelative('all', pose, t)
		else:
			self.emulator.moveAbsolute('all', pose, t)
		while self.notMoving(s_pose, pose, 0.05):
			time.sleep(0.2)
			self.log('Not moving..')
			if relative:
				self.emulator.moveRelative('all', pose, t)
			else:
				self.emulator.moveAbsolute('all', pose, t)
		if blocking: time.sleep(t)
		return 1
	
	def plan(self, initialState, goalState):
		self.log('Waiting for planner service...')
		rospy.wait_for_service('emu_planner')
		try:
			planner = rospy.ServiceProxy('emu_planner', EmuPlanner)
			resp = planner(initialState, goalState)
			return resp.trajectory
		except rospy.ServiceException as e:
			self.log("Service call failed: %s"%e)

	def executeTrajectory(self, joint_trajectory):
		p,v,t = [[],[],[],[],[],[]],[[],[],[],[],[],[]],[]
		lt = 0
		first_vias = joint_trajectory.points[1].positions
		# tend = 
		for num,point in enumerate(joint_trajectory.points[1:len(joint_trajectory.points)]):
			# print (point.positions)
			for i in range(6):
				# print (point.positions[i])
				p[i].append(point.positions[i])
				v[i].append(point.velocities[i])
			t_now = point.time_from_start.secs+(1e-9*point.time_from_start.nsecs)
			t.append(t_now-lt)
			lt = t_now
		self.log('Trajectory vector: '+str(p)+' '+str(v)+' '+str(t))
		self.emulator.sendViaPoints(p, v, t)
		s_pose = self.getStates()
		while self.notMoving(s_pose, first_vias, 0.02):
			time.sleep(0.2)
			self.log('Not moving..')
			self.emulator.sendViaPoints(p, v, t)
		# if blocking: time.sleep(t)
		return 1

	def run(self, script):
		script_path = this_pkg+'/scripts/'+script
		emu.log('Running script at '+script_path)
		script_in = open(script_path)
		data = script_in.read()
		script_in.close()
		try:
			exec(data)
		except Exception as e:
			self.log('Wrong Input: %s'%e, 'error')


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
		qk = self.getStates()
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
		# self.emulator.moveRelative('all', dq, 5)
		self.moveTo(dq, 3, 1)

	def configJogCallback(self, state):
		time.sleep(0.01)
		position_array = state.position
		for n,i in enumerate(position_array):
			if i == 0:
				pass
			else:
				jointNum = n+1
				increment = i	
		self.log('Input joint increments: '+str(position_array))
		# self.emulator.moveRelative(jointNum, increment, 3)
		self.moveOne(jointNum, increment, 3, 1)

if __name__ == "__main__":
	emu = Core(vision = 0)
	emu.log('emu core initialized successfully', None)
	joint_pub_thread = threading.Thread(target=emu.publishJointStates, daemon = 1)
	joint_pub_thread.start()
	while not rospy.is_shutdown():
		time.sleep(1)
