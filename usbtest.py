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
    	for nb in range(data)
	    j = int(data[nb])
	    i = int(old_data[nb])
	    new_data.append((i * (nbr - 1) + j) / nbr)
	return (new_data)

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
while True:
    string = input('would you command this lidar ?\n')
    if (string == 'last'):
    	do_last(last)
    elif (string == 'print'):
    	do_print(last)
    elif (string == 'auto'):
    	do_auto(last)
    elif (string == 'scan'):
    	do_auto(last)
    else:
        if (string[0] >= '0' and string[0] <= '9'):
            string = last[int(string[0]) % len(last)]
        else:
            string = string + '\n'
        last.append(string)
        write_cmd(string)
        read_cmd(1)
