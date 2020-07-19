#!/home/emu/anaconda3/envs/detectron2/bin/python
<<<<<<< HEAD
import time
=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
import sys
import rospy
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
from pyemu import Vision
from geometry_msgs.msg import PoseArray,Pose
<<<<<<< HEAD
from sensor_msgs.msg import Image

import cv2
v = Vision(debug = True)
rospy.init_node('vision', anonymous=True)
pubTrashPose = rospy.Publisher('/emu/vision/trash_poses', PoseArray, queue_size = 20)
pubLeftTray = rospy.Publisher('/emu/vision/left_tray', Image, queue_size = 20,latch=True)
pubRightTray = rospy.Publisher('/emu/vision/right_tray', Image, queue_size = 20,latch=True)
cv2.namedWindow('test ai')
cv2.waitKey(0)
# bins = cv2.imread(package_path+'/bin14.jpg')
# img = v.snapImg()
# v.getBin(img,mode=0)
# cv2.waitKey(0)
traySide = 'l'
v.snapPano(traySide,testImg = package_path+'/deploy1.jpg')
# v.snapPano(traySide)

cv2.waitKey(0)
v.snapPano(traySide,testImg = package_path+'/deploy2.jpg')

# v.snapPano(traySide)
cv2.waitKey(0)
v.snapPano(traySide,testImg = package_path+'/deploy3.jpg')

# v.snapPano(traySide)
cv2.waitKey(0)
trashLists = v.findTrash(traySide,panomode=0,persmode=0)
print("Getted trash")
cv2.imwrite(package_path+"/tray.jpg",v.getTrayImg(traySide))

# cv2.imshow("getPickedTrash",v.getPickedTrash(traySide))
# cv2.waitKey()

=======

import cv2
v = Vision(debug = True)
cv2.namedWindow('test')
cv2.waitKey(0)
traySide = 'l'
v.snapPano(traySide)
cv2.waitKey(0)

v.snapPano(traySide)
cv2.waitKey(0)

v.snapPano(traySide)
cv2.waitKey(0)
trashLists = v.findTrash(traySide,panomode=1,persmode=1)
print("Getted trash")

cv2.waitKey(0)
rospy.init_node('vision', anonymous=True)
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
trashMsg = PoseArray()
trashMsg.header.frame_id="base_link"
now = rospy.get_rostime()
trashMsg.header.stamp = now
for trash in trashLists:
    
    trash_i = Pose()
    trash_i.position.x = trash.getX()
    trash_i.position.y = trash.getY()
<<<<<<< HEAD
    trash_i.position.z = trash.getOrient()*10+trash.getType()+1
=======
    trash_i.position.z = trash.getOrient()*10+trash.getType()
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
    trash_i.orientation.x = trash.getAngle()[0]
    trash_i.orientation.y = trash.getAngle()[1]
    trash_i.orientation.z = trash.getAngle()[2]
    trash_i.orientation.w = trash.getAngle()[3]
<<<<<<< HEAD
    print([trash.getX(),trash.getY(),trash.getOrient()*10+trash.getType()+1,trash.getAngle()[0],trash.getAngle()[1],trash.getAngle()[2],trash.getAngle()[3]])
    trashMsg.poses.append(trash_i)
pubTrashPose.publish(trashMsg)
if traySide=='l':
    pimg = pubLeftTray
elif traySide=='r':
    pimg = pubRightTray
# time.sleep(1)
# v.pubPickedTrash(pimg,traySide)

while(1):
    v.pubPickedTrash(pimg,traySide)
    cv2.imshow("getPickedTrash",v.getPickedTrash(traySide))
    
    key = cv2.waitKey(1)
    if key==ord('q'):
        print("fucking quit")
        break
=======
    print([trash.getX(),trash.getY(),trash.getOrient()*10+trash.getType(),trash.getAngle()[0],trash.getAngle()[1],trash.getAngle()[2],trash.getAngle()[3]])
    trashMsg.poses.append(trash_i)
pub = rospy.Publisher('/emu/vision/trash_poses', PoseArray, queue_size = 20)
pub.publish(trashMsg)
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
