
from scipy.spatial.transform import Rotation as R

class Trash():
    def __init__(self):
        self.x = None
        self.y = None
        self.angle = None
        self.type = None
        self.orient = None
<<<<<<< HEAD
        self.mask=  None
        self.box = None
=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
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
<<<<<<< HEAD
    def setMask(self, mask):
        self.mask = mask
    def setBox(self, box):
        self.box = box
        
=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
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
<<<<<<< HEAD
    def getMask(self):
        return self.mask
    def getBox(self):
        return self.box[0].astype('int')
    
    def __str__(self):
        r = R.from_quat(self.angle)
        des ="""\nType: {}
        \nx,y: {}
        \nAngle_quat: {}
        \nOrientation: {}
        \nAngle_eul:{}\n""".format(self.type,(self.x,self.y),self.angle,self.orient,r.as_euler('zyx',degrees=True))
=======
    def __str__(self):
        r = R.from_quat(self.angle)
        des ="\nType: {}\nx,y: {}\nAngle_quat: {}\nOrientation: {}\nAngle_eul:{}\n".format(self.type,(self.x,self.y),self.angle,self.orient,r.as_euler('zyx',degrees=True))
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
        return des