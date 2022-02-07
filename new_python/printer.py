import yamaha
import card
import laserserial
import gcode

class Printer():
    def __init__(self):
        self.base = yamaha.Yamaha()
        self.head = card.Card()
        self.laser = laserserial.LaserSerial()
        self.gcode = gcode.Gcode()
    
    def init(self, fname):
        return ["Card init : Pass", "Laser init : Pass", "Base init : Pass", "G-Code init : Pass"]
        if not (card_init() and laser_init() and base_init() and gcode_init(fname)):
            return False
        
        self.laser_home_position()
        
    def base_init(self):
        if not self.base.init():
            print("Base init failed.")
            return False
        print("Base init passed.")
        return True

    def laser_init(self):
        if not self.laser.init(True):
            print("Laser init failed.")
            return False
        print("Laser init passed.")
        return True

    def card_init(self):
        if not self.head.init():
            print("Head init failed.")
            return False
        print("Head init passed.")
        return True

    def gcode_init(self, fname):
        if not self.gcode.init(fname):
            print("Gcode init failed.")
            return False
        print("Gcode init passed.")
        return True
    
    def laser_home_position(self):
        self.head.card.start_list(True)
        self.head.enable_laser(True)
        self.head.card.add_point(0, 0)
        self.head.enable_laser(False)
        self.head.card.start_list(False)
        res = self.head.card.read_status()
        self.laser.setState(1)
        self.head.card.exec_list(True)        
