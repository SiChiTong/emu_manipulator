class Bin():
    def __init__(self,holePtsPixel = None,color=None,position=None):
        self.holePtsPixel = holePtsPixel
        self.color = color
        self.position = position
        self.holePtsWorld = None
        self.holeRealPtsWorld = None
        
    def setColor(self,color):
        self.color = color
        
    def setHolePtsPixel(self,holePtsPixel):
        self.holePtsPixel = holePtsPixel
        
    def setHolePtsWorld(self,scaleWorld,scalePix):
        x = self.getHolePtsPixel(0)
        y = self.getHolePtsPixel(1)
        self.holePtsWorld = (self.pixToWorld(x,scaleWorld,scalePix),self.pixToWorld(y,scaleWorld,scalePix))
    def setHoleRealPtsWorld(self,pts):
        self.holeRealPtsWorld = pts
    def setPosition(self,position):
        self.position = position
        
    def getColor(self):
        return self.color
    
    def getHolePtsPixel(self,xy=None):
        if xy != None:
            return self.holePtsPixel[xy]
        else:
            return self.holePtsPixel
        
    def getHolePtsWorld(self,xy=None):
        if xy != None:
            return self.holePtsWorld[xy]
        else:
            return self.holePtsWorld
        
    def getHoleRealPtsWorld(self,xyz=None):
        if xyz != None:
            return self.holeRealPtsWorld[xy]
        else:
            return self.holeRealPtsWorld
        
    def getPosition(self):
        return self.position
    
    @staticmethod
    def pixToWorld(pix,scaleWorld,scalePix):
        scalePerOnePix = scaleWorld/scalePix
        return pix * scalePerOnePix
    
    def __str__(self):
        des =   """
        PixCoor : {}
        Color : {}
        Position: {}
        WolrdCoor: {}""".format(self.getHolePtsPixel(), self.getColor(), self.getPosition(), self.getHolePtsWorld())
        
        return des