

import matplotlib.pyplot as plt
from math import*


tkt=[]
SUM=0

def decode(L,G):                                          #decode tout raw string selon SCIP
    Ls=0
    V=0
    for i in range(len(L)):
        Ls=ord(L[i])
        V=V<<6
        V= V&~0x3f
        V= V|Ls-0x30
    print(V)
    G.append(V)

def decoupe(Code,byte,G):

    dec=''
    for Linge in Code:
        SUM=0
        for I in range (len(Linge)):
            dec=dec+Linge[I]
            SUM+=ord(Linge[I])
            if len(dec)==byte and I!=len(Linge)-1:  #on igniore le dernier caractere de la ligne c'est un check sum
                decode(dec,G)
                dec=''
            if I==len(Linge)-1 :                    #le dernier caractere de la ligne c'est un check sum
                dec=dec[:-1]
                SUM-=ord(Linge[I])
                SUM=int(bin(SUM)[-6:],2)
                SUM+=48
                tkt.append(SUM==ord(Linge[I]))

Code=r'MS0044072501003\n99b\n1l4kl\n746n6m6g6f6d6d6c6c6b6b6b6d6k6k6k6n6k6n77777575757474747676767@7GL\n7O7T7T7Y7e868:8<8F8G8T9J=O>I@L@U@U@N@L@N@N@X@[@[@[@[@]@^@_@mA7ALg\nALALAKAKAIA>A>A;@n@X@X@X@_@a@d@dA2A3A5ACAFAIALASAZAcAcAiAjZIZIZIX\nZ@YnYTYBXXXLXAWhW_WNW>W:V_VQV<UiULUHU:TmTcTLT>T0SjSUSQS1S0R^R[RZF\nRMR>R6QgQcQJQCQ:PkPiP\P\PPP<?P?A?4?4>o>o>o>o>o>d>b>]>V>V>V>W>Y>];\n>]>[>[>[>[>b>e>n?4?7?:?ALNLaLaLOLOLMLCLCLCL?L4L3KiKhKiKfK\K[K\KZ_\nKVKHK<JlJOJ6IiIdIdIbIbI\I\I\I\IeJ?JWJ[J^J_J^J^JRJLJBJBJBJBJ9J9J@@\nJ@J@JBJBJBJ?J?J<J?JHJHJ?JCJ?J=J=J@J=J=J?J<J<J:J:J9J9J9J9J9J9J;JB2\nJ;J;J;oooo000000I0HoHoHoI0I9I9I>I>I@IFIFIFIFIFIIIGIIIWIWIWI[IbIbf\nIcIfIfIjIkJ2J<J>JBJIK^KaKaKaKdKPK2K2K5K2K5K5K13b3b3b3n3n454BJLK>3\nKmKmKmKmKmL<LcLdLlM:M?MLMSMeMhNKOAOCONOSOSOSOVAhAh07P^P^PkPkQSQSP\nQ\QSQSQ\R0RGRIR_RhS1SESFSOS]T9TCTNTVTnU;UIUeV1V;VKVbW0W:WYWaX3XM5\nX]XeXeXeW:W:R1R107Q:Q:06Q:Q:QAQ7Q7QAQEQa_n`U`d`da7aYbAb`b`bab`alN\naTaTaTgFghhTiEiijKk2kelQmTn:ndoPoooooooooooooooooooooooooo000000F\n000000000000070007OhOhooooooooooooooooooooooooooooooooooooooooooB\noooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0\noooooooooo06060606oooo@a?C>T=H<O<O<4;H:d:\:W:R:R:N:@9P9K8a8\8W8PM\n887i7_7[7N7F7@746l6k6g6Q6M6M6M00000000005]5X5V5V5O5O5K5K07004[4eH\n4[4[4e4e4b4b4W4W4T4T4K4K4I4H4D4?4?4?4?44443o3l3j3j3j3n3n3n3m3e3]`\n3\3Z3Y3Y3Y3Y3O3O3O3U3]3]3^3b3^3X3_3_3_3`3`3`40440000000000000000g\n0000005i5i5d5g5g5g5d5`5[5[5W5N5M5M5M5M5M5C5A5A5C5C5F5F5A55545455F\n5?5?5?4m4m4m4k4k4l4kl\n\n'
Code=Code.split('\\n')

info=Code[:3]   #enleve les 3 premiere ligne qui ne font que donnee des infos
Code=Code[3:]
Graph=[]
GG=[]



a=int(info[0][2:6])     #recup de l'info pas de debut
b=int(info[0][6:10])    #recup de l'info pas de fin
c=int(info[0][10:12])   #recup de l'info "modulo" pas pris en compte
byte=0
if info[0][0:2]=='MD':  #recup de l'info codee sur 2 ou 3 bit
    byte=3
else:
    byte=2
theta= [i*2*pi/1024 for i in range(a-125,b-125+1)] # liste degres en radian de 44 a 725, angle mort centre en -90deg sans "modulo"
#theta2=[theta[c*i] for i in range (len(theta)//c +1)] # avec "modulo" des pas
t=[3000 for i in range (682)]
t2=[3000 for i in range (228)]                              #liste test angle mort



#       ###########                   MAIN          ########


decoupe([info[1]],2,GG)
decoupe([info[2]],4,GG)
decoupe(Code,byte,Graph)

print('time stamp ',GG[1]*10**-3,'ms')
plt.polar(theta,Graph)

plt.show()


