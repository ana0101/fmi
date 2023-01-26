# a
def citire_numere(numeFisier):
    lista = []
    fin = open(numeFisier, "r")
    lista1 = fin.read().split("\n")
    for elem in lista1:
        lista2 = elem.split()
        lista2 = [int(x) for x in lista2]
        lista.append(lista2)
    return lista

lista = citire_numere("fisier.txt")
print(lista)


# b
def prelucrare_lista(lista):
    m = -1
    for sublista in lista:
        minim = min(sublista)
        while minim in sublista:
            sublista.remove(minim)
        if len(sublista) < m or m == -1:
            m = len(sublista)

    for sublista in lista:
        i = m
        while i < len(sublista):
            sublista.pop(i)

prelucrare_lista(lista)
print(lista)


# c
matrice = citire_numere("numere.in")
prelucrare_lista(matrice)
for linie in matrice:
    print(*linie)


# d
L = citire_numere("numere.in")
k = int(input("k = "))
lista = []
for linie in L:
    for elem in linie:
        if len(str(elem)) == k:
            if elem not in lista:
                lista.append(elem)
lista.sort(key = lambda x: (-x))
lista = [str(x) for x in lista]
rez = " ".join(lista)
fout = open("cifre.out", "w")
fout.writelines(rez)
fout.close()
