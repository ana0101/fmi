import numpy as np
import matplotlib.pyplot as plt

pdf_normala = lambda x, medie, varianta: ((1 / np.sqrt(2 * np.pi * varianta)) * np.exp(-(x - medie) **2 / (2 * varianta)))

# ex 1
medie = 2
varianta = 3
deviatie = np.sqrt(varianta)
N = 100000

# d - a
xa = [medie + np.sqrt(-2 * varianta * np.log(np.random.rand())) * np.cos(2 * np.pi * np.random.rand()) for i in range(N)]

# d - b
xb = [medie + np.sqrt(-2 * varianta * np.log(np.random.rand())) * np.sin(2 * np.pi * np.random.rand()) for i in range(N)]

# d - c
xc = np.random.normal(medie, deviatie, size=N)

# e
plt.hist(xa, density=True, bins=1000, label="xa")
plt.hist(xb, density=True, bins=1000, label="xb")
plt.hist(xc, density=True, bins=1000, label="xc")

# f
xf = np.linspace(min(min(xa), min(xb), min(xc)), max(max(xa), max(xb), max(xc)), 1000)
pdf = pdf_normala(xf, medie, varianta)
plt.plot(xf, pdf, label="pdf")
plt.title("ex 1")
plt.legend()
plt.show()

# g
medie_a = sum(xa) / N
medie_b = sum(xb) / N
medie_c = sum(xc) / N

xa2 = [x ** 2 for x in xa]
xb2 = [x ** 2 for x in xb]
xc2 = [x ** 2 for x in xc]

varianta_a = sum(xa2) / N - pow(medie_a, 2)
varianta_b = sum(xb2) / N - pow(medie_b, 2)
varianta_c = sum(xc2) / N - pow(medie_c, 2)

print("ex 1:")
print("medie a =", medie_a)
print("medie b =", medie_b)
print("medie c =", medie_c)

print("varianta a =", varianta_a)
print("varianta b =", varianta_b)
print("varianta c =", varianta_c)


# ex 2
medie = 0
varianta = 1
deviatie = 1
alfa = 2
beta = 1.5
N = 100000

x = np.random.normal(medie, deviatie, size=N)

# d - a
ya = [alfa + elem for elem in x]

# d - b
yb = [beta * elem for elem in x]

# d - c
yc = [alfa + beta * elem for elem in x]

# e
plt.hist(ya, density=True, bins=1000, label="ya")
xe = np.linspace(min(ya), max(ya), 1000)
pdf = pdf_normala(xe, alfa + medie, varianta)
plt.plot(xe, pdf, label="pdf")
plt.title("ex 2 e")
plt.legend()
plt.show()

# f
plt.hist(yb, density=True, bins=1000, label="yb")
xf = np.linspace(min(yb), max(yb), 1000)
pdf = pdf_normala(xf, beta * medie, beta ** 2 * varianta)
plt.plot(xf, pdf, label="pdf")
plt.title("ex 2 f")
plt.legend()
plt.show()

# g
plt.hist(yc, density=True, bins=1000, label="yc")
xg = np.linspace(min(yc), max(yc), 1000)
pdf = pdf_normala(xg, alfa + beta * medie, beta ** 2 * varianta)
plt.plot(xg, pdf, label="pdf")
plt.title("ex 2 g")
plt.legend()
plt.show()


# ex 3
lam = 30
N = 10000
n = 500

x = np.random.exponential(scale=1/lam, size=(N, n))
medie = 1 / lam
varianta = 1 / (lam ** 2)

# a
z = [(np.sqrt(n) * (np.sum(x[i]) / n - medie)) for i in range(N)]

# b
plt.hist(z, density=True, bins=1000, label="z")
xb = np.linspace(min(z), max(z), 1000)
pdf = pdf_normala(xb, 0, varianta)
plt.plot(xb, pdf, label="pdf")
plt.title("ex 3")
plt.legend()
plt.show()


# ex 4
pdf_normala = lambda x, medie, varianta: ((1 / np.sqrt(2 * np.pi * varianta)) * np.exp(-(x - medie) **2 / (2 * varianta)))

p = 0.5
n = 500
N = 10000

# a
def pas(p):
    x = np.random.rand()
    if x <= p:
        return 1
    return -1

pasi = [pas(p) for i in range(n)]
mers = np.cumsum(pasi)
plt.plot(mers)
plt.title("ex 4 a")
plt.show()

# b
pozitii = [np.sum([pas(p) for i in range(n)]) for j in range(N)]

# c
plt.hist(pozitii, density=True, bins=100, label="pozitii")

# e(x) = (1 - p) * (-1) + p * 1 = p - 1 + p = 2p - 1
medie = 2 * p - 1
# var(x) = e(x**2) - e(x)**2 = 1 - 4p**2 + 4p + 1 = 4p - 4p**2 = 4p(1 - p)
# e(x**2) = (1 - p) * 1 + p * 1 = 1
# e(x)**2 = (2p - 1)**2 = 4p**2 - 4p + 1
varianta = 4 * p * (1 - p)
x = np.linspace(min(pozitii), max(pozitii), 1000)
pdf = pdf_normala(x, n * medie, n * varianta)
plt.plot(x, pdf, label="pdf")

plt.legend()
plt.title("ex 4 c")
plt.show()


# ex 5
p1, p2, p3 = 0.25, 0.5, 0.25
x1, x2, x3 = -1 / (np.sqrt(0.5)), 0, 1 / (np.sqrt(0.5))
n = 500
N = 10000

# a
def pas(p1, p2, p3):
    x = np.random.rand()
    if x <= p1:
        return x1
    elif x <= p1 + p2:
        return x2
    else:
        return x3
    
pasi = [pas(p1, p2, p3) for i in range(n)]
mers = np.cumsum(pasi)
plt.plot(mers)
plt.title("ex 5 a")
plt.show()

# b
pozitii = [np.sum([pas(p1, p2, p3) for i in range(n)]) for j in range(N)]

# c
plt.hist(pozitii, density=True, bins=100, label="pozitii")

medie = p1 * x1 + p2 * x2 + p3 * x3
varianta = p1 * (x1**2) + p2 * (x2**2) + p3 * (x3**2) - medie**2
x = np.linspace(min(pozitii), max(pozitii), 1000)
pdf = pdf_normala(x, n * medie, n * varianta)
plt.plot(x, pdf, label="pdf")

plt.legend()
plt.title("ex 5 c")
plt.show()
