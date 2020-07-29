import numpy as np
from math import sin, cos, pi, sqrt, atan, atan2
try:
    from .util import kinematics
except:
    from util import kinematics
from scipy.spatial.transform import Rotation as R
import itertools
class EmuRobot:
    def __init__(self, tool_length = 0):
        self.L1, self.L2, self.Le = 0.12596, 0.466, 0.043
        self.a1, self.a2, self.a3 = 0.30767, 0.400, 0.05 
        self.dh_param = np.array([[0, self.a1, self.L1, pi/2],
                                [pi/2, 0, self.a2, 0],
                                [0, 0, self.a3, pi/2],
                                [0, self.L2, 0, -pi/2],
                                [0, 0, 0, pi/2],
                                [0, self.Le, 0, 0]])
        self.rho = [1]*6
        self.joint_limit = np.matrix('-3.1066,3.1066;-2.917,1.703;-1.4312,4.119;-3.1067,3.1067;-3.1067,3.1067;-3.1067,3.1067')
        
    def __str__(self):
        return ('emu Robot')

    def getTransform(self, config, link_num = None):
        """
        Get the homogeneous transformation matrix of link <link_num> with respect to base. (<num_link> is not python index) 
        """
        if link_num:
            link_num -= 1
            return kinematics.fk(config, self.dh_param, self.rho)[link_num]
        else:
            return kinematics.fk(config, self.dh_param, self.rho)
    
    def getJacobian(self, config, link_num = None):
        """
        Get the jacobian matrix of link <link_num>. (<num_link> is not python index) 
        """    
        if link_num:
            link_num -= 1
            return kinematics.mj(config, self.dh_param, self.rho)[link_num]
        else:
            return kinematics.mj(config, self.dh_param, self.rho)

    def computeIK(self, pose, offset = (0,0,0)):
        tf = np.matrix(np.eye(4))
        x,y,z = pose.position.x,pose.position.y,pose.position.z
        r = EmuRobot.quat2rotm([pose.orientation.x,pose.orientation.y,pose.orientation.z,pose.orientation.w])
        tf[0:3,0:3] = r
        tf[0:3,3]=np.matrix([[x],[y],[z]])
        gr06 = tf[0:3, 0:3]
        gw = tf[0:3,3]+np.dot(gr06,np.matrix([0+offset[0], 0+offset[1], -self.Le+offset[2]]).T)
        x = gw[0]
        y = gw[1]
        z = gw[2]
        sign = np.matrix('1 1 1;1 1 -1;1 -1 1;1 -1 -1;-1 1 1;-1 1 -1;-1 -1 1;-1 -1 -1')
        p_q = np.zeros((6,8))
        for i in range(8):
            q = np.zeros(6)
            sign1 = sign[i,0]
            sign2 = sign[i,1]
            sign3 = sign[i,2]
            try:
                R = sign1*sqrt(x**2+y**2)
                k = ((R-self.L1)**2+(z-self.a1)**2-self.L2**2-self.a3**2-self.a2**2)/(2*self.a2)
                q[2] = 2*atan((-2*self.L2+sign2*sqrt(4*self.L2**2+4*(self.a3+k)*(self.a3-k)))/(-2*(self.a3+k)))
                inv = np.matrix([[-(self.L2*sin(q[2])+self.a3*cos(q[2])+self.a2), self.L2*cos(q[2])-self.a3*sin(q[2]) ],[ self.L2*cos(q[2])-self.a3*sin(q[2]), self.L2*sin(q[2])+self.a3*cos(q[2])+self.a2]])
                s2c2 = np.matrix(np.linalg.inv(inv)*np.matrix([R-self.L1, z-self.a1]).T)
                q[1] = atan2(s2c2[0], s2c2[1])
                q[0] = atan2(y/(self.L1+self.L2*cos(q[1]+q[2])-self.a3*sin(q[1]+q[2])-self.a2*sin(q[1])), x/(self.L1+self.L2*cos(q[1]+q[2])-self.a3*sin(q[1]+q[2])-self.a2*sin(q[1])));
                gr03 = np.matrix([[-sin(q[1]+q[2])*cos(q[0]), sin(q[0]), cos(q[1]+q[2])*cos(q[0])],
                        [-sin(q[1]+q[2])*sin(q[0]), -cos(q[0]), cos(q[1]+q[2])*sin(q[0])],
                        [cos(q[1]+q[2]), 0, sin(q[1]+q[2])]])
                gr = gr03.T*gr06
                c5 = gr[2, 2]
                s5 = sign3*sqrt(gr[0,2]**2+gr[1,2]**2)
                q[4] = atan2(s5, c5)
                if s5 != 0:
                    s6 = gr[2,1]/s5
                    c6 = -gr[2,0]/s5
                    q[5] = atan2(s6, c6)
                
                    c4 = gr[0,2]/s5
                    s4 = gr[1,2]/s5
                    q[3] = atan2(s4, c4)
                else:
                    q[3] = 0
                    q[5] = 0
            except:
                nan = np.nan
                q = np.matrix([nan, nan, nan, nan, nan, nan]).T
            
            for j in range(6):
                if (q[j]<self.joint_limit[j,0] or q[j]>self.joint_limit[j,1]):
                    state = 0
                    break
                else:
                    state = 1
            if state == 1:
                p_q[:,i]=q.T
            else:
                nan = np.nan
                nanm = np.matrix([nan, nan, nan, nan, nan, nan])
                p_q[:,i]=nanm
        lastq = p_q[:,~np.all(np.isnan(p_q), axis=0)]
        if type(lastq).__name__ is not 'NoneType':
            lastq = lastq.reshape(6, len(lastq[0]))
            lastq = lastq.T
            return lastq
        else:
            return None

    def computeIKranged(self,pose,offset = (0,0,0),lb = (0,0,0),ub = (0,0,0),step = 0.05):
        newpose = pose
        ikl = []
        oldorient = EmuRobot.quat2eul([pose.orientation.x, pose.orientation.y, pose.orientation.z,pose.orientation.w])
        cmb = []
        for i in range(3):
            
            if lb[i] != ub[i]:
                a = np.arange(lb[i], ub[i],step).tolist()
            else:
                a = [oldorient[i]]
            cmb.append(a)
        
        
        for cm in itertools.product(*cmb):
            
            q_star = EmuRobot.eul2quat([cm[0],cm[1],cm[2]])
            newpose.orientation.x = q_star[0]
            newpose.orientation.y = q_star[1]
            newpose.orientation.z = q_star[2]
            newpose.orientation.w = q_star[3]
            
            ik = self.computeIK(newpose,offset)
            
            if type(ik).__name__ is not 'NoneType':
                ikl = ikl+ik.tolist()
                
        return ikl
    
    def leastDist(self, soln, q_now, weight = [1.5, 1.7, 1.2, 0.8, 0.8, 0.8]):
        dist = abs(np.array(soln)-np.array(q_now))
        print (dist)
        for u in dist:
            print(u)
            for i in range(6):
                u[i] = u[i]*weight[i]
        print (dist)
        cost = np.sum(dist, axis = 1)
        print (cost)
        return list(soln[np.array(list(cost).index(min(cost)))])

    def getCartesianJog(self, q_now, increment, numDof = 6):
        # return q_now.reshape(6,1) + np.dot(np.linalg.inv(self.getJacobian( q_now, numDof)),increment.reshape(6,1))
        return np.dot(np.linalg.inv(self.getJacobian( q_now, numDof)),increment.reshape(6,1))
    
    def getToolJog(self, q_now, increment, numDof = 6):
        # return q_now.reshape(6,1) + np.dot(np.linalg.inv(self.getJacobian( q_now, numDof)),increment.reshape(6,1))
        return 0
    
    @staticmethod
    def rotm2quart(rotm):
        r = R.from_matrix(rotm)
        return r.as_quat()
    @staticmethod
    def quat2rotm(quat):
        r = R.from_quat(quat)
        return r.as_matrix()
    
    @staticmethod
    def eul2quat(eul,p='xyz'):
        r = R.from_euler(p,eul)
        return r.as_quat()
    @staticmethod
    def quat2eul(quat,p='xyz'):
        r = R.from_quat(quat)
        return r.as_euler(p)
if __name__ == '__main__':
    a = EmuRobot()
    tf = np.matrix('1 0 0 -0.5;0 1 0 0;0 0 1 0.5;0 0 0 1')
    b=EmuRobot.quat2rotm([1,0,0,0])
    print (a,b)
    # print (a.getTransform([0,0,0,0,0,0], 6).round(decimals=4))
    print (a.computeIK(a.getTransform([pi/2,0,0,0,0.00001,0], 6), 'least_dist', [pi/2, 0, 0, 0.4, 0.01, 0]).round(decimals=4))
    # print (a.getJacobian([0,0,0,0,1,0], 3).round(decimals=4))