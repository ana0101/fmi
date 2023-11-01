import numpy as np
import matplotlib.pyplot as plt

plt.figure()

# ex 3
# a
# prob = nr de puncte care pica in domeniu / nr de puncte simulate = aria d / aria totala =>
# aria d = nr de puncte care pica in d / nr de puncte simulate * aria totala
def arie_disc(d, raza_disc, N):
    raza_patrat = raza_disc * 2
    x = np.random.uniform(-raza_patrat/2, raza_patrat/2, size=(d, N))
    # n = nr de cazuri favorabile (nr de puncte in disc)
    n = np.sum(1 * (np.linalg.norm(x, axis=0) <= raza_disc))   
    p = n / N
    volum = p * raza_patrat**d
    print("Volum disc dimensiune ", d, "raza ", raza_disc, " = ", volum)

    # plt.axis('equal')
    # plt.plot(x[0,:], x[1,:], '.')

    ind = np.where(np.linalg.norm(x, axis=0) <= raza_disc)
    # plt.plot(x[0, ind], x[1, ind], 'C1.')
    # plt.show()

    return volum

# arie_disc(2, 0.9, 10000)

def plot_volum_dimensiune(d, raza_disc):
    d_max = max(d)
    v_max = 0

    for dim in d:
        volum = arie_disc(dim, raza_disc, 10000)
        if volum > v_max:
            v_max = volum
        plt.plot(dim, volum, marker="o", markersize=5, markeredgecolor="black", markerfacecolor="black")

    plt.xlim([1, d_max+1])
    plt.ylim([0, v_max+10])

d = list()
for i in range (0, 26):
    d.append(i)
plot_volum_dimensiune(d, 1)
plt.show()


# ex 4
f = lambda x, y, a, b: x**2 / a**2 + y**2 / b**2 
def arie_disc_eliptic(a, b, N):
    x = np.random.uniform(-a, a, size=N)
    y = np.random.uniform(-b, b, size=N)

    n = np.sum(1*(f(x, y, a, b) <= 1))
    p = n / N

    arie = p * (2*a)**2
    
    print("Aria =", arie)

    plt.figure()
    plt.axis('equal')
    plt.plot(x, y, '.')

    ind = np.where(f(x, y, a, b) <= 1)
    plt.plot(x[ind], y[ind], '.')
    plt.show()
    
    print("Arie disc eliptic = ", arie)
    return arie

arie_disc_eliptic(3, 2, 10000)

# ex 6
f1 = lambda x, y: x**2 + y**4 + 2*x*y - 1
f2 = lambda x, y: y**2 + x**2*np.cos(y) - 1
f3 = lambda x, y: np.exp(x**2) + y**2 - 4 + 2.99 * np.cos(y)

def domenii6(f, a, N):
    x = np.random.uniform(-a, a, size=N)
    y = np.random.uniform(-a, a, size=N)

    n = np.sum(1*(f(x, y) <= 0))

    p = n / N
    arie = p * (2*a)**2
    
    print("Aria = ", arie)

    plt.figure()
    plt.axis('equal')
    plt.plot(x, y, '.')

    ind = np.where(f(x, y) <= 0)
    plt.plot(x[ind], y[ind], '.')
    plt.show()

domenii6(f1, 3, 10000)
domenii6(f2, 3, 10000)
domenii6(f3, 3, 10000)