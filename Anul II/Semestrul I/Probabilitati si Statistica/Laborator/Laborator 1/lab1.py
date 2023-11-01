import numpy as np
import matplotlib.pyplot as plt

# # Ex 1 a
# # Sa se genereze aleator o coarda pe cercul de raza R prin generarea aleatoare uniforma
# # a capetelor coardei P1, P2 pe cercul de raza R
# N = 1000
# plt.figure()
# plt.xlim([-1, 1])
# plt.ylim([-1, 1])
# plt.axis('equal')
# plt.title('Method a: Random line on circle')
# n = 0

# for i in range(N):
#     theta = 2 * np.pi * np.random.rand()
#     a = np.array([np.cos(theta), np.sin(theta)])
#     theta = 2 * np.pi * np.random.rand()
#     b = np.array([np.cos(theta), np.sin(theta)])

#     l = np.sqrt((b[0]-a[0]) ** 2 + (b[1]-a[1]) ** 2)

#     if l >= np.sqrt(3):
#         n += 1

#     x_values = [a[0], b[0]]
#     y_values = [a[1], b[1]]
#     plt.plot(x_values, y_values, 'bo', linestyle="-", linewidth=0.5)
#     plt.plot(a[0], a[1], marker="o", markersize=3, markeredgecolor="pink", markerfacecolor="pink")
#     plt.plot(b[0], b[1], marker="o", markersize=3, markeredgecolor="pink", markerfacecolor="pink")

# P = n / N
# print('Method a: P = ', P)
# plt.show()


# # Ex 1 b
# # Sa se genereze aleator o coarda pe cercul de raza R prin generarea aleatoare a
# # mijlocului coardei M
# N = 1000
# plt.figure()
# plt.xlim([-1, 1])
# plt.ylim([-1, 1])
# plt.axis('equal')
# plt.title('Method b: Random midpoint on a radius')
# n = 0

# for i in range(N):
#     theta = 2 * np.pi * np.random.rand()
#     r = np.random.rand()
#     m = np.array([r * np.cos(theta), r * np.sin(theta)])

#     lm = np.sqrt(m[1] ** 2 + m[0] ** 2)
#     if lm < 1/2:
#         n += 1

#     a = -m[0] / m[1]
#     b = m[1] - a * m[0]
#     delta = 4 * a ** 2 * b ** 2 - 4 * (1 + a ** 2) * (b ** 2 - 1)
#     x = np.array([(-2 * a * b + np.sqrt(delta)) / (2 * (1 + a ** 2)), (-2 * a * b - np.sqrt(delta)) / (2 * (1 + a ** 2))])
#     y = a * x + b

#     plt.plot(x, y, 'C0', linewidth=0.5)
#     plt.plot(x, y, '.')
#     plt.plot(m[0], m[1], 'C1.')

# P = n / N
# print('Method b: P = ', P)
# plt.show()


# Ex 1 c
# Sa se genereze aleator o coarda pe cercul de raza R prin generarea aleatoare uniforma
# in discul de raza R a mijlocului coardei M
N = 1000
plt.figure()
plt.xlim([-1, 1])
plt.ylim([-1, 1])
plt.axis('equal')
plt.title('Method c: Uniform midpoint in disk')
n = 0

for i in range(N):
    # theta = 2 * np.pi * np.random.rand()
    # r = np.sqrt(np.random.rand())
    # m = np.array([r * np.cos(theta), r * np.sin(theta)])

    ok = False
    m = [0, 0]
    while ok == False:
        m[0] = 2 * np.random.rand() - 1
        m[1] = 2 * np.random.rand() - 1
        if np.sqrt(m[0] ** 2 + m[1] ** 2) <= 1:
            ok = True

    lm = np.sqrt(m[1] ** 2 + m[0] ** 2)
    if lm < 1/2:
        n += 1

    a = -m[0] / m[1]
    b = m[1] - a * m[0]
    delta = 4 * a ** 2 * b ** 2 - 4 * (1 + a ** 2) * (b ** 2 - 1)
    x = np.array([(-2 * a * b + np.sqrt(delta)) / (2 * (1 + a ** 2)), (-2 * a * b - np.sqrt(delta)) / (2 * (1 + a ** 2))])
    y = a * x + b

    plt.plot(x, y, 'C0', linewidth=0.5)
    plt.plot(x, y, '.')
    plt.plot(m[0], m[1], 'C1.')

P = n / N
print('Method c: P = ', P)
plt.show()


# Tema: construiti o functie care sa genereze puncte distribuite uniform intr-o elipsa de raza (a, b)