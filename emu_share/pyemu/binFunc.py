from .Bin import Bin
import cv2
from .Frame import Frame
import numpy as np
from .kin import kinematics
def detectBin(img,binScaleWorld,binScalePixel):
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
    # loop for three bin start with yellow green blue
    for ind in range(3):
        # color segment with hsv
        mask = colorSegment(img,hsvList[ind])
        mask = cv2.morphologyEx(mask,cv2.MORPH_OPEN, np.ones((5,5),np.uint8))
        
        # get bin contours
        _,contours,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        # get bin bounding box
        contours = np.concatenate(contours) 
        bx,by,bw,bh = cv2.boundingRect(contours)
        cv2.rectangle(img, (bx,by), (bx+bw,by+bh),(0,255,255),1)
        
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
            show('detectBinmask',mask)
        else:
            # get hole bounding box
            x,y,w,h = cv2.boundingRect(c)
            cv2.rectangle(img, (bx+x,by+y), (bx+x+w,by+y+h),(0,255,255),1)
            
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
        print(sortedBin[b],'\n')
    show('detectBin',img)
    return sortedBin
def transFrameBinToBase(x,y,z,scaleY):
    bx = 0.5
    by = 0.5
    bz = 0.3
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
def getBinList(Cam,BinScaleWorld,BinScalePixel):
    video = Cam.open(Cam.camIndex)
    # read video
    _,frame = video.read()
    # calibrate cam
    frame = Cam.applyCalibate(frame)
    # find bin pose and color
    binList = detectBin(frame,BinScaleWorld,BinScalePixel)
    # set width scale and height scale of world coordinate
    binFrameHeight = img.shape[0] * BinScaleWorld[1] / BinScalePixel[1]
    # with transfrom to base
    for i in range(len(binList)):
        x = binList[i].getHolePtsWorld(0)
        y = binList[i].getHolePtsWorld(1)
        z = 0 
        f = transFrameBinToBase(x,y,z,binFrameHeight)
        pts = (f[0,3],f[1,3],f[2,3])
        binList[i].setHoleRealPtsWorld(pts)
    return binList