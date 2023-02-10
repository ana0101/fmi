fin = open("pb8_proiecte.txt", "r")
date = fin.read().split("\n")
fin.close()

proiecte = []
ziMax = 0
for linie in date:
    linie = linie.split()
    lista = []
    lista.append(linie[0])
    lista.append(int(linie[1]))
    lista.append(int(linie[2]))
    proiecte.append(lista)
    if int(linie[1]) > ziMax:
        ziMax = int(linie[1])

proiecte.sort(key = lambda l: -l[2])

zile = {i: None for i in range(1, ziMax+1)}

profit = 0

for p in proiecte:
    for zi in range(p[1], 0, -1):
        if zile[zi] == None:
            zile[zi] = p[0]
            profit += p[2]
            break

fout = open("pb8_profit.txt", "w")

for zi in zile.keys():
    if zile[zi] != None:
        fout.writelines("Ziua " + str(zi) + ": " + zile[zi] + "\n")

fout.writelines("\nProfit maxim: " + str(profit))
