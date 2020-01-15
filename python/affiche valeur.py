

import numpy as np
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
Code=r'GD0044072501\n00P\n?ZYDf\n02Q02L02N02N02N02I02I02I02H02G02H02H02H02E02E02E02E02D02D02D02B0U\n2D02D02>02>02<02<02<02>02;02;02:02:02:02C02C02C02C02:02:02=02=02@\n902=02902802802802802:02:02>02>02=02=02=02:02902402402602902=02=4\n02=02702702702702602:02602502402502401o01n01o01m01m01m01W01K01J01\n1K01K01`01f01l01o01o02102202202302402402402402202101n01n01l01j013\nn01j01j01X01X01X01d01m01m02401l01l01l024022026026023022022022022<\n02202202402102101l01l01l01l01k01k01k01l01m01o0230230230230280280O\n2802;02=02;02902902502402302302302702702702702=02=02=02=02>02=02V\n>02=02>02D02M02M02W02b02b02b02M02M02F02E02E02E02D02D02@02C02D02IU\n02F02F02I02F02C02C02C02C02D02D02C02D02D02D02F02H02H02H02E02E02E0U\n2G02G02G02?02>02>02<02<02902902702602302101n01k01k01k01k01k02201g\nk01k01k01l01l01l01l01l01l01j01j01j01h01h01h01h01h01l01l01k01k01kM\n01g01f01e01a01`01`01_01`01h01h01f01f01b01b01b01b01`01`01`01_01`0j\n1_01_01^01^01^01_01b01b01_01_01^01^01]01]01[01[01X01Z01Z01Z01Y01:\nY01Y01U01R01U01Y01Y01Y01_01_01\01\01^01\01\01[01[01X01Y01Y01W01WX\n01U01U01Y01Y01Y01[01\01\01[01Z01Y01Y01Y01Z01Y01X01X01X01V01W01W0\\n1W01W01Z01Z01Y01Y01Y01Y01Y01Y01Y01Y01Y01Y01Y01Y01Y01Y01W01T01T01U\nT01U01U01U01X01U01T01T01U01U01T01S01V01V01V01V01V01U01U01U01X01X;\n01Y01X01X01Y01Y01X01U01V01V01V01W01X01X01Y01Z01[01Y01\01_01`01`0h\n1`01_01\01[01[01[01\01`01`01`01b01b01b01`01b01a01a01a01c01d01i019\ni01j01d01l01c01l01h01l01h01l01m01o02102101o01o01m01l01m022022022<\n0220240240220230250230230230240240240250270270260270270290290290E\n2602002002602702702702702502502502502102001n02001n01l01l01l01l01>\nl01m02002002002002002001l01l01k01k01k01i01k01k01l01l01l01i01i01i;\n01h01h01d01d01d01d01d01i01i01i01d01d01d01b01b01b01b01b01b01b01b0P\n1c01b01b01b01a01a01b01a01a01a01`01`01^01^01\01\01Z01Z01V01V01V01P\nV01V01W01V01W01W01W01W01X01X01V01Z01T01T01Y01Y01Y01Y01X01U01X01U`\n01T01T01T01T01S01T01T01T01T01T01T01T01W01W01Y01Y01W01V01T01T01T0M\n1X01Y01Y01Y01X01V01V01V01W01Y01Y01Y01Y01T01T01T01T01Y01Z01Y01S01=\nZ01S01S01\01\01[01[01[01Q01Q01U01W01U01W01Z01Y01Y01Y01Y01Y01Y01Z2\n01^01]01]01]01a01]01a01_01_01\01[01[01[01]01_01c01c01e01`01e01e0e\n1e01`01e01e01d01d01e01d01d01e01g01h01h01i01h01m01l01l01k01k01hi\n\n'
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

x = np.linspace(-0.5244, 3.6644, len(Graph))
print('time stamp ',GG[1]*10**-3,'ms')
plt.polar(x,Graph)

plt.show()


