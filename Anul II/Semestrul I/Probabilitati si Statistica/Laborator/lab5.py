import numpy as np
import matplotlib.pyplot as plt

def aruncare_zar():
    x = np.random.rand() * 6
    return int(x+1)

# ex 1
N = 500000
pa = 0
pb = 0
pc = 0
pab = 0
pac = 0
pbc = 0
pabc = 0

for i in range(N):
    zar1 = aruncare_zar()
    zar2 = aruncare_zar()

    if zar1 == 1:
        pa += 1
    if zar2 == 6:
        pb += 1
    if zar1 + zar2 == 7:
        pc += 1

    if zar1 == 1 and zar2 == 6:
        pab += 1
    if zar1 == 1 and zar1 + zar2 == 7:
        pac += 1
    if zar2 == 6 and zar1 + zar2 == 7:
        pbc += 1
    if zar1 == 1 and zar2 == 6 and zar1 + zar2 == 7:
        pabc += 1

pa /= N
pb /= N
pc /= N
pab /= N
pac /= N
pbc /= N
pabc /= N

print("pa =", pa)
print("pb =", pb)
print("pc =", pc)
print("pab =", pab, ", pa * pb =", pa * pb)
print("pac =", pac, ", pa * pc =", pa * pc)
print("pbc =", pbc, ", pb * pc =", pb * pc)
print("pabc =", pabc, ", pa * pb * pc =", pa * pb * pc)
print("\n")


# ex 2
N = 500000
pa = 0
pb = 0
pc = 0
pab = 0
pac = 0
pbc = 0
pabc = 0

for i in range(N):
    zar1 = aruncare_zar()
    zar2 = aruncare_zar()

    if zar1 <= 2:
        pa += 1
    if zar1 + zar2 == 7:
        pb += 1
    if zar2 % 2 == 0:
        pc += 1

    if zar1 <= 2 and zar1 + zar2 == 7:
        pab += 1
    if zar1 <= 2 and zar2 % 2 == 0:
        pac += 1
    if zar1 + zar2 == 7 and zar2 % 2 == 0:
        pbc += 1
    if zar1 <= 2 and zar1 + zar2 == 7 and zar2 % 2 == 0:
        pabc += 1

pa /= N
pb /= N
pc /= N
pab /= N
pac /= N
pbc /= N
pabc /= N

print("pa =", pa)
print("pb =", pb)
print("pc =", pc)
print("pab =", pab, ", pa * pb =", pa * pb)
print("pac =", pac, ", pa * pc =", pa * pc)
print("pbc =", pbc, ", pb * pc =", pb * pc)
print("pabc =", pabc, ", pa * pb * pc =", pa * pb * pc)
print("\n")

# sunt independente toate de toate


# ex 3
# a
N = 500000
a = -0.73
b = 0.12
c = 0.25
d = 0.33
px = 0
py = 0
pxy = 0

for i in range(N):
    x = np.random.rand() * 2 - 1
    y = np.random.rand() * 2 - 1
    if x >= a and x <= b:
        px += 1
    if y >= c and y <= d:
        py += 1
    if x >= a and x <= b and y >= c and y <= d:
        pxy += 1

px /= (N)
py /= (N)
pxy /= (N)

print("px =", px)
print("py =", py)
print("pxy =", pxy, ", px * py =", px * py)
print("\n")

# b
N = 500000
a = -0.73
b = 0.12
c = 0.25
d = 0.33
px = 0
py = 0
pxy = 0

for i in range(N):
    x = np.random.rand() * 2 - 1
    y = -x
    if x >= a and x <= b:
        px += 1
    if y >= c and y <= d:
        py += 1
    if x >= a and x <= b and y >= c and y <= d:
        pxy += 1

px /= N
py /= N
pxy /= N

print("px =", px)
print("py =", py)
print("pxy =", pxy, ", px * py =", px * py)
print("\n")


# ex 4
# se arunca 3 zaruri (corecte)
# se considera evenimentele:
# a = primul este par
# b = al doilea si al treilea sunt impare
# c = suma tuturor este para
N = 100000
pa, pb, pc, pab, pac, pbc, pabc = 0, 0, 0, 0, 0, 0, 0

for i in range(N):
    zar1 = aruncare_zar()
    zar2 = aruncare_zar()
    zar3 = aruncare_zar()
    a, b, c = 0, 0, 0

    if zar1 % 2 == 0:
        pa += 1
        a = 1
    if zar2 % 2 == 1 and zar3 % 2 == 1:
        pb += 1
        b = 1
    if (zar1 + zar2 + zar3) % 2 == 0:
        pc += 1
        c = 1
    
    if a and b:
        pab += 1
    if a and c:
        pac += 1
    if b and c:
        pbc += 1
    if a and b and c:
        pabc += 1

pa /= N
pb /= N
pc /= N
pab /= N
pac /= N
pbc /= N
pabc /= N

print("pa =", pa)
print("pb =", pb)
print("pc =", pc)
print("pab =", pab, ", pa * pb =", pa * pb)
print("pac =", pac, ", pa * pc =", pa * pc)
print("pbc =", pbc, ", pb * pc =", pb * pc)
print("pabc =", pabc, ", pa * pb * pc =", pa * pb * pc)
print("\n")

# (a, b), (a, c), (b, c) independente
# (a, b, c) nu independente


# ex 5
def aruncare_moneda():
    x = np.random.rand()
    if x < 0.5:
        return 'H'
    else:
        return 'T'
    
N = 100000
p_castig = 0
durata = list()

for i in range(N):
    m = 1
    M = 5
    d = 0
    while m > 0 and m < M:
        r = aruncare_moneda()
        if r == 'H':
            m += 1
        else :
            m -= 1
        d += 1
        if m == M:
            p_castig += 1
    durata.append(d)

p_castig /= N
print("prob castig =", p_castig)

plt.hist(durata)
plt.show()


# ex 6
# jucatorul arunca doua zaruri (corecte)
# daca suma zarurilor este 7, castiga 5 lei
# daca suma nu este 7, pierde 1 leu
# m = 10
# M = 30

N = 10000
p_castig = 0
durata = list()

for i in range(N):
    m = 10
    M = 30
    d = 0
    while m > 0 and m < M:
        zar1 = aruncare_zar()
        zar2 = aruncare_zar()
        if zar1 + zar2 == 7:
            m += 5
        else:
            m -= 1
        d += 1
    if m >= M:
        p_castig += 1
    durata.append(d)

p_castig /= N
print("prob castig =", p_castig)

plt.hist(durata)
plt.show()
