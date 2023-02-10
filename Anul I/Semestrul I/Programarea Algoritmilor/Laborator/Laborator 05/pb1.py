fin = open("pb1_tis.txt", "r")
timpi = fin.read().split()
fin.close()
timpi = [int(x) for x in timpi]

lista = []
i = 0
for timp in timpi:
    tuplu = (i, timp)
    i += 1
    lista.append(tuplu)

lista.sort(key = lambda t: t[1])

timp = 0
timpTotal = 0
for tuplu in lista:
    timp += tuplu[1]
    print(tuplu, timp)
    timpTotal += timp

print(round(timpTotal / len(lista), 2))
