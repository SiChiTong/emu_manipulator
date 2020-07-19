import cv2
import numpy as np
import rospkg
import sys
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
this_file = '/'.join(__file__.split("/")[0:-1])+'/'
config_path = this_file+"config/"
class Camera():
    
    def __init__(self, width, height, calibrated = False ):
        
        self.shape = ( width , height )
        self.calibrated = calibrated
        self.per_point = 0
        
        # Calibrate check
        if (self.calibrated):
            self.camera_matrix = np.loadtxt(config_path+"cameraMatrix.txt",dtype='f',delimiter=',')
            self.distrotion_matrix = np.array([np.loadtxt(config_path+"cameraDistortion.txt",dtype='f',delimiter=',')])
            self.new_camera_matrix = np.array([np.loadtxt(config_path+"cameraMatrix.txt",dtype='f',delimiter=',')])
    
    def open(self, camIndex = 0):
        
        self.cap = cv2.VideoCapture(camIndex)#cv2.CAP_DSHOW
        self.camIndex = camIndex
        # Config
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.shape[0])
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.shape[1])
        self.cap.set(cv2.CAP_PROP_FPS,60)
        # self.cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 2.25)
        self.cap.set(cv2.CAP_PROP_AUTOFOCUS, 0)
        print("Open Camera with chanel : ",camIndex,
              "\nResolution ",self.shape[0]," x ",self.shape[1],
              "\nExposure ",self.cap.get(cv2.CAP_PROP_EXPOSURE))
        
        return self.cap
    
    def show(self,name,img):
        
        cv2.imshow(str(name),img)  
    def applyCalibate(self,imgNotGood):
        img = imgNotGood
        h,  w = img.shape[:2]
        
        newcameramtx, roi=cv2.getOptimalNewCameraMatrix(self.camera_matrix,self.distrotion_matrix,(w,h),1,(w,h))

        # undistort
        mapx,mapy = cv2.initUndistortRectifyMap(self.camera_matrix,self.distrotion_matrix,None,newcameramtx,(w,h),5)
        dst = cv2.remap(img,mapx,mapy,cv2.INTER_LINEAR)
        # cv2.imshow("uncrop image",dst)
        # crop the image
        x,y,w,h = roi
        dst = dst[y:y+h, x:x+w]
        
        return dst 
