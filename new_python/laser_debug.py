import yamaha
import card
import laserserial
import gcode
import keyboard as key
import time
import ctypes
import msvcrt
import math
import matplotlib.pyplot as plt

base = yamaha.Yamaha()
head = card.Card()
laser = laserserial.LaserSerial()
gcode = gcode.Gcode()
debug = False

fname = "C:/cura_laser/ws_python/ear/layer_0.gcode"
fout = "C:/cura_laser/ws_python/ear_filter.gcode"
folder = "C:/cura_laser/ws_python/ear/"

state = -1
home = -1

def main():
    global head, base, gcode, fname, laser, debug
    
    if not (card_init() and laser_init() and base_init() and gcode_init(fname)):
    #if not (laser_init()):
        return False
    
    laser_home_position()
    #cal_offset()
    #laser.laser.draw_rect()
    #print("STATUS: " + str(head.card.read_status()))
    
    state = 2
    while(True):
        if state == 0:
            time.sleep(0.5)
            state = laser_state(state, debug)
        elif state == 1:
            time.sleep(0.5)
            state = base_adjust(state)
        elif state == 2:
            time.sleep(0.5)
            state = laser_process(state)
        elif state > 2 or -1:
            break

def laser_state_info():
    print('--------------')
    print('Laser state.')
    print('--------------')
    print('    i : get info.')
    print('    g : get laser state.')
    print('0,1,2 : change laser state. [0:sleep, 1:standby, 2:on]')
    print('Enter : continue to next state.')
    print('    q : exit.')
    print('--------------')
def laser_state(state, debug):
    global laser
    laser_state_info()
    t = time.time()
    while True:
        if key.is_pressed('Enter'):
            return state+1
        elif key.is_pressed('q'):
            return -1
        elif time.time()-t > 1.0:
            if key.is_pressed('0'):
                print('Laser state : ' + str(laser.state(0)))
                t = time.time()
            elif key.is_pressed('1'):
                print('Laser state : ' + str(laser.state(1)))
                t = time.time()
            elif key.is_pressed('2'):
                print('Laser state : ' + str(laser.state(2)))
                t = time.time()
            elif key.is_pressed('g'):
                print('Laser state : ' + str(laser.checkState()))
                t = time.time()
            elif key.is_pressed('i'):
                laser_state_info()
                cal_offset()
                t = time.time()

def base_adjust_info():
    print('--------------')
    print('Base adjust mode.')
    print('--------------')
    print("UP/Down : jog.")
    print("    +/- : change current layer.")
    print("      p : read current position.")
    print("      k : change speed.")
    print("      i : base adjust info.")
    print("      h : goto home.")
    print("      s : save layer 0 position to controller.")
    print(" ")
    print("  Enter : continue to laser mode.")
    print("      b : back to prev mode.")
    print("      r : restart this mode.")
    print("      q : exit.")
    print('--------------')
def base_adjust(state):
    global base, home
    base_adjust_info()
    b_jog = False
    k=10
    #print(base.getPosition())
    layer = 1
    t = time.time()
    while True:
        if key.is_pressed('up'):
            #print("Up...")
            base.write("@JOG+.1\r\n")
            b_jog = True
        elif key.is_pressed('down'):
            #print("Down...")
            base.write("@JOG-.1\r\n")
            b_jog = True
        elif b_jog:
            base.write("@STOP.1\r\n")
            b_jog = False
        elif key.is_pressed('r'):
            print("Restarting...")
            return state
        elif key.is_pressed('Enter'):
            print("Continue...")
            return state+1
        elif key.is_pressed('q'):
            print("Exit...")
            return -1
        elif time.time()-t > 1.0:
            if key.is_pressed('i'):
                base_adjust_info()
                t = time.time()
            elif key.is_pressed('b'):
                return state-1
            elif key.is_pressed('h'):
                print("Home...")
                base.gohome()
                t = time.time()
            elif key.is_pressed('p'):
                print("Position : " + str(base.getPosition()*0.01) + " mm.")
                t = time.time()
            elif key.is_pressed('+'):
                layer = layer+1
                if layer > 5:
                    layer = 5
                base.point(layer+1)
                print("Layer " + str(layer) + " : " + str(base.getPosition()*0.01) + " mm.")
                t = time.time()
            elif key.is_pressed('-'):
                layer = layer-1
                if layer < 0:
                    layer = 0
                base.point(layer+1)
                print("Layer " + str(layer) + " : " + str(base.getPosition()*0.01) + " mm.")
                t = time.time()
            elif key.is_pressed('s'):
                print("Set home : Start")
                home = base.getPosition()
                for i in range(7):
                    base.createPoint(i+1, int(home-(i*10)))
                print("Set home : Finished")
                base_adjust_info()
                t = time.time()
            elif key.is_pressed('k'):
                time.sleep(0.5)
                flush_input()
                _k = input("Enter speed [1-10]: ")
                _k = int(_k)
                if _k < 1 or _k > 10:
                    print(str(_k) + "is invalid speed. please enter number between 1-10.")
                    return state
                else:
                    k = _k
                    base.setSpeed(k)
                    time.sleep(0.5)
                t = time.time()
    return state+1

def laser_process_info():
    print('--------------')
    print('Laser process.')
    print('--------------')
    print("i : laser process info.")
    print('pos : get base position.')
    print('y<x> : execute layer x. eq. y5 --> layer 5')
    print('<x> : control base to layer x. : [x = 1 to 5]')
    print('<a>-<b> : automate layer <a> to <b>')
    print('')
    print('p : adjust power : x')
    print('')
    print('b : back to prev state.')
    print('q : exit.')
    print('--------------')
def laser_process(state):
    global base, home, head
    laser_process_info()
    layer = 0
    while True:
        flush_input()
        msg = input("Enter cmd : ")
        if msg == "p":
            print("epfq 20000")
            cmd = input("Enter power cmd : ")
            if 'epfq?' in cmd:
                print('epfq = ' + str(laser.get_epfq()))
            elif 'epfq ' in cmd:
                laser.epfq(int(cmd[5:]))
            elif 'freq?' in cmd:
                print('freq = ' + str(laser.get_freq()))
            elif 'freq ' in cmd:
                laser.freq(int(cmd[5:]))
            elif '?' in cmd:
                print('freq = ' + str(laser.get_xxx(cmd)))
            else:
                print('freq = ' + str(laser.get_xxx(cmd)))

        elif msg == 'i':
            laser_process_info()
        elif msg == "q":
            flush_input()
            return -1
        elif msg == "b":
            flush_input()
            return state-1
        elif msg.isnumeric():
            res = base.point(int(msg)+1, True)
            print("Layer[" + msg + "/5] : " + str(base.getPosition()*0.01) + " mm.")
        elif msg == "pos":
            print("Position : " + str(base.getPosition()*0.01) + " mm.")
        elif len(msg)>=2 and msg[0] == "y":
            num = int(msg[1:])
            if num < 0 or num > 5:
                print("Reject cmd. please enter only layer 0 to layer 5.")
            else:
                print('Layer ' + str(num))
                execute_layer(num)
        else:
            x = msg.split('-')
            if x == -1:
                print("Invalid command.")
                continue
            print(x)
            if not (x[0].isnumeric() and x[1].isnumeric()):
                print("Invalid command.")
                continue
            a = int(x[0])
            b = int(x[1])+1
            print(a)
            print(b)
            #for i in range(a, b):
            if True:
                i = 0
                print("Base moving : " + str(i))
                res = base.point(int(i)+1, True)
                print(res)
                print("Layer Loading : " + str(i))
                fname = "C:/cura_laser/ws_python/ear/layer_" + str(i) + ".gcode"
                gcode_init(fname)
                print("Init : pass")
                exec_laser(True)
                print("Laser Excuting...")
                time.sleep(0.01)
                s = head.card.read_status()
                #print("before : " + bin(s)[8] + ": s")
                while bin(s)[8] != '1':
                    #print(bin(s)[8] + ": s")
                    s = head.card.read_status()                    
                    time.sleep(1)
                laser.state(1)
                print("Layer finished : " + str(i))
            print("OK")
    flush_input()
    return state+1

def execute_layer(layer):
    global base
    print("----- execute_layer : " + str(layer) + " : start -----")
    laser_home_position()
    print("Moving base to layer " + str(layer) + '.')
    res = base.point(layer+1, True)
    print("Base finished. Position : " + str(base.getPosition()*0.01) + " mm.")

    print("Layer Loading : " + str(layer))
    fname = "C:/cura_laser/ws_python/ear/layer_" + str(layer) + ".gcode"
    print(fname)
    gcode_init(fname)
    print('Layer load finished.')

    exec_laser(True)
    print("Laser Excuting...")
    time.sleep(0.01)
    s = head.card.read_status()
    #print("before : " + bin(s)[8] + ": s")
    while bin(s)[8] != '1':
        #print(bin(s)[8] + ": s")
        s = head.card.read_status()                    
        time.sleep(1)
    laser.state(1)
    laser_home_position()
    print("----- execute_layer : " + str(layer) + " : end -----")

def base_init():
    global base
    if not base.init():
        print("Base init failed.")
        return False
    print("Base init passed.")
    return True

def laser_init():
    global laser
    if not laser.init():
        print("Laser init failed.")
        return False
    print("Laser init passed.")
    return True

def card_init():
    global head
    if not head.init():
        print("Head init failed.")
        return False
    print("Head init passed.")
    return True

def gcode_init(fname):
    global gcode
    if not gcode.init(fname):
        print("Gcode init failed.")
        return False
    print("Gcode init passed.")
    return True

def rect1():
    global head
    #head.card.draw_rect()
    
    step_period = ctypes.c_ushort(60)
    jump_del = ctypes.c_ushort(300)
    mark_del = ctypes.c_ushort(300)
    poly_del = ctypes.c_ushort(50)
    laser_off_del = ctypes.c_ushort(300)
    laser_on_del = ctypes.c_ushort(200)
    t1 = ctypes.c_ushort(320)
    t2 = ctypes.c_ushort(200)
    t3 = ctypes.c_ushort(0)
    head.card.setDelays(step_period, jump_del, mark_del, poly_del, laser_off_del, laser_on_del, t1, t2, t3)
    #head.card.longDelays(60000)
    head.card.set_speed(ctypes.c_double(1367.2), ctypes.c_double(450.0))
    #head.card.set_mark_speed(ctypes.c_double(480.0))

    head.card.start_list(True)
    head.enable_laser(False)
    #head.laser_on(True)
    port = ctypes.c_ushort(12)
    val = ctypes.c_ushort(1)
    head.card.write_port_list(port, val)
    val = ctypes.c_ushort(0)
    head.card.writeDA(val)
    head.card.add_point(0,10000)
    head.card.add_point(10000,10000)
    head.card.add_point(10000,0)
    head.card.add_point(0,0)
    #head.card.start_laser_manually(ctypes.c_bool(False))
    #head.laser_on(False)
    head.enable_laser(False)
    head.card.start_list(False)
    #head.card.start_laser_manually(ctypes.c_bool(True))
    head.card.exec_list(True)    

def rect2():
    global head
    #head.card.set_speed(ctypes.c_double(10.0), ctypes.c_double(10.0))
    #port = ctypes.c_ushort(12)
    #val = ctypes.c_ushort(65535)
    #head.card.write_port_list(port, val)
    head.enable_laser(True)
    #head.laser_on(True, 65535)
    head.card.start_list(True)
    #val = ctypes.c_ushort(255)
    #head.card.writeDA(val)
    #head.card.add_point(0,5000)
    '''
    head.card.add_point(10000,10000)
    head.card.add_point(20000,0)
    head.card.add_point(0,0)
    '''
    head.card.start_list(False)
    head.card.exec_list(True)

def exec_laser(status:bool, k=900):
    global head, gcode, laser


    step_period = ctypes.c_ushort(60)
    jump_del = ctypes.c_ushort(500)
    mark_del = ctypes.c_ushort(500)
    poly_del = ctypes.c_ushort(500)
    laser_off_del = ctypes.c_ushort(300)
    laser_on_del = ctypes.c_ushort(200)
    t1 = ctypes.c_ushort(320)
    t2 = ctypes.c_ushort(200)
    t3 = ctypes.c_ushort(0)
    head.card.setDelays(step_period, jump_del, mark_del, poly_del, laser_off_del, laser_on_del, t1, t2, t3)

    head.card.set_speed(ctypes.c_double(1300.0), ctypes.c_double(400.0))

    x = []
    y = []
    for i in range(len(gcode.layers)):
        x.append(gcode.layers[i].x)
        y.append(gcode.layers[i].y)
    xx = [min(x), max(x), avg(x)]
    yy = [min(y), max(y), avg(y)]
    print("x : " + str(xx))
    print("y : " + str(yy))

    xt = []
    yt = []
    for i in range(len(gcode.layers)):
        x = ((gcode.layers[i].x-xx[0]) * k -10000)
        y = ((gcode.layers[i].y-yy[0]) * k -10000)
        xt.append(x)
        yt.append(y)
    xx = [min(xt), max(xt), avg(xt)]
    yy = [min(yt), max(yt), avg(yt)]
    print("x : " + str(xx))
    print("y : " + str(yy))

    if status:
        head.card.start_list(True)
        head.enable_laser(True)
        #head.laser_on(True)
        head.card.start_laser_manually(ctypes.c_bool(True))
    
        for i in range(len(gcode.layers)):
            x = ((gcode.layers[i].x-xx[0]) * k -10000)
            y = ((gcode.layers[i].y-yy[0]) * k -10000)
            head.card.add_point(int(x),int(y))
            for i in range(10):
                head.card.delay_one_ms()

        #head.laser_on(False)
        head.enable_laser(False)
        head.card.start_list(False)
        res = head.card.read_status()
        laser.state(2)
        head.card.exec_list(True)        
    else:
        head.card.exec_list(False)
    return res

def laser_home_position():
    head.card.start_list(True)
    head.enable_laser(True)
    head.card.add_point(0, 0)
    head.enable_laser(False)
    head.card.start_list(False)
    res = head.card.read_status()
    laser.state(1)
    head.card.exec_list(True)        

def flush_input():
    while msvcrt.kbhit():
        msvcrt.getch()

def avg(lst):
    return sum(lst) / len(lst)
    
def cal_offset():
    global gcode
    for layer in range(10):
        fname = "C:/cura_laser/ws_python/ear/layer_" + str(layer) + ".gcode"
        print(fname)
        gcode_init(fname)
        x = []
        y = []
        for i in range(len(gcode.layers)):
            x.append(gcode.layers[i].x)
            y.append(gcode.layers[i].y)
    xx = [min(x), max(x), avg(x)]
    yy = [min(y), max(y), avg(y)]
    print("x : " + str(xx))
    print("y : " + str(yy))

    off_x = (20000/(xx[1]-xx[0])) - xx[0]
    off_y = (20000/(yy[1]-yy[0])) - yy[0]
    off = [off_x, off_y]
    print("off : " + str(off))

    f = open('C:/cura_laser/ws_python/ear_debug.txt', 'w')
    base_x = xx[2]
    base_y = yy[2]
    nx = []
    ny = []
    dd = []
    for i in range(len(x)):
        d = distance(base_x, base_y, x[i], y[i])
        dd.append(d)
        if d > 20:
            msg = str(d) + ', ' + str(x[i]) + ', ' + str(y[i])
            msg = msg + '\n'
            f.write(msg)
        else:
            nx.append(x[i])
            ny.append(y[i])
    f.close()

    xx = [min(nx), max(nx), avg(nx)]
    yy = [min(ny), max(ny), avg(ny)]
    ddd = [min(dd), max(dd), avg(dd)]
    print("x : " + str(xx))
    print("y : " + str(yy))
    print("d : " + str(ddd))
    '''
    fig, axarr = plt.subplots(1, 1, sharex=True)
    axarr.plot(dd)
    plt.show()
    '''

    off_x = (20000/(xx[1]-xx[0])) - xx[0]
    off_y = (20000/(yy[1]-yy[0])) - yy[0]
    off = [off_x, off_y]
    print("off : " + str(off))

    for layer in range(10):
        fname = "C:/cura_laser/ws_python/ear/layer_" + str(layer) + ".gcode"
        print(fname)
        gcode_init(fname)
        x = []
        y = []
        for i in range(len(gcode.layers)):
            m = 1000
            x.append((gcode.layers[i].x-45) * m -10000)
            y.append((gcode.layers[i].y-50) * m -10000)
    xx = [min(x), max(x), avg(x)]
    yy = [min(y), max(y), avg(y)]
    print("x : " + str(xx))
    print("y : " + str(yy))

def distance(x1,y1,x2,y2):
    px = (x1-x2)*(x1-x2)
    py = (y1-y2)*(y1-y2)
    return math.sqrt(px+py)
    

if __name__ == "__main__":
    main()
