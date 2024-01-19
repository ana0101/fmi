import numpy as np
import matplotlib.pyplot as plt
import math

# ex 1
n = 100
p = 0.3
N = 10000

# d - a
ponderi = list()
for k in range(n+1):
    pondere = math.comb(n, k) * pow(p, k) * pow(1-p, n-k)
    ponderi.append(round(pondere, 8))
print(ponderi)
print("\n")

suma_pond_cum = list()
suma_pond_cum.append(ponderi[0])
for i in range(1, n+1):
    suma_pond_cum.append(suma_pond_cum[i-1] + ponderi[i])

print(suma_pond_cum)

def binomial_zar():
    x = np.random.rand() * (n)
    for i in range(n+1):
        if x < suma_pond_cum[i]:
            return i
    return n

xa = [binomial_zar() for i in range(N)]

# d - b
def bernoulli(p):
    x = np.random.rand()
    if x <= p:
        return 1
    return 0

def binomial(n, p):
    b = 0
    for i in range(n):
        b += bernoulli(p)
    return b

xb = [binomial(n, p) for i in range(N)]

# d - c
xc = np.random.binomial(n, p, size=N)

# e - a
# plt.hist(xa, bins=50)
# plt.title("xa binomial")
# plt.show()

# e - b
plt.hist(xb, bins=50)
plt.title("xb binomial")
plt.show()

# e - c
plt.hist(xc, bins=50)
plt.title("xc binomial")
plt.show()

# f 
plt.plot(ponderi)
plt.title("ponderi binomial")
plt.show()

# g
print("binomial: ")
media_b = sum(xb) / N
print("media b = ", media_b)

xb2 = [x*x for x in xb]
var_b = sum(xb2) / N - pow(media_b, 2)
print("varianta b =", var_b)

media_c = sum(xc) / N
print("media c =", media_c)

xc2 = [x*x for x in xc]
var_c = sum(xc2) / N - pow(media_c, 2)
print("varianta c =", var_c)
print("\n")
# e[x^2] - e[x]^2


# ex 2
n = 100
p = 0.3
N = 10000
k = 25
prob = 0
ang = np.random.binomial(n, p, size=N)
for i in range(N):
    if ang[i] >= k:
        prob += 1
prob /= N
print("prob ex 2 =", prob)
print("\n")


# ex 3
# se arunca de n ori cu 2 zaruri
# probabilitatea ca cel putin 1/5 sa aiba suma 7
n = 100
p = 0
N = 100000

# calc probabilitatea ca suma sa fie 7
nr_fav = 0
for i in range(1, 7):
    for j in range(1, 7):
        if i + j == 7:
            nr_fav += 1
p = nr_fav / 36

b = np.random.binomial(n, p, size=N)

p2 = 0
for nr in b:
    if nr >= n/5:
        p2 += 1
p2 /= N
print("probabilitatea =", p2)


# ex 4
# c - a
n = 10
p = 0.3
N = 100
xa = [round(math.log(np.random.rand()) / math.log(1-p)) for i in range(N)]

# c - b
xb = np.random.geometric(p=0.3, size=N)

# d - a
plt.hist(xa, bins=5)
plt.title("xa geom")
plt.show()

# d - b
plt.hist(xb, bins=5)
plt.title("xb geom")
plt.show()

# e
n = 100
ponderi = list()
for k in range(n+1):
    pondere = pow(1-p, k-1) * p
    ponderi.append(pondere)
plt.plot(ponderi)
plt.title("ponderi geom")
plt.show()

# f - a
print("geom: ")
media_a = sum(xa) / N
print("media a = ", media_a)

xa2 = [x*x for x in xa]
var_a = sum(xa2) / N - pow(media_a, 2)
print("varianta a =", var_a)

# f - b
media_b = sum(xb) / N
print("media b = ", media_b)

xb2 = [x*x for x in xb]
var_b = sum(xb2) / N - pow(media_b, 2)
print("varianta b =", var_b)


# ex 6
# se arunca de n ori cu 2 zaruri
# probabilitatea sa fie cel putin k sume diferite de 7 inainte de prima suma care e 7
k = 5
g = np.random.geometric(p=p, size=N)
p2 = 0
for nr in g:
    if nr >= k:
        p2 += 1
p2 /= N
print("probabilitatea =", p2)
