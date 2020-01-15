loop = 1;
while (loop):
	a =input("entrez une annee\n")
	if type(a) != type("ok"):
		print ("un nombre donc\n")
		print (type(a))
	else:
		loop = 0
b = int(a)
if b % 4 == 0:
	print ("not bissextile")
else :
	if (b % 100 == 0):
		if (b % 400):
			print ("bissextile")
		else:
			print ("not bissextile")
	else :
		print ("bissextile")
