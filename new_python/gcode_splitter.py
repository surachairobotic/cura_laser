import os
import gcode

gcode = gcode.Gcode()

fname = "C:/ws_python/gcode2png/ear.gcode"
fout = "C:/cura_laser/ws_python/ear/"

def main():
    if not os.path.exists(fout):
        os.mkdir(fout)

    if not gcode_init(fname):
        return False

    gcode.layers_splitter(fout)

def gcode_init(fname):
    global gcode
    if not gcode.init(fname):
        print("Gcode init failed.")
        return False
    print("Gcode init passed.")
    return True

if __name__ == "__main__":
    main()
