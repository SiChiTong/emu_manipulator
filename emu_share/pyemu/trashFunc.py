import cv2
import numpy as np
from math import sin,cos,atan2,pi
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
    return h