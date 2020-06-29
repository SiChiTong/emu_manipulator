import serial
import time
from colorama import init
from termcolor import cprint 
import sys
import binascii
import struct
init(strip=not sys.stdout.isatty())

def floatToBin(data):
    return int.from_bytes(struct.pack('<f', data), byteorder=sys.byteorder)

def singleTo4(data):
    return [(data>>24)&0xFF, (data>>16)&0xFF, (data>>8)&0xFF, data&0xFF]

class Emuart:
    def __init__(self, port, baudrate = 1000000, device = "Emulator"):
        try:
            self.device = device
            self.port = port
            self.baudrate = baudrate
            self.ser = serial.Serial(port = port, baudrate = baudrate, timeout = 1)
            a = ("{} is connected via {}".format(self.device, self.ser.portstr))
            cprint (' ','white','on_green',end = ' ')
            # self.ser.set_buffer_size(rx_size = 12800, tx_size = 12800)
            cprint (a,'green')
            self.initialized = 1
        except:
            cprint (' ','white','on_red',end = ' ')
            a = ("{} is not connected".format(self.device))
            cprint (a,'red')
            self.initialized = 0

    def __str__(self):
        return self.device+'\n'+'\tport: '+self.port+'\n'+'\tbaudrate: '+str(self.baudrate)+'\n'

    def flush(self):
        self.ser.reset_input_buffer()

    def flush_out(self):
        self.ser.reset_output_buffer()

    def rts(self, state):
        self.ser.rts = state
        
    def cts(self, state):
        self.ser.cts = state

    def close(self):
        self.ser.close()

    def isInitialized(self):
        return self.initialized
    
    def readRaw(self):
        dataLen = 0
        command = 0
        read = lambda s: int.from_bytes(s.read(), byteorder=sys.byteorder)
        if read(self.ser) == 0x7E:
            if read(self.ser) == 0x77:
                crc = [0]*4
                command = read(self.ser) #get command
                dataLen = read(self.ser) #get data length
                data = [None]*dataLen
                for i in range(dataLen+4):
                    if i >= dataLen: crc[i-dataLen] = read(self.ser)
                    else: data[i] = read(self.ser)
                checksum = (crc[0]<<24)|(crc[1]<<16)|(crc[2]<<8)|crc[3] #combine crc32
                expectedCrc32 = binascii.crc32(bytes(data+[command])) #calculate crc32
                if expectedCrc32 != checksum: 
                    return -1 #if the data is wrong
                else: 
                    return command, data #the data is right
            else:
                self.ser.read() #clear the buffer until it pass if statement
            return 16, -2 #it's not start byte 2
        else:
            self.ser.read() #clear the buffer until it pass if statement
        return 16, -1 #it's not start byte 1

    def read(self):
        m,n = self.readRaw()
        if m == 88: 
            return bytes(n).decode()
        elif m == 0x0A:
            q, status, st = [], [], 0
            for _ in range(6):
                q_i = n[st:st+4]
                q.append(struct.unpack('>f', bytes(q_i))[0])
                st = st+4
            for _ in range(2):
                status =[n[-2], n[-1]]
            return [q, status]
        elif m == 0x0B: 
            q, v, status, st = [], [], [], 0
            for _ in range(6):
                q_i = n[st:st+4]
                q.append(struct.unpack('>f', bytes(q_i))[0])
                st = st+4
            for _ in range(6):
                v_i = n[st:st+4]
                v.append(struct.unpack('>f', bytes(v_i))[0])
                st = st+4
            for _ in range(2):
                status =[n[-2], n[-1]]
            return [q, v, status]
        elif m == 16: 
            return -1

    def write(self, command, data):    
        header = [0x7E, 0x77, command, len(data)]
        crc32 = binascii.crc32(bytes(data+[command]))
        crcSep = [(crc32>>24)&0xFF, (crc32>>16)&0xFF, (crc32>>8)&0xFF, crc32&0xFF]
        data = header+data+crcSep
        print(data)
        self.ser.write(bytes(data))

    def writeOls(self, jointNum, speed):
        speed = floatToBin(speed)
        self.write(40+jointNum, singleTo4(speed))

    def moveRelative(self, jointNum, increment, duration):
        print(increment, duration)
        increment = floatToBin(increment)
        duration = floatToBin(duration)
        self.write(50+jointNum, singleTo4(increment)+singleTo4(duration))
        
    def requestJointStates(self, _type = 'simple'):
        if _type is 'simple':
            self.write(0x0C, [])
        elif _type is 'full':
            self.write(0x0D, [])
        time.sleep(0.1)
        d = self.read()
        return d
    
    def setLD3(self, state):
        self.write(0x93, [state])

    def setLD4(self, state):
        self.write(0x94, [state])

if __name__ == "__main__":
    et = Emuart('COM5')
    # et = Emuart('dev/ttyTHS1')
    print (et)
    time.sleep(0.5)
    while et.isInitialized:
        # n = et.read()
        # jN = input("J >>")
        # cmd = input("I >>")
        # et.writeOls(int(jN), float(cmd))
        print (et.requestJointStates())
        cmd = input("I >>")
        et.moveRelative(1, float(cmd), 0.6)
        time.sleep(0.5)


