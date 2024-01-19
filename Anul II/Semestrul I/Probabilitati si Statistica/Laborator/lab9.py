import numpy as np
import matplotlib.pyplot as plt

# ex 1
print("ex 1:")
# i
f = lambda x: np.exp(-x**2)
a = 0
b = 1

# ii
# f = lambda x: np.sin(x) / x
# a = 0
# b = np.pi

# iii
# f = lambda x: np.sin(x**2)
# f = lambda x: np.cos(x**2)
# a = 0
# b = 2 * np.pi

# iv
# f = lambda x: np.exp(np.exp(x))
# a = 0
# b = 1.5

# v
# f = lambda x: 10 * np.exp(-10 * x) * (x**2) * np.sin(x)
# a = 0
# b = 100

# a
x = np.linspace(a, b, 1000)
plt.plot(x, f(x))
plt.title("ex 1 a")
plt.show()

# b
n = 1000
x = np.random.uniform(a, b, size=n)
int_b = np.mean((f(x) * (b-a)))
print("int_b =", int_b)

# c
aprox_int = [f(y) * (b-a) for y in x]
aprox_int = np.cumsum(aprox_int)
for i in range(len(aprox_int)):
    aprox_int[i] /= (i + 1)
plt.plot(aprox_int)
plt.title("ex 1 c")
plt.show()

# d
N = 10000
x = np.random.uniform(a, b, size=(N, n))

# e
aprox_int = list()
for i in range(N):
    int_e = np.mean((f(x[i]) * (b-a)))
    aprox_int.append(int_e)
plt.hist(aprox_int)
plt.title("ex 1 e")
plt.show()


# ex 2
print("ex 2:")
# c
f = lambda x: 10 * np.exp(-10 * x) * (x**2) * np.sin(x)
g = lambda x: (x**2) * np.sin(x)
a = 0
b = 100

# a
n = 10000
x = np.random.exponential(scale=1/10, size=n)
int_a = np.mean(g(x))
print("int_a =", int_a)

# b
aprox_int = np.cumsum(g(x))
for i in range(len(aprox_int)):
    aprox_int[i] /= (i + 1)
plt.plot(aprox_int)
plt.title("ex 2 b")
plt.show()
