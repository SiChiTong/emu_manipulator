import numpy as np
class Frame():
    def __init__(self,f,wrt,H = np.identity(4)):
        self.f = f
        self.wrt = wrt
        self.H = H
    def inverse(self):
        inv = self.H.copy()
        inv[0:3,0:3]=self.H[0:3,0:3].T
        inv[0:3,3]=-1 * self.H[0:3,0:3].T * self.H[0:3,3]
        return inv
    def setRot(self,mat):
        if(mat.shape == (3,3)):
            self.H[0:3,0:3] = mat
    def setPose(self,mat):
        if(mat.shape == (3,1)):
            self.H[0:3,3] = mat