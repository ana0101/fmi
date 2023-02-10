def negative_pozitive(lista):
    lista1 = [x for x in lista if x<0]
    lista2 = [x for x in lista if x>0]
    return lista1, lista2

numeFisier = input("nume fisier: ")
fin = open(numeFisier, "r")
listaNumere = fin.read().split()
numere = [int(x) for x in listaNumere]

lista1, lista2 = negative_pozitive(numere)
lista1.sort()
lista2.sort()

fin = open(numeFisier, "a")
fin.writelines("\n")
linie1 = [str(x) for x in lista1]
linie1 = " ".join(linie1)
fin.writelines(linie1)
fin.writelines("\n")
linie2 = [str(x) for x in lista2]
linie2 = " ".join(linie2)
fin.writelines(linie2)
fin.close()
