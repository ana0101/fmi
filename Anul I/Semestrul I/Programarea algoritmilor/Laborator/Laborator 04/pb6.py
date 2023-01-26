# a
fin = open("elevi.in", "r")
lista = fin.read().split("\n")

elevi = []
for linie in lista:
    linie = linie.split()
    elev = []
    elev.append(int(linie[0]))
    elev.append(linie[1])
    elev.append(linie[2])
    note = []
    for i in range(3, len(linie)):
        note.append(int(linie[i]))
    elev.append(note)
    elevi.append(elev)

print(elevi)


# b
def functieB(cnp, elevi):
    for linie in elevi:
        if cnp == linie[0]:
            linie[3][0] += 1
            return linie[3][0]
    return None


cnp = int(input("cnp: "))
nota = functieB(cnp, elevi)
print(nota)
print(elevi)


# c
def functieC(cnp, note, elevi):
    for linie in elevi:
        if cnp == linie[0]:
            linie[3] += note
            return linie[3]
    return None

cnp = int(input("cnp: "))
note = functieC(cnp, [10, 8], elevi)
print(note)
print(elevi)


# d
def functieD(cnp, elevi):
    for linie in elevi:
        if cnp == linie[0]:
            elevi.remove(linie)

cnp = int(input("cnp: "))
functieD(cnp, elevi)
print(elevi)


# e
elevi2 = []
for linie in elevi:
    elev = []
    elev.append(linie[1])
    elev.append(linie[2])
    elev.append(linie[3])
    elevi2.append(elev)

elevi2 = sorted(elevi2, key = lambda lista: (-sum(lista[2])/len(lista[2]), lista[0]))

fout = open("elevi.out", "w")
for linie in elevi2:
    fout.writelines(linie[0])
    fout.writelines(" ")
    fout.writelines(linie[1])
    fout.writelines(" ")
    note = [str(x) for x in linie[2]]
    note = " ".join(note)
    fout.writelines(note)
    fout.writelines("\n")


# f
from random import *
from string import *
def genereaza_coduri(elevi):
    for linie in elevi:
        cod = "".join(choices(ascii_letters, k=3) + choices(digits, k=3))
        linie.append(cod)

genereaza_coduri(elevi)
print(elevi)
