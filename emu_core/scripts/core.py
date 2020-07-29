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
from std_msgs.msg import String, Float64, Float32, Header, UInt8
from geometry_msgs.msg import Twist, PoseArray, PoseStamped, Pose
from sensor_msgs.msg import JointState,Image

rospack = rospkg.RosPack()
this_pkg = rospack.get_path('emu_core')
share_pkg = rospack.get_path('emu_share')
planner_pkg = rospack.get_path('emu_planner')
sys.path.append(share_pkg)
sys.path.append(planner_pkg)
import pyemu
from scripts.collisionCheck import StateValidity


rospy.init_node('core')

class Core:
	def __init__(self, _port = '/dev/ttyTHS1'):
		self.preconfig_pose = {'home': [0, 0, pi/2, pi/2, 0, -pi/4], 
			'bin_snap': [0, 1.2, -0.05, pi/2-0.05, 0, 0], 
			'tray_left_1': [pi/2, 0.09, 0.1503, 1.6, 0, 0],
			'tray_left_2': [pi/2, 0.09, 0.1503, 1.45, 0, 0],
			'tray_left_3': [pi/2, 0.09, 0.1503, 1.25, 0, 0],
			'tray_right_1': [-pi/2, 0.09, 0.1503, 1.7, 0, 0],
			'tray_right_2': [-pi/2, 0.09, 0.1503, 1.5, 0, 0],
			'tray_right_3': [-pi/2, 0.09, 0.1503, 1.2, 0, 0],
			'zero': [0, 0, 0, 0, 0, 0]}
		self.offset = {'bottle': (0, 0.033, -0.1205), 
				'can': (0, 0.038, -0.1205), 
				'snack': (0, 0.0923, -0.1602)}
		self.lock = 0
		self.port = _port
		self.emulator = pyemu.Emuart(self.port)
		self.kin_solver = pyemu.EmuRobot()
		self.sv = StateValidity()
		while not self.emulator.established():
			pass
		self.joint_rate = rospy.Rate(5)
		self.joint_msg = JointState()
		self.joint_msg.header.frame_id = "base_link"
		self.joint_msg.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
		self.status1 = UInt8()
		self.status2 = UInt8()

		self.__initPublisher()
		self.__initSubscriber()
		# self.vision = pyemu.Vision(debug = False)
		self.log('emuVision initialized successfully.')

	def __initPublisher(self):
		self.emu_log = rospy.Publisher('emu/log', String, queue_size = 20)
		self.status1_publisher = rospy.Publisher('emu/status1', UInt8, queue_size = 10)
		self.status2_publisher = rospy.Publisher('emu/status2', UInt8, queue_size = 10)
		self.joint_states_publisher = rospy.Publisher('emu/joint_states', JointState, queue_size = 20)
		self.bin_poses_publisher = rospy.Publisher('emu/vision/bin_poses',JointState,queue_size = 20, latch=True)
		self.trash_poses_publisher = rospy.Publisher('emu/vision/trash_poses', PoseArray, queue_size = 20, latch=True)
		self.left_tray_publisher = rospy.Publisher('emu/vision/left_tray', Image, queue_size = 0,latch=True)
		self.right_tray_publisher = rospy.Publisher('/emu/vision/right_tray', Image, queue_size = 20,latch=True)

	def __initSubscriber(self):
		rospy.Subscriber('emu/jog/configuration', JointState, self.configJogCallback)
		rospy.Subscriber('emu/jog/cartesian', Twist, self.cartesianJogCallback)
		rospy.Subscriber('emu/command', String, self.__execute)
	
	def isValid(self, pose):
		return self.sv.checkCollision(list(pose))

	def pickTrashCfg(self,trashMsgList):
		listCfg=[]
		for trashMsg in trashMsgList.poses :
			
			trashCfg = self.kin_solver.computeIK(pose = trashMsg,q_now=[0, 0, pi/2, pi/2, 0, pi/4], method = 'least_dist')
			listCfg.append(trashCfg)
		return listCfg

	def log(self, text, msg_type = None):
		text = str(text)
		msg = String()
		head = ''
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

	def getStatus(self):
		return self.status1.data, self.status2.data

	def notMoving(self, start_pose, goal_pose, tol, joint = None):
		if type(start_pose) == list:
			pose_now = self.getStates()
			d = [0,0,0,0,0,0]
			dtm = [0,0,0,0,0,0]
			for i in range(0,6):
				dtm[i] = abs(abs(goal_pose[i]) - abs(start_pose[i]))
				d[i] = abs(abs(pose_now[i]) - abs(start_pose[i]))
			# print (d, dtm)
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

	def moveOne(self, joint, goal, t, relative = 0, blocking = 0, timeout = 30):
		self.log('Moving '+str(joint)+' to ' +  str(goal))
		s_pose = self.getStates()[joint-1]
		if relative:
			self.emulator.moveRelative(joint, goal, t)
		else:
			self.emulator.moveAbsolute(joint, goal, t)
		st_time = time.time()
		time.sleep(0.4)
		while self.notMoving(s_pose, goal, 0.03, joint):
			self.log('Not moving..', 'warn')
			if relative:
				self.emulator.moveRelative(joint, goal, t)
			else:
				self.emulator.moveAbsolute(joint, goal, t)
			time.sleep(0.2)
			if time.time()-st_time > timeout: 
				self.log('MoveOne command timeout!', 'error')
				break
		if blocking: time.sleep(t)
		self.log('Move '+str(joint)+' to ' +  str(goal)+' successfully!')
		return 1

	def moveTo(self, pose, t, relative = 0, blocking = 0, timeout = 30):
		self.log('Moving to ' +  str(pose))
		s_pose = self.getStates()
		if relative:
			self.emulator.moveRelative('all', pose, t)
		else:
			self.emulator.moveAbsolute('all', pose, t)
		st_time = time.time()
		time.sleep(0.4)
		while self.notMoving(s_pose, pose, 0.03):
			self.log('Not moving..', 'warn')
			if relative:
				self.emulator.moveRelative('all', pose, t)
			else:
				self.emulator.moveAbsolute('all', pose, t)
			time.sleep(0.2)
			if time.time()-st_time > timeout: 
				self.log('MoveTo command timeout!', 'error')
				break
		if blocking: time.sleep(t)
		self.log('Move to ' +  str(pose)+' successfully!')
		return 1
	
	def plan(self, initialState, goalState):
		self.log('Waiting for planner service...')
		rospy.wait_for_service('emu_planner_server')
		try:
			planner = rospy.ServiceProxy('emu_planner_server', EmuPlanner)
			resp = planner(initialState, goalState)
			return resp.trajectory
		except rospy.ServiceException as e:
			self.log("Service call failed: %s"%e)

	def executeTrajectory(self, joint_trajectory, blocking = 0, timeout = 30):
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
		st_time = time.time()
		self.log('Trajectory vector: '+str(p)+'\n'+str(v)+'\n'+str(t))
		self.emulator.sendViaPoints(p, v, t)
		s_pose = self.getStates()
		while self.notMoving(s_pose, first_vias, 0.02):
			time.sleep(0.2)
			self.log('Not moving..', 'warn')
			self.emulator.sendViaPoints(p, v, t)
			if time.time()-st_time > timeout: 
				self.log('Execute trajectory command timeout!', 'error')
				break
		if blocking: time.sleep(sum(t))
		self.log('Trajectory is successfully executed!')
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

	def grip(self, method = 'jaw', timeout = 20):
		self.log('Gripping...')
		self.emulator.grip(1)
		st_time = time.time()
		time.sleep(0.2)
		while not (self.getStatus()[0] & 0b00000010)>>1:
			self.log('Not gripping..', 'warn')
			self.emulator.grip(1)
			time.sleep(0.2)
			if time.time()-st_time > timeout: 
				self.log('Grip command timeout!', 'error')
				break
		self.log('Grip successfully!')
		return 1

	def setOD(self, channel, state, timeout = 20):
		self.log('Setting OD{} to {}'.format(channel, state))
		self.emulator.setOD(channel, state)
		st_time = time.time()
		time.sleep(0.2)
		while (not (self.getStatus()[1] & 128>>(channel-1))) if state else (self.getStatus()[1] & 128>>(channel-1)):
			self.log('Not setting..', 'warn')
			self.emulator.setOD(channel, state)
			time.sleep(0.2)
			if time.time()-st_time > timeout: 
				self.log('SetOD command timeout!', 'error')
				break
		self.log('Set OD{} to {} successfully!'.format(channel, state))
		return 1

	def release(self, method = 'jaw', timeout = 6):
		self.log('Releasing...')
		self.emulator.grip(0)
		st_time = time.time()
		time.sleep(0.2)
		while (self.getStatus()[0] & 0b00000010)>>1:
			self.log('Not releasing..', 'warn')
			self.emulator.grip(0)
			time.sleep(0.2)
			if time.time()-st_time > timeout: 
				self.log('Release command timeout!', 'error')
				break
		self.log('Released successfully!')
		return 1


	def publishJointStates(self):
		while 1:
			if not self.lock:
				joint_states = self.emulator.requestJointStates()
				if not joint_states == -1:
					self.status1.data = joint_states[1][0]
					self.status2.data = joint_states[1][1]
					joint_states = joint_states[0]
					now = rospy.get_rostime()
					self.joint_msg.header.stamp = now
					self.joint_msg.position = joint_states
					self.joint_states_publisher.publish(self.joint_msg)
					time.sleep(0.025)
					self.status1_publisher.publish(self.status1)
					time.sleep(0.025)
					self.status2_publisher.publish(self.status2)

	def cartesianJogCallback(self, s_twist):
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
		# print (dq)
		self.log('Input twist: '+str(twist))
		time.sleep(0.05)
		self.log('Output joint increment: '+str(dq))
		# self.emulator.moveRelative('all', dq, 5)
		self.moveTo(dq, t = 3, relative = 1)

	def configJogCallback(self, state):
		position_array = state.position
		jointNum = None
		for n,i in enumerate(position_array):
			if i == 0:
				pass
			else:
				jointNum = n+1
				increment = i	
		self.log('Input joint increments: '+str(position_array))
		# self.emulator.moveRelative(jointNum, increment, 3)
		if jointNum: self.moveOne(joint = jointNum, goal = increment, t = 3, relative = 1)

	def getValidPath(self, path_array, q_now = None):
		q_now = self.getStates() if q_now is None else q_now
		vailid_path = []
		for i in path_array:
			if self.isValid(i):
				vailid_path.append(list(i))
		if vailid_path is []: 
			self.log('No vaild config found!')
		else:
			self.log('Valid Path: '+str(vailid_path))
			soln = self.kin_solver.leastDist(vailid_path, q_now)
		self.log("Valid least distance solution: "+str(soln))
		return soln

	@staticmethod
	def toBin(binMsg, binIdx, isSnack = 0, x_offset = 0.45):
		pose = Pose()
		pose.position.x = x_offset
		pose.position.y = binMsg.velocity[binIdx]
		if 0.56-x_offset >= 0:
			pose.position.z = binMsg.position[binIdx]+(0.56-x_offset)*sin(0.5236)
		else:
			pose.position.z = binMsg.position[binIdx]
		
		if isSnack:
			pose.orientation.x = 0.86727
			pose.orientation.y = 3e-7
			pose.orientation.z = 0.49783
			pose.orientation.w = 2e-7
		else:
			if binIdx == 0:
				pose.orientation.x = 0.24312
				pose.orientation.y = 0.3325
				pose.orientation.z = 0.9073
				pose.orientation.w = -0.08874
			elif binIdx == 1:
				# pose.position.x = x_offset -0.05
				# pose.position.y = binMsg.velocity[binIdx]
				# pose.position.z = binMsg.position[binIdx]+(0.56-0.4)*sin(0.5236)
				pose.orientation.x = 0.2588
				pose.orientation.y = 1e-7
				pose.orientation.z = 0.9659
				pose.orientation.w = 3e-7
			elif binIdx == 2:
				pose.orientation.x = 0.24312
				pose.orientation.y = -0.3325
				pose.orientation.z = 0.9073
				pose.orientation.w = 0.08874
		return pose

	def pickTrash(self, trash, z_offset = 0.25):
		target = Pose()
		target.position.x = trash.position.x
		target.position.y = trash.position.y
		target.position.z = z_offset
		
		t_stand = str(trash.position.z)[0] 
		t_type = str(trash.position.z)[1] 

		if not t_type == '3':
			t_name = 'bottle' if t_type is '1' else 'can'
			if t_stand == '1':
				target.orientation = trash.orientation
				config_list = self.kin_solver.computeIK(target, offset = self.offset[t_name])
			elif t_stand == '2':
				target.orientation.x = 0
				target.orientation.y = -0.70709
				target.orientation.z = 0
				target.orientation.w = 0.7071232
				config_list = self.kin_solver.computeIKranged(target, offset = self.offset[t_name], lb = (0, 0, -pi), ub = (0, 0, pi))
		else:
			t_name = 'snack'
			target.orientation = trash.orientation
			config_list = self.kin_solver.computeIKranged(target, offset = self.offset[t_name], lb = (0, 0, -pi), ub = (0, 0, pi))

		return config_list

	def placeTrash(self, trash, binMsg, x_offset = 0.45):
		t_stand = str(trash.position.z)[0] 
		t_type = str(trash.position.z)[1] 

		if not t_type == '3':
			t_name = 'bottle' if t_type is '1' else 'can'
			bN = 'yellow' if t_name is 'bottle' else 'green'
			iS = 0
		else:
			t_name = 'snack'
			bN = 'blue'
			iS = 1
		bI = binMsg.name.index(bN)
		
		config_list = self.kin_solver.computeIK(Core.toBin(binMsg, binIdx = bI, isSnack = iS), offset = self.offset[t_name])

		return config_list

if __name__ == "__main__":
	emu = Core()
	emu.log('emu core initialized successfully', None)
	joint_pub_thread = threading.Thread(target=emu.publishJointStates, daemon = 1)
	joint_pub_thread.start()
	while not rospy.is_shutdown():
		time.sleep(1)
