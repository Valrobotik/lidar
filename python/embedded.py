import subprocess
from matplotlib import *
import matplotlib.pyplot as plt
import numpy as np
from subprocess import *
#rom subprocess import run

def print_map(flag):
    ok = subprocess.call('./dec')
    file = open("tmp", "r")
    string = file.read()
    file.close()
    data = string.split()
    integ = []
    for k in data:
        j = int(k)
        integ.append(j)
    	    #if j == 0: j = 6000
    x = np.linspace(-0.5244, 3.6644, len(integ))
#plt.plot(data) #linear mode
#plt.show() #linear mode
    plt.polar(x, integ)
    if (flag == 1):
        plt.show()
