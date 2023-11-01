# EX#7(T) Creati un fisier in Python prin care sa se estimeze numeric π folosind experimentul lui Buffon

# l = lungime ac
# t = latime fasie
# l <= t
# p = 2/pi * l/t
# pi = 2l/tp

import numpy as np
import matplotlib.pyplot as plt

l = 0.8
t = 1
dim = 5
N = 1000000

plt.figure()

# ploteaza acele si podeaua
# plt.title('Needles')
# plt.xlim([0, dim])
# plt.ylim([0, dim])
# plt.gca().xaxis.grid()

# ploteaza pi
# plt.title('Pi')
# plt.xlim([0, N])
# plt.ylim([0, 5])

# genereaza un ac pe podea
def generate_needle(l, t, dim):
    # genereaza primul capat al acului intre 1 si dim-1 (pt ambele axe)
    x1 = np.random.rand() * (dim-2) + 1
    y1 = np.random.rand() * (dim-2) + 1

    # genereaza un unghi intre 0 si 2pi
    theta = np.random.rand() * 2 * np.pi

    # calculeaza al doilea capat al acului in functie de primul si unghiul theta
    x2 = x1 + l * np.cos(theta)
    y2 = y1 + l * np.sin(theta)

    # ploteaza acul
    # x_values = [x1, x2]
    # y_values = [y1, y2]
    # plt.plot(x_values, y_values, 'bo', linestyle="-", markersize=2)

    return [x1, y1], [x2, y2]

# simuleaza aruncarea a N ace si returneaza probabilitatea sa intersecteze o linie
def simulation(l, t, dim, N):
    p = 0
    for i in range(N):
        p1, p2 = generate_needle(l, t, dim)

        # verifica daca intersecteaza
        for j in range(1, dim):
            if p1[0] <= j and p2[0] >= j:
                p += 1
            elif p1[0] >= j and p2[0] <= j:
                p += 1

        # ploteaza pi
        # if p != 0:
        #     pi = (2*l) / (t*(p/(i+1)))
        # else:
        #     pi = 0
        # plt.plot(i, pi, marker="o", markersize=2)
    p /= N
    return p

p = simulation(l, t, dim, N)

pi = (2*l) / (t*p)
print("pi =", pi)

# plt.show() 