fin = open("pb2_spectacole.txt", "r")
date = fin.read().split("\n")
fin.close()

lista = []
for linie in date:
    tuplu = ()
    lista1 = linie.split(" ")
    ore = lista1[0].split("-")
    nume = ""
    for i in range(1, len(lista1)):
        nume += lista1[i] + " "
    nume = nume.strip()
    tuplu = (ore[0], ore[1], nume)
    lista.append(tuplu)

lista.sort(key = lambda t: t[1])

fout = open("pb2_programare.txt", "w")
oraSf = "00:00"

for tuplu in lista:
    if tuplu[0] >= oraSf:
        linie = tuplu[0] + "-" + tuplu[1] + " " + tuplu[2] + "\n"
        fout.writelines(linie)
        oraSf = tuplu[1]
