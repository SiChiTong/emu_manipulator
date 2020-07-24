#!/usr/bin/env python3
import time
import sys
import rospy
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
from pyemu import Vision
from geometry_msgs.msg import PoseArray,Pose
from sensor_msgs.msg import Image

import cv2
v = Vision(debug = True)
rospy.init_node('vision', anonymous=True)
pubTrashPose = rospy.Publisher('/emu/vision/trash_poses', PoseArray, queue_size = 20)
pubLeftTray = rospy.Publisher('/emu/vision/left_tray', Image, queue_size = 0,latch=True)
pubRightTray = rospy.Publisher('/emu/vision/right_tray', Image, queue_size = 20,latch=True)
# cv2.namedWindow('test ai')
# cv2.waitKey(0)
# bins = cv2.imread(package_path+'/bin14.jpg')
# img = v.snapBinImg()
# v.getBin(mode=1)
# cv2.waitKey(0)
print("snappano")
traySide = 'l'
# # v.snapPano(traySide,testImg = package_path+'/deploy1.jpg')
v.snapPano(traySide)

cv2.waitKey(0)
# # v.snapPano(traySide,testImg = package_path+'/deploy2.jpg')

v.snapPano(traySide)
cv2.waitKey(0)
# # v.snapPano(traySide,testImg = package_path+'/deploy3.jpg')

v.snapPano(traySide)
cv2.waitKey(0)
trashPose,pickTrashImg,trashNum = v.findTrash(traySide,panomode=0,persmode=0)
print("Getted trash")
# cv2.imwrite(package_path+"/getPickedTrash.jpg",v.getPickedTrash(traySide))

cv2.imshow("getPickedTrash",v.getPickedTrash(traySide))
cv2.waitKey()


# def pickTrashCfg(self,trashMsgList):
#     listCfg=[]
#     for trashMsg in trashMsgList :
#         Hi = np.matrix(np.eye(4))
#         x = trashMsg.x
#         y = trashMsg.y
#         z = 0.3
#         r = pyemu.quat2rotm([trashMsg.orientation.x,trashMsg.orientation.y,trashMsg.orientation.z,trashMsg.orientation.w])
#         Hi[0:3,0:3]=r
#         Hi[0:3,3]=np.matrix([[x],[y],[z]])
#         trashCfg = pyemu.computeIK(tf = Hi,q_now=self.getJointStates())
#         listCfg.append(trashCfg)
#     return listCfg
# trashMsg = PoseArray()
# trashMsg.header.frame_id="base_link"
# now = rospy.get_rostime()
# trashMsg.header.stamp = now
# for trash in trashLists:
    
#     trash_i = Pose()
#     trash_i.position.x = trash.getX()
#     trash_i.position.y = trash.getY()
#     trash_i.position.z = trash.getOrient()*10+trash.getType()+1
#     trash_i.orientation.x = trash.getAngle()[0]
#     trash_i.orientation.y = trash.getAngle()[1]
#     trash_i.orientation.z = trash.getAngle()[2]
#     trash_i.orientation.w = trash.getAngle()[3]
#     print([trash.getX(),trash.getY(),trash.getOrient()*10+trash.getType()+1,trash.getAngle()[0],trash.getAngle()[1],trash.getAngle()[2],trash.getAngle()[3]])
#     trashMsg.poses.append(trash_i)
# pubTrashPose.publish(trashMsg)
# if traySide=='l':
#     pimg = pubLeftTray
# elif traySide=='r':
#     pimg = pubRightTray
# # time.sleep(1)
# v.pubPickedTrash(pimg,traySide)

# while(1):
#     v.pubPickedTrash(pimg,traySide)
#     cv2.imshow("getPickedTrash",v.getPickedTrash(traySide))
    
#     key = cv2.waitKey(1)
#     if key==ord('q'):
#         print("fucking quit")
#         break
