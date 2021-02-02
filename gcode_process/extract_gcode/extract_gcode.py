import random

def main():
  f = open("C:/Users/PC/Desktop/UMS5_cube_10_20_30.gcode", "r")
  data = f.readlines()
  f.close()
  
  dict = {}
  for d in data:
    d = d[:-1]
    if len(d) > 0:
      if d[0] == ';':
        if not (';' in dict):
          dict[d[0]] = []
        dict[d[0]].append(d[1:])
      else:
        k = d.split(' ')
        if not (k[0] in dict):
          dict[k[0]] = []
        dict[k[0]].append(d)

  print(dict.keys())
  random.seed(1)
  for key in dict.keys():
    print('----- ' + str(key) + ' -----')
    for i in range(5):
      indx = random.randint(0, len(dict[key])-1)
      print(dict[key][indx])

if __name__ == '__main__':
  main()