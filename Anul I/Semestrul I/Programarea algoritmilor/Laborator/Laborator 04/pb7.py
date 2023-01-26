# a
def citire(n, lista):
    n = int(input("numar de elemente: "))
    lista = []
    for i in range(n):
        nr = int(input("element: "))
        lista.append(nr)
    return n, lista


# b
def functie(s, x, i=0, j=0):
    if j == 0:
        j = len(s)
    for k in range(i, j):
        if s[k] > x:
            return k
    return -1


# c
n = 0
lista = []
n, lista = citire(n, lista)
for i in range(len(lista)-1):
    if functie(lista, lista[i], i+1) != -1 or lista[i] == lista[i+1]:
        print("Nu")
        break
else:
    print("Da")
