from .Camera import Camera
from .initVision import initModel, visualModel
from .binFunc import getBinList
from .trayFunc import perspecTray,make0TrayHomo
from .trashFunc import  calOrientTrash, calAngTrash, calPoseTrash, makeTrayTrashHomo
from .Trash import Trash
from .Tray import Tray
from .kin import kinematics
import cv2
import numpy as np
def getTypeTrashEle(trash):
    return trash.getType()
class Vision():
    def __init__(self):
        self.WIDTH = 1024
        self.HEIGHT = 1024
        self.CALIBRATE = True
        self.CAMINDEX = 0
        self.TESTTHRESHOLD = 0.85
        self.BinScaleWorld = [0.10,0.1]
        self.BinScalePixel = [42,42]
        self.CLASSNUM = 3
        self.TrayLeft = Tray()
        self.TrayRight = Tray()
        self.Cam = Camera(self.WIDTH, self.HEIGHT, self.CALIBRATE)
        self.video = self.Cam.open(self.CAMINDEX)
        self.model = initModel(self.TESTTHRESHOLD,self.CLASSNUM)
    def getBin(self):
        return getBinList(self.Cam,self.BinScaleWorld,self.BinScalePixel)
    def snapPano(self,traySide):
        
        self.video.release()
            # find tray 
        self.video = self.Cam.open(0)
        while(1):
            _,frame = self.video.read()
            frame = self.Cam.applyCalibate(frame)
            
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) & 0xFF==ord('d'):
                if traySide == 'l':
                    self.TrayLeft.addPano(frame)
                elif traySide == 'r':    
                    self.TrayRight.addPano(frame)
                break
    
    def getTrash(self,traySide,panomode=0,persmode=1):
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        if len(Tray1.pano) == 3:
            frame = perspecTray(Tray1,panomode,persmode,traySide)
            Tray1.clearPano()
            
            # blackTuning(frame)
            
            cv2.imshow('frame',frame)
            cv2.waitKey(0)
                
            wScale = 1/1000
            hScale = 0.4 / 400
                # feed persTray to model
            outputs = self.model(frame)
                # model return trash mask and type
            tra = visualModel(frame, outputs,self.CLASSNUM)
            cv2.imshow('frame',tra)
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
            trashList = sorted(trashList,key = getTypeTrashEle)
            return trashList

    