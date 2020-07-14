#!/usr/bin/env python

import sys
import rospy
import time
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')

from geometry_msgs.msg import PoseArray,Pose

poseList = [[0.10599999999999998, 0.525, 11, -0.004222495939768292, 0.9999910852242827, -6.123179408479028e-17, -2.585533068524967e-19],
[-0.361, 0.5760000000000001, 11, 0.5650443717528625, 0.825060517750312, -5.0520386108288877e-17, 3.4598989062168507e-17],
[-0.03999999999999998, 0.543, 22, 1.0, 0.0, 0.0, 6.123233995736766e-17],
[0.30600000000000005, 0.529, 13, -0.002238052132716429, 0.9999974955581895, -6.123218660453532e-17, -1.3704116903280412e-19],
[-0.07500000000000001, 0.684, 13, -0.3738952804399497, 0.927470926371674, -5.679121506416506e-17, -2.2894482920354318e-17],
[-0.275, 0.651, 13, 0.4103722017889784, 0.9119181191306959, -5.583888028389407e-17, 2.5128050168996203e-17],
[-0.258, 0.544, 13, 0.24973214185491485, 0.9683149577098129, -5.929219067629136e-17, 1.5291683408341713e-17],
[-0.356, 0.663, 13, 0.3411705121299028, 0.9400014264100985, -5.755848690235367e-17, 2.0890668782167435e-17],
[0.10799999999999998, 0.6020000000000001, 13, -0.045283614368823215, 0.9989741709722507, -6.116952604560238e-17, -2.772821669530122e-18]]
rospy.init_node('vision', anonymous=True)
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
pub = rospy.Publisher('/emu/vision/trash', PoseArray, queue_size = 20, latch = True)
time.sleep(0.25)
pub.publish(trashMsg)
print("pub finish")