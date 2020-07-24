#!/usr/bin/env python

import rospy
from moveit_msgs.srv import GetStateValidityRequest, GetStateValidity
from moveit_msgs.msg import RobotState
from sensor_msgs.msg import JointState


class StateValidity():
    def __init__(self):
        # subscribe to joint joint states
        rospy.Subscriber("joint_states", JointState, self.jointStatesCB, queue_size=1)
        # prepare service for collision check
        self.sv_srv = rospy.ServiceProxy('/check_state_validity', GetStateValidity)
        # wait for service to become available
        self.sv_srv.wait_for_service()
        rospy.loginfo('service is avaiable')
        # prepare msg to interface with moveit
        self.rs = RobotState()
        self.rs.joint_state.name = ['joint_1','joint_2', 'joint_3','joint_4', 'joint_5','joint_6']
        self.joint_states_received = False


    def checkCollision(self, _joint_position = None):
        '''
        check if robotis in collision
        '''
        if _joint_position:
            self.rs.joint_state.position = _joint_position
            
        else:
            pass
        validity = self.getStateValidity()
        if validity.valid:
            rospy.loginfo('robot not in collision, all ok!')
            return 1
        else:
            c = []
            rospy.logwarn('robot in collision')
            for i in validity.contacts:
                c.append(i.contact_body_1+' : '+i.contact_body_2)
            rospy.logwarn(str(c))
            return 0


    def jointStatesCB(self, msg):
        '''
        update robot state
        '''
        self.rs.joint_state.position = msg.position
        self.joint_states_received = True


    def getStateValidity(self, group_name='arm', constraints=None):
        '''
        Given a RobotState and a group name and an optional Constraints
        return the validity of the State
        '''
        gsvr = GetStateValidityRequest()
        gsvr.robot_state = self.rs
        gsvr.group_name = group_name
        if constraints != None:
            gsvr.constraints = constraints
        result = self.sv_srv.call(gsvr)
        return result

# bool valid
# ContactInformation[] contacts
# CostSource[] cost_sources
# ConstraintEvalResult[] constraint_result

    def start_collision_checker(self, jointStates = None):
        if not jointStates:
            while not self.joint_states_received:
                rospy.sleep(0.1)
        else:
            self.rs.joint_state.position = jointStates
        rospy.loginfo('joint states received! continue')
        self.checkCollision()
        rospy.spin()


if __name__ == '__main__':
    rospy.init_node('collision_checker_node', anonymous=False)
    collision_checker_node = StateValidity()
    collision_checker_node.checkCollision([-3.1,-3.1,0,0,0,0])
    # collision_checker_node.start_collision_checker()