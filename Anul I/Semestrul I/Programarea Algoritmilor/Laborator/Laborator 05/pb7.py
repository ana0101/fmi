fin = open("pb7_obiecte.txt", "r")
date = fin.read().split("\n")
fin.close()

gMax = int(date[0])
obiecte = []
for i in range(1, len(date)):
    lista = date[i].split()
    tuplu = ("Obiect " + str(i), int(lista[0]), int(lista[1]), round(int(lista[1]) / int(lista[0]), 2))
    obiecte.append(tuplu)

obiecte.sort(key = lambda t: -t[3])

castig = 0
k = 0
p = 0

while gMax > 0:
    if gMax - obiecte[k][1] > 0:
        gMax -= obiecte[k][1]
        castig += obiecte[k][2]
    else:
        p = round(100*gMax/obiecte[k][1], 2)
        gMax = 0
        castig += round(p/100 * obiecte[k][1], 2)
    k += 1

fout = open("pb7_rucsac.txt", "w")
fout.writelines("Castig maxim: " + str(castig) + "\n\n")
fout.writelines("Obiectele incarcate: \n")

for i in range(k-1):
    fout.writelines(obiecte[i][0] + ": 100.0%" + "\n")

fout.writelines(obiecte[k-1][0] + ": " + str(p) + "%")
fout.close()
