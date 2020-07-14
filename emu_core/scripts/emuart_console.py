#!/usr/bin/env python

#add share pyemu
import sys, time
import copy
import rospkg
import rospy
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

from pyemu import Emuart

port ='/dev/ttyTHS1'

et = Emuart(port)

rospy.init_node('emulator_console')

print (et)
time.sleep(0.5)

while et.established() and not rospy.is_shutdown():
    cmd = input(">> ")
    cmd = 'ret = et.'+cmd
    try:
        exec(cmd)
        if ret is None:
            pass
        else:
            print ('Return: '+str(ret))
    except:
        print ('Wrong input!')
