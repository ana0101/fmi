# a
def liste_x(x, *liste):
    k = 0
    for lista in liste:
        if x in lista:
            k += 1
    return k

nr = liste_x(3, [1, 5, 7], [3], [1, 8, 3], [])
print(nr)

# b
def liste_x(x, *liste):
    global rez
    rez = 0
    for lista in liste:
        if x in lista:
            rez += 1

rez = None
liste_x(3, [1, 5, 7], [3], [1, 8, 3], [4,3])
print(rez)
