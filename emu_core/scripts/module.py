self.log('+++ Initializing Module Script +++')

# i = JointState()
# i.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
# i.position = self.getStates()

# g = JointState()
# g.name = i.name
# g.position = [1, -pi/2, pi/2, 0,0,0]

# a = self.plan(i, g)
# self.executeTrajectory(a)

# self.moveTo(self.preconfig_pose['bin_snap'],15, blocking = 1)
# time.sleep(1)
# self.moveTo(self.preconfig_pose['tray_left_1'],12, blocking = 1)
# time.sleep(1)
# self.moveTo(self.preconfig_pose['home'],12, blocking = 1)
# self.log('Moving done!')

# self.log('Hello There!')
# last_pose = self.getStates()
# self.moveTo(self.preconfig_pose['bin_snap'],8)
# self.moveDelay(last_pose, 5, 10, 'self.moveTo(self.preconfig_pose[\'bin_snap\'],10)')
# self.log('Start snap bin')

# # # self.vision.snapBinImg()
# # # self.log('Snap bin finish')
# # # self.log('find bin pose')
# # # binMsg = self.vision.getBin()
# # # self.bin_pose_publisher.publish(binMsg)

# self.log('Bin position: Done!')
# time.sleep(0.5)
# self.log('Moving to left tray 1')
# last_pose = self.getStates()
# self.moveTo(self.preconfig_pose['tray_left_1'],16)
# self.moveDelay(last_pose, 8, 18, 'self.moveTo(self.preconfig_pose[\'tray_left_1\'],17)')
# self.log('snap pano left 1')
# self.vision.snapPano('l')
# self.log('Moving to left tray 2')
# last_pose = self.getStates()
# self.moveOne(4, pi/2, 5)
# self.moveDelay(last_pose, 4, 6, 'self.moveOne(4, pi/2, 3)')
# self.log('snap pano left 2')
# self.vision.snapPano('l')
# self.log('Moving to left tray 3')
# last_pose = self.getStates()
# self.moveOne(4, (pi/2)-0.2-0.5, 5)
# self.moveDelay(last_pose, 4, 6, 'self.moveOne(4, (pi/2)-0.2-0.5, 3)')
# self.log('snap pano left 3')
# self.vision.snapPano('l')
# self.log('start Predict')
# leftTrashMsg,leftTrayImg,leftTrashNum = self.vision.findTrash('l',panomode=0,persmode=0)
# self.log('Left tray: Done!  {} '.format(leftTrashNum))

# self.log('Moving to right tray 1')
# last_pose = self.getStates()
# self.moveTo(self.preconfig_pose['tray_right_1'],10)
# self.moveDelay(last_pose, 7, 15, 'self.moveTo(self.preconfig_pose[\'tray_right_1\'],12)')
# self.log('snap pano right 1')
# self.vision.snapPano('r')
# self.log('Moving to right tray 2')
# last_pose = self.getStates()
# self.moveOne(4, pi/2, 5)
# self.moveDelay(last_pose, 4, 6, 'self.moveOne(4, pi/2, 3)')
# self.log('snap pano right 2')
# self.vision.snapPano('r')
# self.log('Moving to right tray 3')
# last_pose = self.getStates()
# self.moveOne(4, (pi/2)-0.2-0.05, 5)
# self.moveDelay(last_pose, 4, 6, 'self.moveOne(4, (pi/2)-0.2-0.05, 3)')
# self.log('snap pano right 3')
# self.vision.snapPano('r')
# self.log('start Predict')

# rightTrashMsg,rightTrayImg,rightTrashNum = self.vision.findTrash('r',panomode=0,persmode=0)
# self.log('Right tray: Done!  {} '.format(rightTrashNum))

# if leftTrashNum + rightTrashNum == 0:
#     pass
# else:
#     if leftTrashNum != 0:
#         self.left_tray_publisher.publish(leftTrayImg)
#         self.trash_poses_publisher.publish(leftTrashMsg)

#         time.sleep(0.1)
#     else:
#         # self.left_tray_publisher.publish(leftTrayImg)
#         pass
#     time.sleep(0.1)
#     if rightTrashNum != 0:
#         self.right_tray_publisher.publish(rightTrayImg)
#         self.trash_poses_publisher.publish(rightTrashMsg)		

#         time.sleep(0.1)
#     else:
#         # self.right_tray_publisher.publish(rightTrayImg)
#         pass
# last_pose = self.getStates()
# config_togo = self.pickTrashCfg(leftTrashMsg)
# for i in config_togo:
#     self.moveTo(i, 15)
#     self.moveDelay(last_pose, 5, 18, 'self.moveTo(i, 15)')
#     self.moveTo(self.preconfig_pose['home'], 15)
#     self.moveDelay(last_pose, 5, 18, 'self.moveTo(self.preconfig_pose[\'home\'], 15)')
