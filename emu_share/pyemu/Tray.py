class Tray():
    def __init__(self):
        self.pano = []
        self.trayImg=[]
    def addPano(self,img):
        self.pano.append(img)
    def clearPano(self):
        self.pano = []
    def addImg(self,img):
        self.trayImg = img
    def clearImg(self):
        self.trayImg = []
    def getImg(self):
        return self.trayImg