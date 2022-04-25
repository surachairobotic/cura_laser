#!/usr/bin/env python3

import time
import ctypes

def main():

    laser = ctypes.CDLL("C:\\cura_laser\\ws_python\\Debug\\laser_rect_dll.dll")
    laser.draw_rect()

if __name__ == "__main__":
    print("Start !!!")
    main()
    print("END !!!")
