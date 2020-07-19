from .Camera import Camera
from .initVision import initModel, visualModel
from .binFunc import getBinList
from .trayFunc import perspecTray,make0TrayHomo
<<<<<<< HEAD
from .trashFunc import  calOrientTrash, calAngTrash, calPoseTrash, makeTrayTrashHomo, pickSequence
=======
from .trashFunc import  calOrientTrash, calAngTrash, calPoseTrash, makeTrayTrashHomo
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
from .Trash import Trash
from .Tray import Tray
from .kin import kinematics
import cv2
import numpy as np
<<<<<<< HEAD
import time
from std_msgs.msg import Header
from sensor_msgs.msg import Image
import rospy


=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
def getTypeTrashEle(trash):
    return trash.getType()
class Vision():
    def __init__(self,debug = False):
        self.WIDTH = 1024
<<<<<<< HEAD
        self.HEIGHT = 576
        self.CALIBRATE = True
        self.CAMINDEX = 0
        self.TESTTHRESHOLD = 0.85
        self.BinScaleWorld = [0.10,0.55] # setnew scale
        self.BinScalePixel = [83,576] # set newscale
=======
        self.HEIGHT = 1024
        self.CALIBRATE = True
        self.CAMINDEX = 0
        self.TESTTHRESHOLD = 0.85
        self.BinScaleWorld = [0.10,0.1]
        self.BinScalePixel = [42,42]
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
        self.CLASSNUM = 3
        self.TrayLeft = Tray()
        self.TrayRight = Tray()
        self.Cam = Camera(self.WIDTH, self.HEIGHT, self.CALIBRATE)
        self.video = self.Cam.open(self.CAMINDEX)
        self.model = initModel(self.TESTTHRESHOLD,self.CLASSNUM)
        self.debug = debug
<<<<<<< HEAD
        
    def getBin(self,img,mode=0):
        return getBinList(self.Cam,self.BinScaleWorld,self.BinScalePixel,img,mode=mode)
    def snapImg(self):
        while(1):
            _,frame = self.video.read()
            # frame = self.Cam.applyCalibate(frame)
            
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) & 0xFF==ord('d'):
                return frame
                break
    def snapPano(self,traySide,testImg=None):
        if testImg!=None:
            frame = cv2.imread(testImg)
            if traySide == 'l':
                self.TrayLeft.addPano(frame)
            elif traySide == 'r':    
                self.TrayRight.addPano(frame)
            return True
=======
    def getBin(self):
        return getBinList(self.Cam,self.BinScaleWorld,self.BinScalePixel)
    def snapPano(self,traySide):
        
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
        self.video.release()
            # find tray 
        self.video = self.Cam.open(0)
        if self.debug:
            while(1):
                _,frame = self.video.read()
<<<<<<< HEAD
                # frame = self.Cam.applyCalibate(frame)
=======
                frame = self.Cam.applyCalibate(frame)
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
                
                cv2.imshow('frame',frame)
                if cv2.waitKey(1) & 0xFF==ord('d'):
                    if traySide == 'l':
                        self.TrayLeft.addPano(frame)
                    elif traySide == 'r':    
                        self.TrayRight.addPano(frame)
                    break
        else:
            _,frame = self.video.read()
            frame = self.Cam.applyCalibate(frame)
            if traySide == 'l':
                self.TrayLeft.addPano(frame)
            elif traySide == 'r':    
                self.TrayRight.addPano(frame)
    
<<<<<<< HEAD
    def findTrash(self,traySide,panomode=0,persmode=1,testImg=None):
=======
    def findTrash(self,traySide,panomode=0,persmode=1):
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
<<<<<<< HEAD
        if len(Tray1.pano) == 3 or testImg != None:
=======
        if len(Tray1.pano) == 3:
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
            frame = perspecTray(Tray1,panomode,persmode,traySide,debug=self.debug)
            Tray1.clearPano()
            
            # blackTuning(frame)
            if self.debug:
                cv2.imshow('frame',frame)
                cv2.waitKey(0)
                
<<<<<<< HEAD
            wScale = 1.41/1128
            hScale = 0.55 / 440
                # feed persTray to model
            outputs = self.model(frame)
            print(outputs)
                # model return trash mask and type
            tra = visualModel(frame, outputs,self.CLASSNUM)
            Tray1.addImg(frame)
=======
            wScale = 1/1000
            hScale = 0.4 / 400
                # feed persTray to model
            outputs = self.model(frame)
                # model return trash mask and type
            tra = visualModel(frame, outputs,self.CLASSNUM)
            Tray1.addImg(tra)
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
            if self.debug:
                cv2.imshow('trash',tra)
                cv2.waitKey(0)
                    
                # remem number of trash in tray
            trashNum = len(outputs['instances'])
                # loop per number of trash
            trashList = []
            for i in range(trashNum):
                    # cal position of trash
                        # get trash type
                tTrash = outputs['instances'].pred_classes[i].item()
                        # cal orientation
                tOrient = calOrientTrash(outputs['instances'],i)
                        # cal yaw angle of trash
                            # depend on orientation
                                # if lay down
                if tOrient == 1:
                                # return yaw
                    tAngle = calAngTrash(outputs['instances'],i)
                                # else
                else:
                                # return n
                    tAngle = 0
                                
                        # cal world pose of trash
                tx,ty,tz = calPoseTrash(outputs['instances'],i,wScale,hScale)
                        # make homogenous matrix => htray_trash
                htray_trash = makeTrayTrashHomo(tAngle,tx,ty,tz)            
                        # transform to base frame
                            # h0_trash = h0_tray * htray_trash
                h0_trash = np.dot(make0TrayHomo(traySide),htray_trash)
                
                        # construct trash class
                trash = Trash()
                            # set pose xy
                                # getX,getY pose from h0_trash
<<<<<<< HEAD
                trash.setBox(outputs['instances'].pred_boxes[i].tensor.cpu().numpy())
                trash.setMask(outputs['instances'].pred_masks[i].cpu().numpy().astype(np.uint8)*255)
=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
                trash.setX(h0_trash[0,3])
                trash.setY(h0_trash[1,3])
                            # set angle
                                # change rotm from h0_trash to quarternion
                trash.setAngle(kinematics.rotm2quart(h0_trash[0:3,0:3]))
                            # set trash type
                                # bot = 1
                                # can = 2
                                # snack = 3
                                # get from model output
                trash.setType(tTrash)
                            # set trash orientation
                trash.setOrient(tOrient)
                
                        # generate ros message
                
                            # format x,y,z,quart
                            # set x and y from trash x and y
                            # z is two digit int 
                trashList.append(trash)
<<<<<<< HEAD
            trashList = pickSequence(trashList)
            trashList = sorted(trashList,key = getTypeTrashEle)
            cv2.destroyAllWindows()
            p = np.zeros((440,1128),dtype=np.uint8)
            for trash in trashList:
                
                picked_trash = cv2.bitwise_and(Tray1.getImg(),Tray1.getImg(),mask=trash.getMask())
                p = cv2.bitwise_or(p,trash.getMask())
                print(trash)
                # cv2.imshow('PickedTrash',picked_trash)
                # cv2.waitKey(0)
            pickedTrashTray = cv2.bitwise_and(Tray1.getImg(),Tray1.getImg(),mask=p)
            Tray1.addPickedTrash(pickedTrashTray)
            # cv2.imshow('Pic Trash',pickedTrashTray)
            # cv2.waitKey()
            return trashList

    def getTrayImg(self,traySide):
=======
            trashList = sorted(trashList,key = getTypeTrashEle)
            return trashList

    def getTrashImg(self,trashSide):
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
<<<<<<< HEAD
        return Tray1.getImg()
    def getPickedTrash(self,traySide):
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        return Tray1.getPickedTrash()
    
    
    def pubPickedTrash(self,pub,traySide):
        
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        img = Tray1.getPickedTrash()
        msg = Image()
        msg.header = Header()
        msg.height = img.shape[0]
        msg.width = img.shape[1]
        msg.step = img.strides[0]
        msg.encoding = 'bgr8'
        msg.is_bigendian = 0
        msg.data = img.flatten().tolist()
        
        pub.publish(msg)
        print('send')
        
=======
        return Tray1.getImg()
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
