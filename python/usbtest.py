import serial
import subprocess
from embedded import print_map
from subprocess import *
import numpy as np
import matplotlib.pyplot as plt

serialLid = serial.Serial('/dev/ttyACM0', 115200, timeout=0.50)

#
# Fonction convertissant et transmettant une string (un ensemble de caractere)
# sur le port serial 
#

def write_cmd(string):
    if (type(string) == type('thisisastring')):
        command = []
        for char in string:
            command.append( ord(char))
        serialLid.write(command)

#
# Fonction convertissant une string (un ensemble de caractere)
# et la return (pour avoir une commande prete a envoyer)
#

def get_cmd(string):
    if (type(string) == type('thisisastring')):
        command = []
        for char in string:
            command.append( ord(char))
        return (command)

#
# Fonction lisant sur le port serial et stockant les donnees
# sur un fichier temporaire "encryptx.txt"
# Si le flag est mis a 1, la fonction ecrit la lecture sur la sortie standard (terminal)
#

def read_cmd(flag):
    f = open("encryptx.txt", 'w+')	#le flag 'w+' sert a ouvrir le fichier en ecriture
    a = 1
    while a:    
        while serialLid.in_waiting:
            data = serialLid.readline()
            if (flag == 1):
                print (data)
            f.write(data.decode())
            a = 0


# Fonction presentant les diverse commandes disponibles dans l'IHM du lidar, (fonctions de ce fichier)
#

def do_help(last):
    print ('Type one of the following key word or a raw command (PP, VV, GD..., ...) for the lidar:\n')
    print ('last  :  print the last command typed (do not store key words), start with some pre_stored data\n')
    print ('print :  print the last data set aquired\n')
    print ('auto  :  keep you in a loop, showing real time lidar datas -> problem: stuck in the loop\n')
    print ('scan  :  read servals data set, to build a more precise data set\n')

#
# Fonction affichant la derniere lecture en memoire
# call d'une fonction d'un autre fichier python
#

def do_print(last):
    print_map(1)

#
# Fonction permettant d'afficher l'historique des commandes effectuees
# (toute commande est stockee dans un historique de commande sous forme d'un tableau de string: last[]
#

def do_last(last):
    print (last)

#
# Fonction permettant de lire automatiquement et d'afficher "en temps reel" les donnees percuent par
# le lidar, les donnee s'affichent toutes les secondes et un delai de quelque seconde s'observe
#

def do_auto(last):
    string = last[1]
    cmd = get_cmd(string)
    for k in range(1000):
        serialLid.write(cmd)
        read_cmd(0)
        plt.clf()
        print_map(0)
       # print("one turn\n")
        plt.pause(0.001)
    plt.show()

#
# Fonction traitant un fichier de lecture de lidar et l'ancienne lecture puis combine les
# deux pour que le resultat equivale a la moyenne de toutes les lectures precedentes
# Return la nouvelle lecture amelioree du nouveau set de points
#

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

#
# Fonction se servant de celle ci dessu -improve- pour effectuer un certain nombre de mesure,
# et en afficher une moyenne
# La fonction demande le nombre de tour demandé et ne fonctionne pas si l'entree n'est pas numerique
# une securitee sommaire est a ajouter
#

def do_scan(last):
    string = last[1]
    number = input('combien de tours de scan ?')
    old_data = []
    for k in range(int(number)):
        write_cmd(string)
        read_cmd(0)
        old_data = improve(old_data, k)
    x = np.linspace(-0.5244, 3.6644, len(old_data))
    plt.polar(x, old_data)
    plt.show()

#
# corps du programme
# Une string est demmande a l'utilisateur, si elle n'est pas une commande connu elle est transferee au lidar
# sinon la dite commande est effectue
# en tant que programme de test de fonctionnement de lidar, le programme n'est pas "securise"
# une erreur de l'utilisateur peut necessiter de relancer le programme.
#

last = ['MS004407250103\n', 'GD0044072501\n']
while True:
    string = input('Please enter a raw command or type help for a list of premade functions\n')
    if (string == 'help'):
    	do_help(last)
    elif (string == 'last'):
        do_last(last)
    elif (string == 'print'):
        do_print(last)
    elif (string == 'auto'):
        do_auto(last)
    elif (string == 'scan'):
        do_scan(last)
    else:
        if (string[0] >= '0' and string[0] <= '9'):
            string = last[int(string[0]) % len(last)]
        else:
            string = string + '\n'
        last.append(string)
        write_cmd(string)
        read_cmd(1)
