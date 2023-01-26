# a
def cifra_control(n):
    s = 0
    while n > 0:
        s += n % 10
        n //= 10
    while s > 9:
        s1 = 0
        while s > 0:
            s1 += s % 10
            s //= 10
        s = s1
    return s

cf = cifra_control(638)
print(cf)


# b
def insereaza_cifra_control(lista):
    i = 0
    while i < len(lista):
        cf = cifra_control(lista[i])
        lista.insert(i+1, cf)
        i += 2

lista = [543, 3123, 64, 213, 3231]
insereaza_cifra_control(lista)
print(lista)


# c
def egale(*liste):
    listaListe = []
    for lista in liste:
        listaListe.append(lista)

    ok = True

    for i in range(len(listaListe)):
        for j in range(i+1, len(listaListe)):
            if listaListe[i] != listaListe[j]:
                ok = False

    return ok

ok = egale([1, 2], [1, 2], [1, 2])
print(ok)


# d
fin = open("numere.in", "r")
numere = fin.read().split()
fin.close()
lista = [int(x) for x in numere]
insereaza_cifra_control(lista)

i = 0
while i < len(lista):
    print(str(lista[i]) + " " + str(lista[i+1]))
    i += 2


# e
fin1 = open("numere.in", "r")
fin2 = open("numere2.in", "r")

numere1 = fin1.read().split()
numere2 = fin2.read().split()

numere1 = set(numere1)
numere2 = set(numere2)
numere1 = list(numere1)
numere2 = list(numere2)

numere1 = [int(x) for x in numere1]
numere2 = [int(x) for x in numere2]

numere1.sort(key = lambda x: x)
numere2.sort(key = lambda x: x)

insereaza_cifra_control(numere1)
insereaza_cifra_control(numere2)

i = 1
cifre1 = []
while i < len(numere1):
    cifre1.append(numere1[i])
    i += 2

i = 1
cifre2 = []
while i < len(numere2):
    cifre2.append(numere2[i])
    i += 2

if egale(cifre1, cifre2) == True:
    print("da")
else:
    print("nu")