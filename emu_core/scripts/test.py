#!/home/emu/anaconda3/envs/detectron2/bin/python
import sys
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
from pyemu import Vision
import cv2
v = Vision()
cv2.namedWindow('test')
cv2.waitKey(0)

v.snapPano('l')
cv2.waitKey(0)

v.snapPano('l')
cv2.waitKey(0)

v.snapPano('l')
cv2.waitKey(0)
print(v.getTrash('l'))
