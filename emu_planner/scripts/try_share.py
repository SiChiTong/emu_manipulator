#!/usr/bin/env python

import sys
import rospkg
import rospy

rospack = rospkg.RosPack()

share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)

import pyemu