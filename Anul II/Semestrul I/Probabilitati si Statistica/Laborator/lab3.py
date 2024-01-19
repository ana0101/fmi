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


# ex 7
# l = lungime ac
# t = latime fasie
# l <= t
# p = 2/pi * l/t
# pi = 2l/tp

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
