from .Camera import Camera
from .initVision import initModel, visualModel
from .binFunc import getBinList
from .trayFunc import perspecTray,make0TrayHomo
from .trashFunc import  calOrientTrash, calAngTrash, calPoseTrash, makeTrayTrashHomo, pickSequence
from .Trash import Trash
from .Tray import Tray
from .kin import kinematics
import cv2
import numpy as np
import time
from std_msgs.msg import Header
from sensor_msgs.msg import Image, JointState
import rospy
from geometry_msgs.msg import PoseArray,Pose


def getTypeTrashEle(trash):
    return trash.getType()
class Vision():
    def __init__(self,debug = False,emuLog=None):
        self.WIDTH = 1024
        self.HEIGHT = 576
        self.CALIBRATE = True
        self.CAMINDEX = 0
        self.TESTTHRESHOLD = 0.9
        self.BinScaleWorld = [0.775,0.508] # setnew scale
        self.BinScalePixel = [1024,576] # set newscale
        self.CLASSNUM = 3
        self.TrayLeft = Tray()
        self.TrayRight = Tray()
        self.Cam = Camera(self.WIDTH, self.HEIGHT, self.CALIBRATE)
        self.video = self.Cam.open(self.CAMINDEX)
        self.model = initModel(self.TESTTHRESHOLD,self.CLASSNUM)
        self.debug = debug
        self.binImg = None
        self.log = emuLog
    def getBin(self,mode=0):
        img = self.binImg
        binList = getBinList(self.Cam,self.BinScaleWorld,self.BinScalePixel,img,mode=mode)
        color=[]
        z=[]
        y=[]
        for b in binList:
            color.append(b.getColor())
            z.append(b.getHoleRealPtsWorld(2))
            y.append(b.getHoleRealPtsWorld(1))
        msg = JointState()
        msg.header.frame_id="base_link"
        now = rospy.get_rostime()
        msg.header.stamp = now
        msg.name = color
        msg.position = z
        msg.velocity = y
        return msg
    def snapBinImg(self):
        self.video.release()
        self.video = self.Cam.open(0)
        if self.debug:
            while(1):
                _,frame = self.video.read()
                frame = self.Cam.applyCalibate(frame)
                
                cv2.imshow('frame',frame)
                if cv2.waitKey(1) & 0xFF==ord('d'):
                    self.binImg = frame
                    
                    return frame
                    break
        else:
            cv2.waitKey(5)
            _,frame = self.video.read()
            frame = self.Cam.applyCalibate(frame)
            self.binImg = frame
    def snapPano(self,traySide,testImg=None):
        if testImg!=None:
            frame = cv2.imread(testImg)
            if traySide == 'l':
                self.TrayLeft.addPano(frame)
            elif traySide == 'r':    
                self.TrayRight.addPano(frame)
            return True
        self.video.release()
            # find tray 
        self.video = self.Cam.open(0)
        if self.debug:
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
        else:
            _,frame = self.video.read()
            frame = self.Cam.applyCalibate(frame)
            if traySide == 'l':
                self.TrayLeft.addPano(frame)
            elif traySide == 'r':    
                self.TrayRight.addPano(frame)
    
    def findTrash(self,traySide,panomode=0,persmode=0,testImg=None):
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        if len(Tray1.pano) == 3 or testImg != None:
            frame = perspecTray(Tray1,panomode,persmode,traySide,debug=self.debug)
            Tray1.clearPano()
            print("panofinish")
            # blackTuning(frame)
            if self.debug:
                cv2.imshow('frame',frame)
                cv2.waitKey(0)
                
            wScale = 1.286/1008
            hScale = 0.565 / 440
                # feed persTray to model
            print("start predict")
            outputs = self.model(frame)
            print("Predict done")
            # print(outputs)
                # model return trash mask and type
            tra = visualModel(frame, outputs,self.CLASSNUM)
            Tray1.addImg(tra)
            if self.debug:
                cv2.imshow('trash',tra)
                cv2.waitKey(0)
                    
                # remem number of trash in tray
            trashNum = len(outputs['instances'])
                # loop per number of trash
            trashList = []
            if trashNum == 0:
                return None,self._msgImgPickedTrash(traySide,Tray1.getImg()),trashNum
            else:
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
                    trash.setBox(outputs['instances'].pred_boxes[i].tensor.cpu().numpy())
                    trash.setMask(outputs['instances'].pred_masks[i].cpu().numpy().astype(np.uint8)*255)
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
                    trash.setPredId(i)
                            # generate ros message
                    
                                # format x,y,z,quart
                                # set x and y from trash x and y
                                # z is two digit int 
                    trashList.append(trash)
                trashList = pickSequence(trashList)
                if len(trashList)==0:
                    return None,self._msgImgPickedTrash(traySide,Tray1.getImg()),trashNum
                trashList = sorted(trashList,key = getTypeTrashEle)
                cv2.destroyAllWindows()
                p = np.zeros((440,1128),dtype=np.uint8)
                pId=[]
                for trash in trashList:
                    
                    # picked_trash = cv2.bitwise_and(Tray1.getImg(),Tray1.getImg(),mask=trash.getMask())
                    # p = cv2.bitwise_or(p,trash.getMask())
                    # print(trash)
                    pId.append(trash.getPredId())
                    print(trash)
                    # cv2.imshow('PickedTrash',picked_trash)
                    # cv2.waitKey(0)
                pickedTrashTray = visualModel(frame, outputs,self.CLASSNUM,pId)
                # pickedTrashTray = cv2.bitwise_and(Tray1.getImg(),Tray1.getImg(),mask=p)
                # gray = cv2.cvtColor(Tray1.getImg(),cv2.COLOR_BGR2GRAY)
                # gray = cv2.cvtColor(gray,cv2.COLOR_GRAY2BGR)
                # pickGray = cv2.bitwise_and(gray,gray,mask=cv2.bitwise_not(p))
                # # pickGray = np.stack((pickGray,)*3, axis=-1)
                # orimg = cv2.bitwise_or(pickGray,pickedTrashTray)
                # cv2.imshow('pp',pickedTrashTray)
                # cv2.waitKey(0)
                Tray1.addPickedTrash(pickedTrashTray)
                trashPose = self._msgTrashPose(trashList)
                picktrashMsg = self._msgImgPickedTrash(traySide)
                # cv2.imshow('Pic Trash',pickedTrashTray)
                # cv2.waitKey()
                return trashPose,picktrashMsg,trashNum

    def getTrayImg(self,traySide):
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        return Tray1.getImg()
    def getPickedTrash(self,traySide):
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        return Tray1.getPickedTrash()
    
    def _msgTrashPose(self,trashLists):
        trashMsg = PoseArray()
        trashMsg.header.frame_id="base_link"
        now = rospy.get_rostime()
        trashMsg.header.stamp = now
        for trash in trashLists:
            
            trash_i = Pose()
            trash_i.position.x = trash.getX()
            trash_i.position.y = trash.getY()
            trash_i.position.z = trash.getOrient()*10+trash.getType()+1
            trash_i.orientation.x = trash.getAngle()[0]
            trash_i.orientation.y = trash.getAngle()[1]
            trash_i.orientation.z = trash.getAngle()[2]
            trash_i.orientation.w = trash.getAngle()[3]
            # print([trash.getX(),trash.getY(),trash.getOrient()*10+trash.getType()+1,trash.getAngle()[0],trash.getAngle()[1],trash.getAngle()[2],trash.getAngle()[3]])
            trashMsg.poses.append(trash_i)
        return trashMsg
    def _msgImgPickedTrash(self,traySide,imgN=None):
        
        
        if traySide == 'l':
            Tray1 = self.TrayLeft
        elif traySide == 'r':    
            Tray1 = self.TrayRight
        if type(imgN) == type(None):
            img = Tray1.getPickedTrash()
        else:
            img = Tray1.getImg()
        img = Tray1.getImg()
        
        msg = Image()
        msg.header = Header()
        msg.height = img.shape[0]
        msg.width = img.shape[1]
        msg.step = img.strides[0]
        msg.encoding = 'bgr8'
        msg.is_bigendian = 0
        msg.data = img.flatten().tolist()
        
        return msg
        # break
        
