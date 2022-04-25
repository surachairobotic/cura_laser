import serial
import serial.tools.list_ports
import time

class LaserSerial():
    def __init__(self):
        self.laser = ""
        self.id = "VID:PID=067B:2303"
        self.port = ""
        self.buff = ""

    def __del__(self):
        self.terminate()

    def terminate(self):
        if self.port != "" and self.ser.is_open:
            self.ser.close()        
    
    def init(self, debug=False):
        ports = serial.tools.list_ports.comports()
        for port, desc, hwid in sorted(ports):
            if debug:
                print(str(port) + ", " + str(desc) + ", " + str(hwid))
            if self.id in hwid:
                self.port = port
        if self.port is "":
            print("LaserSerial device not found.")
            return False

        if debug:
            print("LaserSerial port name : " + self.port)
        self.ser = serial.Serial(self.port, 
                                 19200, 
                                 bytesize=serial.EIGHTBITS, 
                                 stopbits=serial.STOPBITS_ONE, 
                                 timeout=0,
                                 parity=serial.PARITY_NONE)  # open serial port
        '''
        while self.checkState(debug) == 0:
            self.setState(0)
            time.sleep(0.5)
        while self.checkState(debug) == 1:
            self.setState(1)
            time.sleep(0.5)
        '''
        return True

    def write(self, msg:str) -> str:
        str_as_bytes = str.encode(msg+'\n')
        self.ser.write(str_as_bytes)
        #print(msg)

    def getState(self, debug=False):
        return self.readCmd('state?', debug)
    def getIs1(self, debug=False):
        return self.readCmd('is1?', debug)
    def getImax(self, debug=False):
        return self.readCmd('imax?', debug)
    def getIa1(self, debug=False):
        return self.readCmd('ia1?', debug)
    def getTa1(self, debug=False):
        return self.readCmd('ta1?', debug)
    def getEpfq(self, debug=False):
        return self.readCmd('epfq?', debug)
    def getFreq(self, debug=False):
        return self.readCmd('freq?', debug)
    def getOfftime(self, debug=False):
        return self.readCmd('offtime?', debug)
    def getGateext(self, debug=False):
        return self.readCmd('gateext?', debug)
    def getErrors(self, debug=False):
        return self.readCmd('geterrors?', debug)
    def getWarnings(self, debug=False):
        return self.readCmd('getwarnings?', debug)


    def setState(self, n, timeout=1):
        self.write('state '+str(n))
        t = time.time()
        while time.time()-t < timeout:
            if self.checkState() == n:
                return True
        return False
    
    def setStdfreq(self, freq):
        self.write('epfq '+str(freq))
    
    def freq(self, n):
        self.write('freq '+str(n))

    def get_xxx(self, cmd):
        return self.readCmd(cmd, debug=True)

    def read(self, noPrint=False):
        n = self.ser.inWaiting()
        if (n > 0):
            # read the bytes and convert from binary array to ASCII
            data_str = self.ser.read(self.ser.inWaiting()).decode('ascii') 
            # print the incoming string without putting a new-line
            # ('\n') automatically after every print()
            if not noPrint:
                print(data_str, end='')

    def readUntilOk(self):
        self.buff = ''
        while True:
            n = self.ser.inWaiting()
            #print('n : ' + str(n))
            if (n > 0):
                data_str = self.ser.read(self.ser.inWaiting()).decode('ascii')
                self.buff = self.buff+data_str
                if 'ok' in self.buff:
                    print(self.buff)
                    break

    def readLine(self):
        buffer = []
        while True:
            oneByte = self.ser.read(1)
            print(oneByte)
            if oneByte == b"\n":    #method should returns bytes
                return buffer
            else:
                #buffer += oneByte.decode("ascii")
                buffer.append(oneByte)

    def checkState(self, debug=False):
        self.write('state?')
        msg = self.readLine()
        if debug:
            print(msg)
        if 'state? ' in msg:
            return int(msg[7])
        else:
            return -1


    def readCmd(self, cmd, debug=False, out=10):
        self.write(cmd)
        while out > 0:
            msg = self.readLine()
            if debug:
                print(msg)
            if cmd in msg:
                n = len(cmd)
                s = msg[n+1:]
                #print(s)
                if s == "":
                    s = '-1'
                return self.str2num(s)
            out = out-1
        return -1

    def str2num(self, n):
        return float(n) if '.' in n else int(n)