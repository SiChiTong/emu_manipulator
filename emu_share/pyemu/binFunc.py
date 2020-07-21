from .Bin import Bin
import cv2
from .Frame import Frame
import numpy as np
from .kin import kinematics
from math import pi

import rospkg
import sys
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
this_file = '/'.join(__file__.split("/")[0:-1])+'/'
config_path = this_file+"config/"
def createTrackbar(name,img):
    def nothing(x):
        pass
    blank_image = np.zeros(shape=[601,601, 3], dtype=np.uint8)
    cv2.namedWindow(name)


    cv2.createTrackbar('x1', name,0,img.shape[1],nothing)
    cv2.createTrackbar('y1', name,0,img.shape[0],nothing)
    cv2.createTrackbar('x2', name,0,img.shape[1],nothing)
    cv2.createTrackbar('y2', name,0,img.shape[0],nothing)
    cv2.createTrackbar('x3', name,0,img.shape[1],nothing)
    cv2.createTrackbar('y3', name,0,img.shape[0],nothing)
    cv2.createTrackbar('x4', name,0,img.shape[1],nothing)
    cv2.createTrackbar('y4', name,0,img.shape[0],nothing)
    
def readTrackbar(name):
    x1 = cv2.getTrackbarPos('x1',name)
    y1 = cv2.getTrackbarPos('y1',name)
    x2 = cv2.getTrackbarPos('x2',name)
    y2 = cv2.getTrackbarPos('y2',name)
    x3 = cv2.getTrackbarPos('x3',name)
    y3 = cv2.getTrackbarPos('y3',name)
    x4 = cv2.getTrackbarPos('x4',name)
    y4 = cv2.getTrackbarPos('y4',name)

    return x1,y1,x2,y2,x3,y3,x4,y4
def selectPoint(newimg,name):
    createTrackbar('test',newimg)
    
    while(1):
        img=newimg.copy()
        key = cv2.waitKey(1) & 0xFF
        x1,y1,x2,y2,x3,y3,x4,y4 = readTrackbar('test')
        pts = np.array([[x1,y1],[x2,y2],[x3,y3],[x4,y4]])
        cv2.circle(img, tuple(pts[0]), 5, (0, 0, 255), -1)
        cv2.circle(img,tuple(pts[1]), 5, (0, 255, 255), -1)
        
        cv2.circle(img,tuple(pts[2]), 5, (255, 255, 255), -1)
        cv2.circle(img, tuple(pts[3]), 5, (0, 255, 0), -1)
        # cv2.imshow('img',img)
        
        
        if key == ord('q'):
            break
        elif key == ord('s'):
            x= np.array([x1,y1,x2,y2,x3,y3,x4,y4])
            np.savetxt(config_path+'{}.txt'.format(name), x, delimiter=',') 
            # return(x1,y1,x2,y2,x3,y3,x4,y4)
            return True
def applyPerspective(img,w,h,name,mode=0,):
    temp_rect = np.zeros((4,2), dtype = "float32")
    if mode == 0:
        
        # s = np.sum(pts, axis = -1)
        
        # tl = pts[np.argmin(s)]
        # br = pts[np.argmax(s)]
        # diff = np.diff(pts, axis = -1)
        # tr = pts[np.argmin(diff)]
        # bl = pts[np.argmax(diff)]

        # # print(tl[0],tl[1])
        # temp_rect[0] = tl
        # temp_rect[1] = tr
        # temp_rect[2] = bl
        # temp_rect[3] = br
        
        x1,y1,x2,y2,x3,y3,x4,y4 = np.loadtxt(config_path+name+'.txt')
        temp_rect[0] = np.array([x1,y1])
        temp_rect[1] = np.array([x2,y2])
        temp_rect[2] = np.array([x3,y3])
        temp_rect[3] = np.array([x4,y4])
    elif mode == 1:
        
        check = selectPoint(img,name=name)
        if check :
            x1,y1,x2,y2,x3,y3,x4,y4 = np.loadtxt(config_path+name+'.txt')
        temp_rect[0] = np.array([x1,y1])
        temp_rect[1] = np.array([x2,y2])
        temp_rect[2] = np.array([x3,y3])
        temp_rect[3] = np.array([x4,y4])
    dst = np.array([[0,0],[w-1,0],[0,h-1],[w-1, h-1]], np.float32)
    M = cv2.getPerspectiveTransform(temp_rect,dst)
    warp = cv2.warpPerspective(img, M, (w, h))
    # print(temp_rect,ind,newLid)
    return warp
def detectBin(img,binScaleWorld,binScalePixel,mode=0):
    # helper function
    def detect(c):
        # initialize the shape name and approximate the contour
        shape = "unidentified"
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.04 * peri, True)
        # if the shape is a triangle, it will have 3 vertices
        if len(approx) == 3:
            shape = "triangle"
        # if the shape has 4 vertices, it is either a square or
        # a rectangle
        elif len(approx) == 4:
            # compute the bounding box of the contour and use the
            # bounding box to compute the aspect ratio
            (x, y, w, h) = cv2.boundingRect(approx)
            ar = w / float(h)
            # a square will have an aspect ratio that is approximately
            # equal to one, otherwise, the shape is a rectangle
            shape = "square" # if ar >= 0.95 and ar <= 1.05 else "rectangle"
        # if the shape is a pentagon, it will have 5 vertices
        elif len(approx) == 5:
            shape = "pentagon"
        # otherwise, we assume the shape is a circle
        else:
            shape = "circle"
        # return the name of the shape
        return shape
    def colorSegment(image,hsv):
        image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        lower = np.array([hsv[0],hsv[1],hsv[2]])
        upper = np.array([hsv[3],hsv[4],hsv[5]])
        mask = cv2.inRange(image,lower, upper)
        result = cv2.bitwise_and(image,image,mask = mask)
    
        return mask
    def labSegment(image,lab):
        image = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)
        lower = np.array([lab[0],lab[1],lab[2]])
        upper = np.array([lab[3],lab[4],lab[5]])
        mask = cv2.inRange(image,lower, upper)
        result = cv2.bitwise_and(image,image,mask = mask)
        
        return mask
    
    # parameter
    yHsv = [19, 51, 154, 35, 255, 255]
    gHsv = [37, 23, 70, 86, 255, 255]
    bHsv = [86, 30, 0, 162, 255, 255]
    
    yShapeLab = [0, 79, 87, 110, 179, 148]
    gShapeLab = [0, 80, 72, 21, 140, 142]
    bShapeLab = [0, 124, 86, 61, 131, 166]
    
    yShape = 'circle'
    gShape = 'circle'
    bShape = 'square'
    
    hsvList = [yHsv,gHsv,bHsv]
    shapeLabList = [yShapeLab,gShapeLab,bShapeLab]
    shapeList = [yShape,gShape,bShape]
    colorList = ['yellow','green','blue']
    binList = []
    # perspective 
    img = applyPerspective(img,1024,576,'binPer',mode=mode)
    # loop for three bin start with yellow green blue
    for ind in range(3):
        # color segment with hsv
        mask = colorSegment(img,hsvList[ind])
        mask = cv2.morphologyEx(mask,cv2.MORPH_OPEN, np.ones((7,7),np.uint8))
        
        # get bin contours
        _,contours,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        # get bin bounding box
        contours = np.concatenate(contours) 
        bx,by,bw,bh = cv2.boundingRect(contours)
        # cv2.rectangle(img, (bx,by), (bx+bw,by+bh),(0,255,255),1)
        
        # crop bin image
        binImg = img[by:by+bh,bx:bx+bw].copy()
        
        # color segment to find hole shape
        maskc = labSegment(binImg,shapeLabList[ind])
        maskc = cv2.morphologyEx(maskc,cv2.MORPH_OPEN, np.ones((5,5),np.uint8))
        
        # get hole contour
        _,contours,_ = cv2.findContours(maskc, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        # select max area contour
        c = max(contours, key = cv2.contourArea)
        
        # find hole shape 
        holeShape = detect(c)
        
        # shape check
        if holeShape != shapeList[ind]:
            print("Error when finding hole shape!!")
            # cv2.imshow('detectBinmask',mask)
            # cv2.waitKey()
        else:
            # get hole bounding box
            x,y,w,h = cv2.boundingRect(c)
            cv2.rectangle(img, (bx+x,by+y), (bx+x+w,by+y+h),(0,0,255),3)
            
            # get hole center point
            centerX = x+w//2
            centerY = y+h//2
            
            # offset to full image coordinate
            centerOffsetX = bx+centerX
            centerOffsetY = by+centerY
            
            # create Bin
            b = Bin(holePtsPixel = (centerOffsetX,centerOffsetY), color = colorList[ind])
            
            # Calculate world Position
            b.setHolePtsWorld(binScaleWorld,binScalePixel)
            binList.append(b)
            
    # find position
    def getBinXCoord(b):
        return b.getHolePtsPixel(0)
    sortedBin = sorted(binList,key=getBinXCoord)
    
    for b in range(3):
        sortedBin[b].setPosition(b)
        # print(sortedBin[b],'\n')
    # cv2.imshow('detectBin',img)
    # cv2.waitKey(0)
    return sortedBin
def transFrameBinToBase(x,y,z,scaleY):
    bx = 0.5
    by = 0.49
    bz = 0.36
    h0_cvp = Frame('0','cvp',np.matrix( [[1, 0, 0, bx],[0, 1, 0, by],[0, 0, 1, bz],[0, 0, 0, 1]] ))

    bx = 0
    by = scaleY
    bz = 0
    
    hcv_cvp = kinematics.transl(by,'y') * kinematics.rot(pi/2,'x') * kinematics.rot(pi/2,'z')
    hcv_cvp = Frame('cv','cvp',hcv_cvp)

    
    hcv_bin = Frame('cv','bin',np.matrix( [[1, 0, 0, x],[0, 1, 0, y],[0, 0, 1, z],[0, 0, 0, 1]] ))

   
    hbin_realbin = kinematics.transl(0.075,'z')
    hbin_realbin = Frame('bin','realbin',hbin_realbin)

    h0_realbin = h0_cvp.H * hcv_cvp.inverse() * hcv_bin.H * hbin_realbin.H
    
    return h0_realbin
def getBinList(Cam,BinScaleWorld,BinScalePixel,frame,mode=0):
    # video = Cam.open(Cam.camIndex)
    # read video
    # _,frame = video.read()
    # calibrate cam
    # frame = Cam.applyCalibate(frame)
    # cv2.imshow("ff",frame)
    # cv2.waitKey()
    # find bin pose and color
    binList = detectBin(frame,BinScaleWorld,BinScalePixel,mode=mode)
    # set width scale and height scale of world coordinate
    # print(0.5/frame.shape[0])
    binFrameHeight = frame.shape[0] * BinScaleWorld[1] / BinScalePixel[1]
    print(binFrameHeight)
    
    # with transfrom to base
    for i in range(len(binList)):
        x = binList[i].getHolePtsWorld(0)
        y = binList[i].getHolePtsWorld(1)
        z = 0 
        f = transFrameBinToBase(x,y,z,binFrameHeight)
        pts = (f[0,3],f[1,3],f[2,3])
        binList[i].setHoleRealPtsWorld(pts)
        print(binList[i])
    return binList