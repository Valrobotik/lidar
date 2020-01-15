import serial
import subprocess
from embedded import print_map
from subprocess import *
import numpy as np
import matplotlib.pyplot as plt

serialLid = serial.Serial('/dev/ttyACM0', 9600, timeout=0.50)

def write_cmd(string):
    if (type(string) == type('thisisastring')):
        #command = [0x50, 0x50, 0x0A]
        command = []
        for char in string:
            #command.append(hex( ord(char)))
            command.append( ord(char))
        serialLid.write(command)

def read_cmd(flag):
    f = open("encryptx.txt", 'w+')
    a = 1
    while a:    
        while serialLid.in_waiting:
            data = serialLid.readline()
            if (flag == 1):
                print (data)
            f.write(data.decode())
            a = 0

def improve(old_data, nbr):
    ok = subprocess.call('./dec')
    file = open("tmp", "r")
    string = file.read()
    file.close()
    data = string.split()
    if (nbr == 0 or old_data == []):
        new_data = []
        for k in data:
            j = int(k)
            new_data.append(j)
        return (new_data)
    else:
        new_data = []
        for nb in range(len(data)):
            j = int(data[nb])
            i = int(old_data[nb])
            new_data.append((i * (nbr - 1) + j) / nbr)
        return (new_data)

def do_help(last):
    print ('Type some of the following key word or a raw command (PP, VV, GD..., ...) for the lidar:\n')
    print ('last  :  print the last command typed (do not store key words), start with some pre_stored data\n')
    print ('print :  print the last data set aquired\n')
    print ('auto  :  keep you in a loop, showing real time lidar datas -> problem: stuck in the loop\n')
    print ('scan  :  read servals data set, to build a more precise data set\n')

def do_print(last):
    print_map(1)

def do_last(last):
    print (last)
  
def do_auto(last):
    string = last[1]
    for k in range(1000):
        write_cmd(string)
        read_cmd(0)
        plt.clf()
        print_map(0)
        plt.pause(0.001)
    plt.show()

def do_scan(last):
    string = last[1]
    number = input('combien de tours de scan ?')
    for k in range(int(number)):
        write_cmd(string)
        read_cmd(0)
        old_data = improve(old_data, k)
    x = np.linspace(-0.5244, 3.6644, len(old_data))
    plt.polar(x, old_data)
    plt.show()
    
last = ['MS004407250103\n', 'GD0044072501\n']
cmd = ['help', 'last', 'print', 'auto', 'scan']
while True:
    over = 0
    string = input('what would you wish to accomplish ? type help for... help !\n')
    for cm in cmd:
        if (string == cm):
            func = local()['do_' + cm]
            func()
            over = 1
    if (over == 0):
        if (string[0] >= '0' and string[0] <= '9'):
            string = last[int(string[0]) % len(last)]
        else:
            string = string + '\n'
        last.append(string)
        write_cmd(string)
        read_cmd(1)
