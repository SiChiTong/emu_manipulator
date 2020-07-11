
from scipy.spatial.transform import Rotation as R

class Trash():
    def __init__(self):
        self.x = None
        self.y = None
        self.angle = None
        self.type = None
        self.orient = None
    def setX(self, x):
        self.x = x
    def setY(self, y):
        self.y = y
    def setAngle(self, angle):
        self.angle = angle
    def setType(self, ttype):
        self.type = ttype
    def setOrient(self, orientation):
        self.orient = orientation
    def getX(self):
        return self.x
    def getY(self):
        return self.y
    def getAngle(self):
        return self.angle
    def getType(self):
        return self.type
    def getOrient(self):
        return self.orient
    def __str__(self):
        r = R.from_quat(self.angle)
        des ="\nType: {}\nx,y: {}\nAngle_quat: {}\nOrientation: {}\nAngle_eul:{}\n".format(self.type,(self.x,self.y),self.angle,self.orient,r.as_euler('zyx',degrees=True))
        return des