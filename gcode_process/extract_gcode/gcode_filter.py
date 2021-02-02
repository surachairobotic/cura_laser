import random

def main():
  f = open("C:/Users/PC/Desktop/UMS5_cube_10_20_30.gcode", "r")
  data = f.readlines()
  f.close()
  
  f = open("C:/Users/PC/Desktop/UMS5_cube_10_20_30_filter.gcode", "w")  
  print_cmd = ['G0', 'G1']
  for d in data:
    cmd = d.split(' ')[0]
    if d.find('LAYER') != -1:
      f.write(d)
    elif cmd in print_cmd:
      cmd = d.split(' ')
      y = [x for x in cmd if x[0] == 'X' or x[0] == 'Y']
      f.write(','.join(y))
      f.write('\n')
      
  f.close()


if __name__ == '__main__':
  main()