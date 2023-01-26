fin = open("pb9_intervale.txt", "r")
date = fin.read().split("\n")
fin.close()

intervale = []
for linie in date:
    lista = linie.split()
    lista = [int(x) for x in lista]
    intervale.append((lista[0], lista[1]))

intervale.sort(key = lambda t: t[1])

fout = open("pb9_acoperire.txt", "w")
cui = 0
for tuplu in intervale:
    if tuplu[0] > cui:
        cui = tuplu[1]
        fout.writelines(str(cui) + "\n")

fout.close()
