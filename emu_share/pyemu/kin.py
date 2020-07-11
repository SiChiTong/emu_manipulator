import numpy as np
from math import sin, cos, pi, sqrt
from scipy.spatial.transform import Rotation as R
class kinematics:
    @staticmethod
    def rot(theta, axis):
        c = cos(theta)
        s = sin(theta)

        if axis is 'x':
            H = np.matrix([[1, 0, 0, 0], [0, c, -s, 0], [0, s, c, 0], [0, 0, 0, 1]])
        elif axis is 'y':
            H = np.matrix([[c, 0, s, 0], [0, 1, 0, 0], [-s, 0, c, 0], [0, 0, 0, 1]])
        elif axis is 'z':
            H = np.matrix([[c, -s, 0, 0], [s, c, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
        else:
            print ('Incorrect axis of rotation')
        return H
    
    @staticmethod
    def transl(dist, axis):
        H = np.identity(4)

        if axis is 'x':
            idx = 0
        elif axis is 'y':
            idx = 1
        elif axis is 'z':
            idx = 2
        else:
            print ('Incorrect axis of translation')
        H[idx][3] = dist
        return H
    
    @staticmethod
    def fk(q, dh, rho):
        n = len(rho)
        prevTf = np.identity(4)
        tf = []
        for i in range(6):
            tf.append(prevTf*rot(dh[i][0]+(rho[i]*q[i]), 'z')*transl(dh[i][1]+(-rho[i]+1)*q[i], 'z')*transl(dh[i][2], 'x')*rot(dh[i][3], 'x'))
            prevTf = tf[i]
        return tf
    
    @staticmethod
    def mj(q, dh, rho):
        n = len(rho)
        J = []
        tf = fk(q, dh, rho)

        for i in range(n):
            o_n = tf[i][0:3, 3]
            z_prev = np.matrix('0; 0; 1')
            o_prev = np.matrix('0; 0; 0')
            Ji = np.matrix([[]]*n)
            for j in range(i+1):
                Jvi = np.cross(np.array(rho[j]*z_prev).reshape(3), np.array(o_n-o_prev).reshape(3)).reshape(3,1)
                Jwi = rho[j]*z_prev
                Jj = np.concatenate((Jwi, Jvi),axis=0)
                Ji = np.concatenate((Ji, Jj),axis=1)
                z_prev = tf[j][0:3, 2];
                o_prev = tf[j][0:3, 3];
            J.append(Ji)
        return J
    
    @staticmethod
    def rotm2quart(rotm):
        r = R.from_matrix(rotm)
        return r.as_quat()