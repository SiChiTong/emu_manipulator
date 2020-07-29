#!/usr/bin/env python3

#add share pyemu
import sys, time
import copy
import rospkg
import rospy
from math import pi
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

from pyemu import Emuart

port ='/dev/ttyTHS1'

et = Emuart(port)

rospy.init_node('emulator_console')

print (et)
time.sleep(0.5)

test_q = [[0.3, 0, -0.3, 0, pi/2, 0], [-0.3, 0.3, -0.3, 0, 0.5, 0], [-0.3, 0.2, -0.3, 0, -0.5, pi/2], [0.3, 0, -0.3, pi/2, 0, pi/2], [pi/2, 0, -pi/2, 0, -0.2, 0], [pi/2, 0, -pi/2, 0, 0, -pi/4]]

test_v = [[0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]

test_t = [10, 5, 8, 8, 10, 8]

pose = {'home': [0, 0, pi/2, pi/2, 0, -pi/4], 
        'bin_snap': [0, 1.2, -0.02, pi/2, 0, 0], 
        'tray_left_1': [pi/2, 0.09, 0.1503, 1.6, 0, 0],
        'tray_left_2': [pi/2, 0.09, 0.1503, 1.45, 0, 0],
        'tray_left_3': [pi/2, 0.09, 0.1503, 1.25, 0, 0],
        'tray_right_1': [-pi/2, 0.09, 0.1503, 1.6, 0, 0],
        'tray_right_2': [-pi/2, 0.09, 0.1503, 1.45, 0, 0],
        'tray_right_3': [-pi/2, 0.09, 0.1503, 1.25, 0, 0],
        'zero': [0, 0, 0, 0, 0, 0]}

while et.established() and not rospy.is_shutdown():
    cmd = input(">> ")
    cmd = 'ret = et.'+cmd
    # try:
    exec(cmd)
    if ret is None:
        pass
    else:
        print ('Return: '+str(ret))
    # except:
    #     print ('Wrong input!')
