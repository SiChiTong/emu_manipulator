self.log('+++ Initializing Module Script +++')

#Publishing fake Trashes and Bins ==================================================
binMsg = JointState()
binMsg.name = ['green', 'blue', 'yellow']
binMsg.position = [0.46, 0.46, 0.46]
binMsg.velocity = [0.31, 0, -0.32]

poseList = [[0.10599999999999998, 0.75, 11, -0.004222495939768292, 0.9999910852242827, -6.123179408479028e-17, -2.585533068524967e-19],
[-0.361, 0.5760000000000001, 11, 0.5650443717528625, 0.825060517750312, -5.0520386108288877e-17, 3.4598989062168507e-17],
[0.1999999999999998, 0.63, 22, 1.0, 0.0, 0.0, 6.123233995736766e-17],
[0.30600000000000005, 0.529, 13, -0.002238052132716429, 0.9999974955581895, -6.123218660453532e-17, -1.3704116903280412e-19],
[-0.07500000000000001, 0.684, 13, -0.3738952804399497, 0.927470926371674, -5.679121506416506e-17, -2.2894482920354318e-17],
[-0.275, 0.651, 13, 0.4103722017889784, 0.9119181191306959, -5.583888028389407e-17, 2.5128050168996203e-17],
[-0.258, 0.544, 13, 0.24973214185491485, 0.9683149577098129, -5.929219067629136e-17, 1.5291683408341713e-17],
[-0.356, 0.663, 13, 0.3411705121299028, 0.9400014264100985, -5.755848690235367e-17, 2.0890668782167435e-17],
[0.10799999999999998, 0.6020000000000001, 13, -0.045283614368823215, 0.9989741709722507, -6.116952604560238e-17, -2.772821669530122e-18]]
trashMsg = PoseArray()
trashMsg.header.frame_id="base_link"
now = rospy.get_rostime()
trashMsg.header.stamp = now
for trash in range(len(poseList)):
    trash_i = Pose()
    trash_i.position.x = poseList[trash][0]
    trash_i.position.y = poseList[trash][1]
    trash_i.position.z = poseList[trash][2]
    trash_i.orientation.x = poseList[trash][3]
    trash_i.orientation.y = poseList[trash][4]
    trash_i.orientation.z = poseList[trash][5]
    trash_i.orientation.w = poseList[trash][6]
    trashMsg.poses.append(trash_i)
self.bin_poses_publisher.publish(binMsg)
time.sleep(0.2)
self.trash_poses_publisher.publish(trashMsg)
#=======================================================================================

def transferTrash(self, trash, binMsg):
    i = JointState()
    i.name = self.joint_msg.name
    i.position = self.getStates()
    g = JointState()
    g.name = i.name

    pick_cfg = self.getValidPath(self.pickTrash(trash, z_offset = 0.1))
    place_cfg = self.getValidPath(self.placeTrash(trash, binMsg), q_now = pick_cfg)

    g.position = pick_cfg
    pick_path = self.plan(i, g)
    self.executeTrajectory(pick_path, blocking = 1)
    time.sleep(1)

    i.position = pick_cfg
    g.position = place_cfg
    place_path = self.plan(i, g)
    self.executeTrajectory(place_path, blocking = 1)



# a = self.placeTrash(trashMsg.poses[3], binMsg)
transferTrash(self, trashMsg.poses[2], binMsg)

# a = getTrash(self, trashMsg.poses[1] , 0.1)
# self.log(a)



# a = self.plan(i, g)
# self.executeTrajectory(a, blocking = 1)
time.sleep(0.5)

#bottle and can x_offset = 0.56
# b = self.kin_solver.computeIK(Core.toBin(binMsg, binIdx = 0, isSnack = 0,x_offset = 0.56), offset = self.offset['bottle'])
# b = self.kin_solver.leastDist(b, self.getStates())
# self.log(b)
# self. moveTo(b, 3)






# self.moveTo(self.preconfig_pose['bin_snap'],12, blocking = 1)
# time.sleep(0.5)
# self.vision.snapBinImg()
# binMsg = self.vision.getBin()
# self.bin_pose_publisher.publish(binMsg)
# test_1 = Pose()
# test_1.position.x = 0.4
# test_1.position.y = binMsg.velocity[0]
# test_1.position.z = binMsg.position[0]+0.1*sin(0.5236)
# test_1.orientation.x = 0
# test_1.orientation.y = -0.258
# test_1.orientation.z = 0
# test_1.orientation.w = 0.966
# a = self.kin_solver.computeIK(test_1, 'least_dist', self.getStates())
# self.log(np.array(a)*(180/pi))
# # self.moveTo(a,12, blocking = 1)
# time.sleep(0.5)
# self.moveTo(self.preconfig_pose['tray_left_1'],12, blocking = 1)

# self.moveTo(self.preconfig_pose['home'],10, blocking = 1)
# self.log('Moving done!')

