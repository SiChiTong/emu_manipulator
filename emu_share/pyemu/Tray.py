class Tray():
    def __init__(self):
        self.pano = []
        self.trayImg=[]
<<<<<<< HEAD
        self.pickedTrash=[]
=======
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
    def addPano(self,img):
        self.pano.append(img)
    def clearPano(self):
        self.pano = []
    def addImg(self,img):
        self.trayImg = img
    def clearImg(self):
        self.trayImg = []
    def getImg(self):
<<<<<<< HEAD
        return self.trayImg
    def addPickedTrash(self,pickImg):
        self.pickedTrash = pickImg
    def getPickedTrash(self):
        return self.pickedTrash
=======
        return self.trayImg
>>>>>>> 056183dc48941ea113f96fc1b9a8e452a320c075
