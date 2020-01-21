import subprocess
from matplotlib import *
import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

#
# Fonction d'affichage de la map utilisant pyplot
# Si nous sommes dans une raspberry minimale, la creation de fenetre n'est pas possible.
# 	il faut donc installer un systeme de gestion de fenetre, type "startx"
# 	la commande startx permet de lancer une interface avec fenetre ouvrable
#	(et curseur de souris) les arguments de la commande permet de gerer la taille de la fenetre
#	(a adapter donc). Quelques raccourcis ont ete mis en place sur notre raspberry, appellé ""
#	ils permettent de substituer un mot cle par une commande:
#	un terminal colore, lisible et a la taille de notre ecran embarque
#	startx:
#	un peu plus grand (ecran de la salle "valrob, tp5")
#	startbig:
#	encore plus grand (ecran de la salle "meca, tp6")
#	startmax:
#

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
