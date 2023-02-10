# a
def min_max(lista):
    minim = maxim = lista[0]
    for elem in lista:
        if elem < minim:
            minim = elem
        if elem > maxim:
            maxim = elem
    return minim, maxim

minim, maxim = min_max([3, -3, 1, 7, 3, 2])
print(minim, maxim)


# b
def incarca_fisier(numeFisier):
    fin = open(numeFisier, "r")
    text = fin.read().split("\n")
    fin.close()
    lista = []
    for linie in text:
        linie1 = [int(x) for x in linie.split()]
        lista.append(linie1)
    return lista

lista = incarca_fisier("fisier.txt")
print(lista)


# c
numeFisier = input("nume fisier: ")
lista = incarca_fisier(numeFisier)
fout = open("egale.txt", "w")
ok = False

for i in range(len(lista)):
    minim, maxim = min_max(lista[i])
    if minim == maxim:
        fout.writelines(str(i) + "\n")

fout.close()