import pyemu
import numpy as np
import time

def cartsianJog()

if __name__ == "__main__":
    emu = pyemu.EmuRobot()
    emulator = pyemu.Emuart('COM5')
    # et = Emuart('dev/ttyTHS1')
    print (emulator)
    time.sleep(0.5)
    while emulator.established:
        cmd = input(">> ")
        cmd = 'ret = emulator.'+cmd
        try:
            exec(cmd)
            if ret is None:
                pass
            else:
                print ('Return: '+str(ret))
        except:
            print ('Wrong input!')