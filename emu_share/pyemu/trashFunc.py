import cv2
import numpy as np
<<<<<<< HEAD
from math import sin,cos,atan2,pi,sqrt

=======
from math import sin,cos,atan2,pi
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
def calAngTrash(output,ind):

    rcv = np.matrix([[0, -1, 0],
            [1,0,0],
            [0,0,1]])
    thresh = output.pred_masks[ind].cpu().numpy().astype(np.uint8)*255
    # find outer contour
    _,cntrs,_ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    cntrs = np.concatenate(cntrs) 

    (x,y),(MA,ma),angle = cv2.fitEllipse(cntrs)
    
    rad = angle*pi/180
    rt = np.matrix([[cos(rad), -sin(rad), 0],
        [sin(rad),cos(rad),0],
        [0,0,1]])
    
    tf = np.dot(rcv,rt)
    nangle = atan2(tf[1,0],tf[0,0])
    return nangle
   
def calOrientTrash(output,ind):
    # cal orientation
    #     depend on type
    tType = output.pred_classes[ind].item()
    mask = output.pred_masks[ind].cpu().numpy().astype(np.uint8)*255
    
        # if type is bot or can
    if tType == 0: # bottle
        # find major axis and mionr axis from fit elipse at contour
        _,cntrs,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cntrs = np.array(cntrs[0])
        (x,y),(MA,ma),angle = cv2.fitEllipse(cntrs)
        # check ratio of Ma/ma
            # if low ratio
        if(MA/ma <= 0.32):
            #  orientaion is lay down => 1
            print('bot lay',MA/ma)
            orient = 1
        else:
            # if high ratio
            # orientaion is stand up => 2
            print('bot stand',MA/ma)
            orient = 2
    elif tType == 1: # can
        # find major axis and mionr axis from fit elipse at contour
        _,cntrs,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cntrs = np.array(cntrs[0])
        (x,y),(MA,ma),angle = cv2.fitEllipse(cntrs)
        # check ratio of Ma/ma
            # if low ratio
        if(MA/ma <= 0.4):
            #  orientaion is lay down => 1
            print('can lay',MA/ma)
            orient = 1
        else:
            # if high ratio
            #  orientaion is stand up => 2
            print('can stand',MA/ma)
            orient = 2
    # if type is snack
    elif tType == 2: # snack
        #  orientaion is lay down => 1
        orient = 1
    return orient
                
def calPoseTrash(output,ind,wScale,hScale):
    # get mask
    mask = output.pred_masks[ind].cpu().numpy().astype(np.uint8)*255
    # calculate moments of binary image
    M = cv2.moments(mask)
    # calculate x,y coordinate of center
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    # world coor = cent_coor * tray scale(width and height)
    wX = cX*wScale
    wY = cY*hScale
    wZ = 0
    # return x and y set z to zero
    return (wX, wY,wZ)
def makeTrayTrashHomo(yaw,x,y,z):
    h = np.matrix([[cos(yaw), -sin(yaw), 0, x],
                   [sin(yaw), cos(yaw),0,y],
                   [0,0,1,z],
                   [0,0,0,1]])
<<<<<<< HEAD
    return h
def pickSequence(trashLists):
    def getRatio(ele):
        temp_rect = np.zeros((4,2), dtype = "float32")
        bbox = ele.getBox()
        tmask = ele.getMask()
        im, contours, hierarchy = cv2.findContours(tmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        rect = cv2.minAreaRect(contours[0])
        box = cv2.boxPoints(rect)
        pts = np.int0(box)
        
        s = np.sum(pts, axis = -1)
        
        tl = pts[np.argmin(s)]
        br = pts[np.argmax(s)]
        diff = np.diff(pts, axis = -1)
        tr = pts[np.argmin(diff)]
        bl = pts[np.argmax(diff)]
        area = sqrt((tl[0]-tr[0])**2+(tl[1]-tr[1])**2)*sqrt((tl[0]-bl[0])**2+(tl[1]-bl[1])**2)
        maskarea = cv2.contourArea(contours[0])
        ratio = len(np.where(tmask==255)[0])/area
        # print('ratio',ele.getType(),ratio,maskarea,((bbox[2]-bbox[0])*(bbox[3]-bbox[1])),len(np.where(tmask==255)[0]),area)
        return ratio
    # check all intersect instance per this instance
        # loop main trash in trashLists:
    robotPickLists=[]
    while len(trashLists)> 0:
        # sub loop trash in trashLists except self:
        tray = np.zeros((400,1000),dtype=np.uint8)
        mtray = tray.copy()
        
        mtrash = trashLists[0].getBox()
        print(mtrash)
        mtray[mtrash[1]:mtrash[3],mtrash[0]:mtrash[2]]=1
        newTray=mtray.copy()
        intersLists=[trashLists[0]]
        for strash in  trashLists[1:]:
            instray  = tray.copy()
            strashBB = strash.getBox()
            instray[strashBB[1]:strashBB[3],strashBB[0]:strashBB[2]]=1
            overlap = mtray+instray
            if len(np.where(overlap==2)[0])>0:
                print('intersect')
                intersLists.append(strash)
            else:
                print('not',len(np.where(overlap==2)[0]))
            
            # cv2.imshow('overlap',overlap*127)
            # cv2.waitKey(0)
        # if main and sub is intersect add to intersect list
        pickLists=[]
        # loop in intersect list
        for trash in intersLists:
            # check area threshold depend on type and oreint
            if trash.getType() == 0:
                tmask = trash.getMask()
                im, contours, hierarchy = cv2.findContours(tmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
                contours=np.concatenate(contours)
                area = cv2.contourArea(contours)
                print('bottle',area,cv2.minAreaRect(contours))#11000 9600
                if len(intersLists)>1 and area >= 9000:
                    pickLists.append(trash)
                elif len(intersLists)==1:
                    pickLists.append(trash)
                cv2.imshow('tmask',tmask)
                cv2.waitKey(0)
            if trash.getType() == 1:
                tmask = trash.getMask()
                im, contours, hierarchy = cv2.findContours(tmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
                contours=np.concatenate(contours)
                area = cv2.contourArea(contours)
                print('can',area,cv2.minAreaRect(contours))#5000
                if len(intersLists)>1 and area >= 5000:
                    pickLists.append(trash)
                elif len(intersLists)==1:
                    pickLists.append(trash)
                cv2.imshow('tmask',tmask)
                cv2.waitKey(0)
            if trash.getType() == 2:
                tmask = trash.getMask()
                
                im, contours, hierarchy = cv2.findContours(tmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
                contours=np.concatenate(contours)
                area = cv2.contourArea(contours)
                if len(intersLists)>1 and area >= 2300:
                    pickLists.append(trash)
                elif len(intersLists)==1:
                    pickLists.append(trash)
                print('snack',area,cv2.minAreaRect(contours))
                cv2.imshow('tmask',tmask)
                cv2.waitKey(0)
        print('pickLists',len(pickLists))
        if len(pickLists) > 1:
            
            pickLists = sorted(pickLists,key=getRatio)
            robotPickLists.append(pickLists[-1])
        else:
            robotPickLists.append(pickLists[0])
            # if lower then remove from picklist
            # if upper 
                # check ratio between mask/bndboxarea
                # lower is back remove from picklist
        for i in intersLists:
            trashLists.remove(i)
    print(robotPickLists,len(robotPickLists))
    return robotPickLists
def pickSequence2(trashLists):
    while len(trashLists)> 0:
        tmask = trashLists[0].getMask()
        tray = np.zeros((400,1000),dtype=np.uint8)
        mtray = tray.copy()
        im, contours, hierarchy = cv2.findContours(tmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        contours = np.concatenate(contours)
        rect = cv2.minAreaRect(contours)
        box = cv2.boxPoints(rect)
        box = np.int0(box)
        cv2.drawContours(mtray,[box],-1,1,-1)
        intersLists = [trashLists[0]]
        for strash in  trashLists[1:]:
            instray  = tray.copy()
            strashMask = strash.getMask()
            im, contours, hierarchy = cv2.findContours(strashMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
            contours = np.concatenate(contours)
            rect = cv2.minAreaRect(contours)
            box = cv2.boxPoints(rect)
            box = np.int0(box)
            cv2.drawContours(instray,[box],-1,1,-1)
            overlap = mtray+instray
            if len(np.where(overlap==2)[0])>0:
                print('intersect')
                print(np.where(overlap<2,0,255).shape,strashMask.shape)
                cv2.imshow('ins',np.where(overlap<2,0,255)*255)
                cv2.waitKey()
                interstmask = np.bitwise_and(np.where(overlap<2,0,255),  tmask*1)
                intersstarshmask = np.bitwise_and(np.where(overlap<2,0,255),strashMask*1)
                print(len(np.where(interstmask==255)[0]))
                print(len(np.where(intersstarshmask==255)[0]))
                
                intersLists.append(strash)
            else:
                print('not',len(np.where(overlap==2)[0]))
            
            cv2.imshow('overlap',overlap*127)
            cv2.waitKey(0)
        pickLists = []
        
=======
    return h
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
