# Hodivoianu Anamaria
# 232
# Laborator 2

import numpy as np

# Ex 1
# a
def aruncare_corecta():
    x = np.random.rand()
    if x < 0.5:
        return 'H'
    else:
        return 'T'


# Ex 3
def secventa(nr, k):
    N = 10000
    p = 0
    rez = [0] * (nr)
    for i in range(N):
        # rez - aruncarile
        for j in range(nr):
            rez[j] = aruncare_corecta()

        # verific daca exista secventa
        lh = 0
        lt = 0
        ok = False

        if rez[0] == 'H':
            lh += 1
        else:
            lt += 1

        for j in range(1, nr):
            if rez[j] == rez[j-1]:
                if rez[j] == 'H':
                    lh += 1
                    if lh >= k:
                        ok = True
                else:
                    lt += 1
                    if lt >= k:
                        ok = True
            else:
                if rez[j] == 'H':
                    lh = 1
                    lt = 0
                else:
                    lt = 1
                    lh = 0

        if ok:
            p += 1

    p /= N
    return p
    
print("Probabilitate cu 10 si 4: ", secventa(10, 4))
print("Probabilitate cu 20 si 4: ", secventa(20, 4))


# Ex 4
zar1 = [1, 4]
p1 = [1/6, 5/6]

zar2 = [3, 6]
p2 = [5/6, 1/6]

zar3 = [2, 5]
p3 = [1/2, 1/2]

def aruncare_zar(zar, p):
    x = np.random.rand()
    if x < p[0]:
        return zar[0]
    else:
        return zar[1]

# probabilitatea ca zar1 sa bata zar2    
def prob_castig(zar1, p1, zar2, p2):
    N = 10000
    fav = 0
    for i in range(N):
        rez1 = aruncare_zar(zar1, p1)
        rez2 = aruncare_zar(zar2, p2)
        if rez1 > rez2:
            fav += 1
    return fav / N
