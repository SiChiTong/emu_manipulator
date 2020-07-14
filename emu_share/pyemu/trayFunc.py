import cv2
import numpy as np
import skimage.io as io
from skimage.color import rgb2gray
from skimage.feature import ORB
from skimage.feature import match_descriptors
from skimage.transform import ProjectiveTransform
from skimage.measure import ransac
from skimage.transform import SimilarityTransform
from skimage.transform import warp
from skimage.morphology import flood_fill
from skimage.graph import route_through_array
from skimage.color import gray2rgb
from math import sin,cos,pi
import rospkg
import sys
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
this_file = '/'.join(__file__.split("/")[0:-1])+'/'
config_path = this_file+"config/"
#helper
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
        cv2.imshow('img',img)
        
        
        if key == ord('q'):
            break
        elif key == ord('s'):
            x= np.array([x1,y1,x2,y2,x3,y3,x4,y4])
            np.savetxt(config_path+'{}.txt'.format(name), x, delimiter=',') 
            # return(x1,y1,x2,y2,x3,y3,x4,y4)
            return True
            
def makePano(pano_imgs,traySide,n_keypoints=800,fast_threshold=0.05,mode=0):
    def generate_costs(diff_image, mask, vertical=True, gradient_cutoff=2.):
        """
        Ensures equal-cost paths from edges to region of interest.

        Parameters
        ----------
        diff_image : ndarray of floats
            Difference of two overlapping images.
        mask : ndarray of bools
            Mask representing the region of interest in ``diff_image``.
        vertical : bool
            Control operation orientation.
        gradient_cutoff : float
            Controls how far out of parallel lines can be to edges before
            correction is terminated. The default (2.) is good for most cases.

        Returns
        -------
        costs_arr : ndarray of floats
            Adjusted costs array, ready for use.
        """
        if vertical is not True:
            return tweak_costs(diff_image.T, mask.T, vertical=vertical,
                            gradient_cutoff=gradient_cutoff).T

        # Start with a high-cost array of 1's
        costs_arr = np.ones_like(diff_image)

        # Obtain extent of overlap
        row, col = mask.nonzero()
        cmin = col.min()
        cmax = col.max()
        shape = mask.shape

        # Label discrete regions
        labels = mask.copy().astype(np.uint8)
        cslice = slice(cmin, cmax + 1)
        submask = np.ascontiguousarray(labels[:, cslice])
        submask = flood_fill(submask, (0, 0), 2)
        submask = flood_fill(submask, (shape[0]-1, 0), 3)
        labels[:, cslice] = submask

        # Find distance from edge to region
        upper = (labels == 2).sum(axis=0).astype(np.float64)
        lower = (labels == 3).sum(axis=0).astype(np.float64)

        # Reject areas of high change
        ugood = np.abs(np.gradient(upper[cslice])) < gradient_cutoff
        lgood = np.abs(np.gradient(lower[cslice])) < gradient_cutoff

        # Give areas slightly farther from edge a cost break
        costs_upper = np.ones_like(upper)
        costs_lower = np.ones_like(lower)
        costs_upper[cslice][ugood] = upper[cslice].min() / np.maximum(upper[cslice][ugood], 1)
        costs_lower[cslice][lgood] = lower[cslice].min() / np.maximum(lower[cslice][lgood], 1)

        # Expand from 1d back to 2d
        vdist = mask.shape[0]
        costs_upper = costs_upper[np.newaxis, :].repeat(vdist, axis=0)
        costs_lower = costs_lower[np.newaxis, :].repeat(vdist, axis=0)

        # Place these in output array
        costs_arr[:, cslice] = costs_upper[:, cslice] * (labels[:, cslice] == 2)
        costs_arr[:, cslice] +=  costs_lower[:, cslice] * (labels[:, cslice] == 3)

        # Finally, place the difference image
        costs_arr[mask] = diff_image[mask]

        return costs_arr
    def add_alpha(img, mask=None):
        """
        Adds a masked alpha channel to an image.
        
        Parameters
        ----------
        img : (M, N[, 3]) ndarray
            Image data, should be rank-2 or rank-3 with RGB channels
        mask : (M, N[, 3]) ndarray, optional
            Mask to be applied. If None, the alpha channel is added
            with full opacity assumed (1) at all locations.
        """
        from skimage.color import gray2rgb
        if mask is None:
            mask = np.ones_like(img)
            
        if img.ndim == 2:
            img = gray2rgb(img)
        
        return np.dstack((img, mask))
    pano0, pano1, pano2 = [rgb2gray(im) for im in pano_imgs]
    
    if mode==1:
        orb = ORB(n_keypoints=800, fast_threshold=0.05)

        # Detect keypoints in pano0
        orb.detect_and_extract(pano0)
        keypoints0 = orb.keypoints
        descriptors0 = orb.descriptors

        # Detect keypoints in pano1
        orb.detect_and_extract(pano1)
        keypoints1 = orb.keypoints
        descriptors1 = orb.descriptors

        # Detect keypoints in pano2
        orb.detect_and_extract(pano2)
        keypoints2 = orb.keypoints
        descriptors2 = orb.descriptors
        np.savetxt(config_path+'k0'+traySide+'.txt',keypoints0,delimiter=',')
        np.savetxt(config_path+'d0'+traySide+'.txt',descriptors0,delimiter=',')
        
        np.savetxt(config_path+'k1'+traySide+'.txt',keypoints1,delimiter=',')
        np.savetxt(config_path+'d1'+traySide+'.txt',descriptors1,delimiter=',')
        
        np.savetxt(config_path+'k2'+traySide+'.txt',keypoints2,delimiter=',')
        np.savetxt(config_path+'d2'+traySide+'.txt',descriptors2,delimiter=',')
        
        print("save Keypoint and Descriptors")
    elif mode == 0:
        keypoints0 = np.loadtxt(config_path+'k0'+traySide+'.txt',delimiter=',')
        descriptors0 = np.loadtxt(config_path+'d0'+traySide+'.txt',delimiter=',')
        
        keypoints1= np.loadtxt(config_path+'k1'+traySide+'.txt',delimiter=',')
        descriptors1 = np.loadtxt(config_path+'d1'+traySide+'.txt',delimiter=',')
        
        keypoints2 = np.loadtxt(config_path+'k2'+traySide+'.txt',delimiter=',')
        descriptors2 = np.loadtxt(config_path+'d2'+traySide+'.txt',delimiter=',')
        
        print("load Keypoint and Descriptors")
    # Match descriptors between left/right images and the center
    matches01 = match_descriptors(descriptors0, descriptors1, cross_check=True)
    matches12 = match_descriptors(descriptors1, descriptors2, cross_check=True)
    # Select keypoints from 
    #   * source (image to be registered): pano0
    #   * target (reference image): pano1, our middle frame registration target
    src = keypoints0[matches01[:, 0]][:, ::-1]
    dst = keypoints1[matches01[:, 1]][:, ::-1]

    model_robust01, inliers01 = ransac((src, dst), ProjectiveTransform,
                                    min_samples=4, residual_threshold=1, max_trials=300)

    # Select keypoints from 
    #   * source (image to be registered): pano2
    #   * target (reference image): pano1, our middle frame registration target
    src = keypoints2[matches12[:, 1]][:, ::-1]
    dst = keypoints1[matches12[:, 0]][:, ::-1]

    model_robust12, inliers12 = ransac((src, dst), ProjectiveTransform,
                                    min_samples=4, residual_threshold=1, max_trials=300)
    # Shape of middle image, our registration target
    r, c = pano1.shape[:2]

    # Note that transformations take coordinates in (x, y) format,
    # not (row, column), in order to be consistent with most literature
    corners = np.array([[0, 0],
                        [0, r],
                        [c, 0],
                        [c, r]])

    # Warp the image corners to their new positions
    warped_corners01 = model_robust01(corners)
    warped_corners12 = model_robust12(corners)

    # Find the extents of both the reference image and the warped
    # target image
    all_corners = np.vstack((warped_corners01, warped_corners12, corners))

    # The overall output shape will be max - min
    corner_min = np.min(all_corners, axis=0)
    corner_max = np.max(all_corners, axis=0)
    output_shape = (corner_max - corner_min)

    # Ensure integer shape with np.ceil and dtype conversion
    output_shape = np.ceil(output_shape[::-1]).astype(int)
    # This in-plane offset is the only necessary transformation for the middle image
    offset1 = SimilarityTransform(translation= -corner_min)

    # Translate pano1 into place
    pano1_warped = warp(pano1, offset1.inverse, order=3,
                        output_shape=output_shape, cval=-1)

    # Acquire the image mask for later use
    pano1_mask = (pano1_warped != -1)  # Mask == 1 inside image
    pano1_warped[~pano1_mask] = 0      # Return background values to 0
    
    # Warp pano0 (left) to pano1
    transform01 = (model_robust01 + offset1).inverse
    pano0_warped = warp(pano0, transform01, order=3,
                        output_shape=output_shape, cval=-1)

    pano0_mask = (pano0_warped != -1)  # Mask == 1 inside image
    pano0_warped[~pano0_mask] = 0      # Return background values to 0
    # Warp pano2 (right) to pano1 
    transform12 = (model_robust12 + offset1).inverse
    pano2_warped = warp(pano2, transform12, order=3,
                        output_shape=output_shape, cval=-1)

    pano2_mask = (pano2_warped != -1)  # Mask == 1 inside image
    pano2_warped[~pano2_mask] = 0      # Return background values to 0
    merged = (pano0_warped + pano1_warped + pano2_warped)
    # Track the overlap by adding the masks together
    overlap = (pano0_mask * 1.0 +  # Multiply by 1.0 for bool -> float conversion
           pano1_mask + 
           pano2_mask)
    # Normalize through division by `overlap` - but ensure the minimum is 1
    normalized = merged / np.maximum(overlap, 1)
    rmax = output_shape[0] - 1
    cmax = output_shape[1] - 1

    # Start anywhere along the top and bottom, left of center.
    mask_pts01 = [[0,    cmax // 3],
                [rmax, cmax // 3]]

    # Start anywhere along the top and bottom, right of center.
    mask_pts12 = [[0,    2*cmax // 3],
                [rmax, 2*cmax // 3]]
    costs01 = generate_costs(np.abs(pano0_warped - pano1_warped),
                         pano0_mask & pano1_mask)
    costs01[0,  :] = 0
    costs01[-1, :] = 0
    

    # Arguments are:
    #   cost array
    #   start pt
    #   end pt
    #   can it traverse diagonally
    pts, _ = route_through_array(costs01, mask_pts01[0], mask_pts01[1], fully_connected=True)

    # Convert list of lists to 2d coordinate array for easier indexing
    pts = np.array(pts)
    mask0 = np.zeros_like(pano0_warped, dtype=np.uint8)
    mask0[pts[:, 0], pts[:, 1]] = 1
    # Labeling starts with one at point (0, 0)
    mask0 = flood_fill(mask0, (0, 0), 1, connectivity=1)
    costs12 = generate_costs(np.abs(pano1_warped - pano2_warped),
                         pano1_mask & pano2_mask)
    costs12[0,  :] = 0
    costs12[-1, :] = 0
    
    costs12[mask0 > 0] = 1
    pts, _ = route_through_array(costs12, mask_pts12[0], mask_pts12[1], fully_connected=True)
    pts = np.array(pts)
    mask2 = np.zeros_like(pano0_warped, dtype=np.uint8)
    mask2[pts[:, 0], pts[:, 1]] = 1
    mask2 = flood_fill(mask2, (rmax, cmax), 1, connectivity=1)
    mask1 = ~(mask0.astype(np.bool) | mask2.astype(np.bool))
    pano0_color = warp(pano_imgs[0], (model_robust01 + offset1).inverse, order=3,
                   output_shape=output_shape, cval=0)

    pano1_color = warp(pano_imgs[1], offset1.inverse, order=3,
                    output_shape=output_shape, cval=0)

    pano2_color = warp(pano_imgs[2], (model_robust12 + offset1).inverse, order=3,
                    output_shape=output_shape, cval=0)
    pano0_final = add_alpha(pano0_color, mask0)
    pano1_final = add_alpha(pano1_color, mask1)
    pano2_final = add_alpha(pano2_color, mask2)
    # Start with empty image
    pano_combined = np.zeros_like(pano0_color)

    # Place the masked portion of each image into the array
    # masks are 2d, they need to be (M, N, 3) to match the color images
    pano_combined += pano0_color * gray2rgb(mask0)
    pano_combined += pano1_color * gray2rgb(mask1)
    pano_combined += pano2_color * gray2rgb(mask2)

    return pano_combined
def applyPerspective(img,pts,w,h,traySide,mode=0,):
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
        if traySide == 'l':
            trayname = 'LeftTray'
        elif traySide == 'r':
            trayname = 'RightTray'
        x1,y1,x2,y2,x3,y3,x4,y4 = np.loadtxt(config_path+trayname+'.txt')
        temp_rect[0] = np.array([x1,y1])
        temp_rect[1] = np.array([x2,y2])
        temp_rect[2] = np.array([x3,y3])
        temp_rect[3] = np.array([x4,y4])
    elif mode == 1:
        if traySide == 'l':
            trayname = 'LeftTray'
        elif traySide == 'r':
            trayname = 'RightTray'
        check = selectPoint(img,name=trayname)
        if check :
            x1,y1,x2,y2,x3,y3,x4,y4 = np.loadtxt(config_path+trayname+'.txt')
        temp_rect[0] = np.array([x1,y1])
        temp_rect[1] = np.array([x2,y2])
        temp_rect[2] = np.array([x3,y3])
        temp_rect[3] = np.array([x4,y4])
    dst = np.array([[0,0],[w-1,0],[0,h-1],[w-1, h-1]], np.float32)
    M = cv2.getPerspectiveTransform(temp_rect,dst)
    warp = cv2.warpPerspective(img, M, (w, h))
    # print(temp_rect,ind,newLid)
    return warp
# find trash in tray1 coordinate
def perspecTray(Tray,panomode,persmode,traySide):
    
  
    frame = makePano(Tray.pano,traySide,mode=panomode)
    frame = cv2.normalize(frame, None, alpha = 0, beta = 255, norm_type = cv2.NORM_MINMAX, dtype = cv2.CV_8UC1)
    # return frame
    # find tray edges
        # find with tray mask with binary thresh
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    ret,mask = cv2.threshold(gray, 188, 255, cv2.THRESH_BINARY)
    
        # morph thresh mask
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN,np.ones((9,9),np.uint8))
    cv2.imshow('mask',mask)
    cv2.waitKey(0)
        # find tray contour
    _,contours,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours = np.concatenate(contours)
        # maybe select edges only top left and top right
        # return edges
    # make perspective from tray edges
    frame = applyPerspective(frame,contours,1000,400,mode=persmode,traySide = traySide )
    return frame
def make0TrayHomo(traySide):
    if traySide == 'l':
        h = np.matrix([[1,0,0,-0.5],
                    [0,cos(pi), -sin(pi), 0.5+0.4],
                    [0,sin(pi), cos(pi),0],
                    [0,0,0,1]])
    elif traySide == 'r':
        h = np.matrix([[1,0,0,0.5],
                    [0,cos(pi), -sin(pi), -0.5-0.4],
                    [0,sin(pi), cos(pi),0],
                    [0,0,0,1]])
    return h