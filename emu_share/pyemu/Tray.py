class Tray():
    def __init__(self):
        self.pano = []
    def addPano(self,img):
        self.pano.append(img)
    def clearPano(self):
        self.pano = []