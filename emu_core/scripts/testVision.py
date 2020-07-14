#!/home/emu/anaconda3/envs/detectron2/bin/python
import sys
import rospy
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
from pyemu import Vision
from geometry_msgs.msg import PoseArray,Pose

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
trashMsg = PoseArray()
trashMsg.header.frame_id="base_link"
now = rospy.get_rostime()
trashMsg.header.stamp = now
for trash in trashLists:
    
    trash_i = Pose()
    trash_i.position.x = trash.getX()
    trash_i.position.y = trash.getY()
    trash_i.position.z = trash.getOrient()*10+trash.getType()
    trash_i.orientation.x = trash.getAngle()[0]
    trash_i.orientation.y = trash.getAngle()[1]
    trash_i.orientation.z = trash.getAngle()[2]
    trash_i.orientation.w = trash.getAngle()[3]
    print([trash.getX(),trash.getY(),trash.getOrient()*10+trash.getType(),trash.getAngle()[0],trash.getAngle()[1],trash.getAngle()[2],trash.getAngle()[3]])
    trashMsg.poses.append(trash_i)
pub = rospy.Publisher('/emu/vision/trash_poses', PoseArray, queue_size = 20)
pub.publish(trashMsg)
