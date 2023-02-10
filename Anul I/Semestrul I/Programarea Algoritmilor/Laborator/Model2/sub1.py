# a
def citire_numere(nume_fisier):
    fin = open(nume_fisier, "r")
    date = fin.read().split("\n")
    fin.close()
    lista = []
    for linie in date:
        linie = linie.split()
        linie = [int(x) for x in linie]
        lista.append(linie)
    return lista

lista = citire_numere("numere.in")
print(lista)

# b
def prelucrare_lista(lista):
    m = len(lista[0])
    for i in range(len(lista)):
        minim = min(lista[i])
        while minim in lista[i]:
            lista[i].remove(minim)
        if len(lista[i]) < m:
            m = len(lista[i])
    for i in range(len(lista)):
        lista[i][m:] = []

prelucrare_lista(lista)
print(lista)

# c
for linie in lista:
    print(*linie)

# d
lista = citire_numere("numere.in")
k = int(input("k = "))
elem = []

for linie in lista:
    for nr in linie:
        if len(str(nr)) == k:
            if nr not in elem:
                elem.append(nr)

elem.sort(key = lambda x: (-x))

fout = open("cifre.out", "w")

if elem == []:
    fout.writelines("Imposibil!")
else:
    elem = [str(x) for x in elem]
    elem = " ".join(elem)
    fout.writelines(elem)

fout.close()
