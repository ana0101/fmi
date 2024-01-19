import numpy as np
import matplotlib.pyplot as plt
import math

# ex 1
lam = 20
n = 100000
N = 100000
print("ex 1 poisson: ")

# c - a
xa = np.random.binomial(n, lam/n, size=N)
print(xa)

# c - b
xb = np.random.poisson(lam=lam, size=N)
print(xb)

# d - a
plt.hist(xa, bins=50)
plt.title("poisson a")
plt.show()

# d - b
plt.hist(xb, bins=50)
plt.title("poisson b")
plt.show()

# e
n2 = 50
ponderi = list()
for k in range(n2+1):
    pondere = np.exp(-lam) * pow(lam, k) / np.math.factorial(k)
    ponderi.append(pondere)
print(ponderi)
plt.plot(ponderi)
plt.title("ponderi poisson")
plt.show()

# f - a
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
print("\n")


# ex 2
lam = 150
N = 100000
p = 0

x = np.random.poisson(lam=lam, size=N)

for i in range(N):
    if x[i] > 150:
        p += 1
p /= N
print("probabilitatea ex 2 =", p)
print("\n")


# ex 3
# o pisica trece strada in medie de 20 de ori pe ora
# care e probabilitatea ca pisica sa treaca strada de mai mult de 20 de ori pe ora?
lam = 20
N = 100000
p = 0

x = np.random.poisson(lam=lam, size=N)

for i in range(N):
    if x[i] > 20:
        p += 1
p /= N
print("probabilitatea ex 3 =", p, "\n")


# ex 4
lam = 20
N = 100000

# c - a
xa = [-1/lam * math.log(np.random.rand()) for i in range(N)]
# print(xa)

# c - b
xb = np.random.exponential(scale=1/lam, size=N)
# print(xb)

# d - a
plt.hist(xa, bins=100)
plt.title("exp a")
plt.show()

# d - b
plt.hist(xb, bins=100)
plt.title("exp b")
plt.show()

# e
x = np.linspace(0, max(max(xa), max(xb)), 1000) 
plt.plot(x, lam * np.exp(-lam*x))
plt.title("densitate exp")
plt.show()

# f - a
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
print("\n")

# g - a
x = np.linspace(0, max(xa), 1000)
xa2 = np.sort(xa)
nr = np.arange(1, len(xa2) + 1) / len(xa2)
plt.plot(x, 1 - np.exp(-lam * x))
plt.plot(xa2, nr)
plt.title("cdf exp")
plt.show()


# ex 5
lam1 = 2.5
lam2 = 5
N = 100000

x1 = np.random.exponential(scale=lam1, size=N)
x2 = np.random.exponential(scale=lam2, size=N)

p1 = 1 - np.mean(x1 <= lam1)
p2 = 1 - np.mean(x2 <= lam2)

print("ex 5")
print("prob tel 1 =", p1)
print("prob tel 2 =", p2)


# ex 6
# un interviu dureaza in medie 30 de minute
# care e probabilitatea ca un interviu sa dureze mai mult de 30 de minute?
lam = 30
N = 100000
x = np.random.exponential(scale=lam, size=N)
p = 1 - np.mean(x <= lam)
print("probabilitatea ex 6 =", p, "\n")


# ex 7
lam1 = 20
lam2 = 50
N = 10000

# a
x = np.random.exponential(scale=1/lam1, size=N)
y = np.random.exponential(scale=1/lam2, size=N)

# b
z = np.minimum(x, y)
plt.hist(z, bins=1000, label="z")

# c
xy = np.linspace(0, max(z), 1000)
pdf_xy = (lam1 + lam2) * np.exp(-(lam1 + lam2) * xy)
plt.plot(xy, pdf_xy, label="cdf xy")

plt.title("ex 7")
plt.legend()
plt.show()


# ex 8
lam1 = 4
lam2 = 8
N = 10000

# a
x1 = np.random.exponential(scale=lam1, size=N)
plt.hist(x1, bins=1000)
plt.show()
p1 = np.mean(x1 > 5)
print("prob sa astepte mai mult de 5 min tramvaiul =", p1)

# b
x2 = np.random.exponential(scale=lam2, size=N)
plt.hist(x2, bins=1000)
plt.show()
p2 = np.mean(x2 > 5)
print("prob sa astepte mai mult de 5 min tramvaiul sau autobuzul =", p1 * p2)
