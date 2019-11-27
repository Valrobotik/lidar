from matplotlib import *
import matplotlib.pyplot as plt
import numpy as np
from subprocess import *
#rom subprocess import run
ok = subprocess.call('./dec')
file = open("tmp", "r")
string = file.read()
file.close()
data = string.split()
integ = []
for k in data:
	j = int(k)
	#if j == 0: j = 6000
	integ.append(j)
x = np.linspace(-0.5244, 3.6644, len(integ))
#plt.plot(data) #linear mode
#plt.show() #linear mode
plt.polar(x, integ)
plt.show()
