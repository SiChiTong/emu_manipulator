#!/usr/bin/env python3

#add share pyemu
import sys, time
import copy
import rospkg
import rospy

from std_msgs.msg import String, Float64, Float32
from geometry_msgs.msg import Twist, PoseArray, PoseStamped, Pose
from sensor_msgs.msg import JointState

rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

import pyemu

rospy.init_node('Core')

class Core:
	def __init__(self, _port = '/dev/ttyTHS1'):
		self.port = _port
		self.emulator = pyemu.Emuart(self.port)
		while not self.emulator.established():
			pass

		self.joint_rate = rospy.Rate(5)
		self.joint_msg = JointState()
		self.joint_msg.header.frame_id = "base_link"
		self.joint_msg.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']

		self.emu_log = rospy.Publisher('emu/log', String, queue_size = 20)
		self.joint_states_publisher = rospy.Publisher('emu/joint_states', JointState, queue_size = 20)

		rospy.Subscriber('emu/jog/configuration', JointState, self.configJogCallback)
		rospy.Subscriber('emu/jog/cartesian', Twist, self.cartesianJogCallback)
		rospy.Subscriber('emu/command', Twist, self.__execute)

	def log(self, text, msg_type = None):
		msg = String
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
		cmd = 'ret = et.'+cmd
		try:
			exec(cmd)
			if ret is None:
				pass
			else:
				print ('Return: '+str(ret))
		except:
			print ('Wrong input!')

	def publishJointStates(self):
		joint_states = self.emulator.requestJointStates('simple')
		if not joint_states == -1:
			joint_states = joint_states[0]
			now = rospy.get_rostime()
			self.joint_msg.header.stamp = now
			self.joint_msg.position = joint_states
			self.joint_states_publisher.publish(self.joint_msg)
			self.joint_rate.sleep()

	def cartesianJogCallback(self, s_twist):
		t_ang = s_twist.angular
		t_lin = s_twist.linear
		twist = [t_ang.x, t_ang.y, t_ang.z, t_lin.x, t_lin.y, t_lin.z]
		print (twist)

	def configJogCallback(self, state):
		position_array = [state.position[0], state.position[1], state.position[2], state.position[3], state.position[4], state.position[5]]
		print (position_array)
		

if __name__ == "__main__":
	emu = Core()
	while not rospy.is_shutdown():
		emu.publishJointStates()
