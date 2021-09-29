import random

def main():
  f = open("C:/ws_python/gcode2png/ear.gcode", "r")
  data = f.readlines()
  print(data)
  f.close()
  
  f = open("C:/ws_python/gcode2png/ear.gcodel0_filter.gcode", "w")  
  print_cmd = ['G0', 'G1']
  for d in data:
    cmd = d.split(' ')[0]
    if d.find('LAYER') != -1:
      f.write(d)
    elif cmd in print_cmd:
      cmd = d.split(' ')
      y = [x for x in cmd if x[0] == 'X' or x[0] == 'Y']
      y = ','.join(y)
      if len(y) > 0:
        f.write(y)
        if y[-1] != '\n':
          f.write('\n')
      
  f.close()


if __name__ == '__main__':
  main()