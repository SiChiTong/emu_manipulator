self.log('+++ Initializing Module Script +++')

binMsg = JointState()
binMsg.name = ['green', 'blue', 'yellow']
binMsg.position = [0.46, 0.46, 0.46]
binMsg.velocity = [0.31, 0, -0.32]

poseList = [[0.10599999999999998, 0.525, 11, -0.004222495939768292, 0.9999910852242827, -6.123179408479028e-17, -2.585533068524967e-19],
[-0.361, 0.5760000000000001, 11, 0.5650443717528625, 0.825060517750312, -5.0520386108288877e-17, 3.4598989062168507e-17],
[-0.03999999999999998, 0.543, 22, 1.0, 0.0, 0.0, 6.123233995736766e-17],
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
# binGenCb(binMsg)
# trashGenCb(trashMsg)

def toBin(binMsg, binIdx, isSnack = 0):
    pose = Pose()
    pose.position.x = 0.45
    pose.position.y = binMsg.velocity[binIdx]
    pose.position.z = binMsg.position[binIdx]+(0.56-0.45)*sin(0.5236)
    
    if isSnack:
        pose.orientation.x = 0.86727
        pose.orientation.y = 3e-7
        pose.orientation.z = 0.49783
        pose.orientation.w = 2e-7
    else:
        if binIdx == 0:
            pose.orientation.x = 0.24312
            pose.orientation.y = 0.3325
            pose.orientation.z = 0.9073
            pose.orientation.w = -0.08874
        elif binIdx == 1:
            pose.position.x = 0.4
            pose.position.y = binMsg.velocity[binIdx]
            pose.position.z = binMsg.position[binIdx]+(0.56-0.4)*sin(0.5236)
            pose.orientation.x = 0.2588
            pose.orientation.y = 1e-7
            pose.orientation.z = 0.9659
            pose.orientation.w = 3e-7
        elif binIdx == 2:
            pose.orientation.x = 0.24312
            pose.orientation.y = -0.3325
            pose.orientation.z = 0.9073
            pose.orientation.w = 0.08874
    return pose

BOTTLE_OFFSET = (0,0,-0.145)
SNACK_OFFSET = (0, 0.0881, -0.185)

a = self.kin_solver.computeIK(toBin(binMsg, 0, 0), offset = BOTTLE_OFFSET)
self.log(a)
vailid_path = []
for i in a:
    if self.isValid(i):
        vailid_path.append(list(i))
if vailid_path is []: 
    self.log('No config found!')
else:
    self.log('Valid Path: '+str(vailid_path))
    soln = self.kin_solver.leastDist(vailid_path, self.getStates())
self.log("soln: "+str(soln))
# self.moveTo(a,12, blocking = 1)

i = JointState()
i.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
i.position = self.getStates()

g = JointState()
g.name = i.name
g.position = soln

a = self.plan(i, g)
self.executeTrajectory(a)

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

