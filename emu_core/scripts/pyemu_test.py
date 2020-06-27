import pyemu
import numpy as np

emu = pyemu.EmuRobot()
# emulator = pyemu.Emuart('COM5')
print (emu.getCartesianJog(np.matrix('0; 0; 0; 0; 0; 0'), np.matrix('0; 0; 0; 0; 0; 0.1')))