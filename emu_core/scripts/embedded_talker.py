#!/usr/bin/env python

import rospy
import pyemu
import time
import numpy as np
import math
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64

rospy.init_node('embedded_talker')

emu_llc = pyemu.EmuRobot()

emu_joint_states = 0

js = rospy.Publisher('/emu/joint_states', JointState, queue_size=10)


def getCubicCoeff(qi, qf, vi, vf, Ti):
    return [qi, vi, 3*(qf-qi)/Ti**2-(vf+2*vi)/Ti, -2*(qf-qi)/Ti**3+(vf+vi)/Ti**2]

def cubicGen(qr, qdr, T, Tk, mode = 'constant'):
    cumsum = lambda ls : [sum(ls[0:x:1]) for x in range(1, len(ls)+1)] 
    Tc = cumsum(T)
    T_prev = 0
    q = np.array([[], [], []])
    subA = []
    for i in range(0, len(T)):
        ci = getCubicCoeff(qr[i], qr[i+1], qdr[i], qdr[i+1], T[i])
        sT = Tk if mode is 'constant' else T[i]/Tk 
        t_start = T_prev
        t_end = Tc[i]-sT
        T_prev = t_end+sT 
        subTvec = np.linspace(t_start,t_end,math.floor(t_end/sT))
        tau = subTvec-t_start;
        subTraj = np.array([ci[0]+ci[1]*tau+ci[2]*tau**2+ci[3]*tau**3, 
                            ci[1]+2*ci[2]*tau+3*ci[3]*tau**2, 
                            2*ci[2]+6*ci[3]*tau])
        q = np.concatenate((q, subTraj),axis=1)
        subA.append(subTraj[2][0]);
        subA.append(subTraj[2][len(subTraj[2])-1]);
    aCon = [];
    for j in range(0,len(subA)-3,2):
        aCon.append(subA[j+1]-subA[j+2])
    return q, aCon

def joint_states_to_vect(joint_states):
    p = joint_states.position
    return np.matrix([[p[0]], [p[1]], [p[2]], [p[3]], [p[4]], [p[5]]])

def latest_joint_state(latest_joint_states):
    global emu_joint_states
    emu_joint_states = latest_joint_states

def cartesian_jog_callback(twist_command):
    global emu_joint_states
    if emu_joint_states:
        qk = joint_states_to_vect(emu_joint_states)
        increment = np.matrix([[twist_command.angular.x], [twist_command.angular.y], [twist_command.angular.z], [twist_command.linear.x], [twist_command.linear.y],[twist_command.linear.z]])
        q_kp1 = emu_llc.getCartesianJog(qk, increment)
        # q_kp1 = [[0],[0], [0], [0], [0], [0]]
        # print (q_kp1)
        next_joint_states = JointState()
        next_joint_states.name = []
        next_joint_states.position = []
        next_joint_states.velocity = []
        for i in range(1,7):
            next_joint_states.name.append("joint_{}".format(i))
            next_joint_states.position.append(float(q_kp1[i-1][0]))
            next_joint_states.velocity.append(0)
        js.publish(next_joint_states)


    else:
        pass






if __name__ == '__main__':
    try:
        rospy.Subscriber('emu/jog/cartesian', Twist, cartesian_jog_callback)
        rospy.Subscriber('emu/joint_states', JointState, latest_joint_state)
        rospy.spin()
    except rospy.ROSInterruptException:
        pass