n = int(input("n = "))
spectacole = []
for i in range(n):
    aux = input("spectacol: ").split()
    tuplu = tuple(aux)
    spectacole.append(tuplu)

spectacole.sort(key = lambda t: t[1])

nrMax = 1
f = spectacole[0][1]
for tuplu in spectacole:
    if tuplu[0] >= f:
        nrMax += 1
        f = tuplu[1]

print(nrMax)
