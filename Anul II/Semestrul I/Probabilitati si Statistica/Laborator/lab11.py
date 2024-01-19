import numpy as np
import matplotlib.pyplot as plt
from scipy.special import factorial as factorial_array

# ex 1
sample_Bernoulli = "sample_Bernoulli.npy"
sample_Poisson = "sample_Poisson.npy"
sample_Geom = "sample_Geom.npy"
sample_Exp = "sample_Exp.npy"

X_Bernoulli = np.load(sample_Bernoulli)
X_Poisson = np.load(sample_Poisson)
X_Geom = np.load(sample_Geom)
X_Exp = np.load(sample_Exp)

# bernoulli
# log L = log(teta) * sum(xi) + log(1-teta) * sum(1-xi)
# teta = sum(xi) / n

# poisson
# log L = -n * teta + log(teta) * sum(xi) - sum(log(xi!))
# teta = sum(xi) / n

# geom
# log L = n * log(teta) + log(1 - teta) * sum(xi - 1)
# teta = n / (sum(xi))

# exp
# log L = n * log(teta) - teta * sum(xi)
# teta = n / (sum(xi))

# 2) afisati graficul functiei log L(x1, x2,..,xn, teta pe (0, 50))
L_Bernoulli = lambda X, n, t: np.log(t) * np.sum(X) + np.log(1 - t) * sum(1 - X)
L_Poisson = lambda X, n, t: -n * t + np.log(t) * np.sum(X) - np.sum(np.log(factorial_array(X)))
L_Geom = lambda X, n, t: n * np.log(t) + np.log(1 - t) * np.sum(X - 1)
L_Exp = lambda X, n, t: n * np.log(t) - t * sum(X)

t_Bernoulli = np.linspace(0.05, 0.95)
t_Poisson = np.linspace(0.1, 50)
t_Geom = np.linspace(0.05, 0.95)
t_Exp = np.linspace(0.1, 50)

calc_teta_caciula_B_P = lambda X, n: sum(X) / n
calc_teta_caciula_G_E = lambda X, n: n / (sum(X))

def ex1(X, L, t, calc_teta):
    # 1) afisati histograma datelor
    plt.hist(X, bins=50)
    plt.title("data")
    plt.show()

    n = len(X)
    values = L(X, n, t)
    plt.plot(t, values) 
    plt.title("log L")
    plt.show()

    # 3) determinati teta cu caciula
    teta = calc_teta(X, n)
    print("teta cu caciula =", teta)

    # 4) afisati pe graficul anterior pct de maxim (teta cu caciula)
    max_teta = L(X, n, teta)
    plt.plot(t, values) 
    plt.scatter(teta, max_teta)
    plt.title("log L with max")
    plt.show()

ex1(X_Bernoulli, L_Bernoulli, t_Bernoulli, calc_teta_caciula_B_P)
ex1(X_Poisson, L_Poisson, t_Poisson, calc_teta_caciula_B_P)
ex1(X_Geom, L_Geom, t_Geom, calc_teta_caciula_G_E)
ex1(X_Exp, L_Exp, t_Exp, calc_teta_caciula_G_E)


# ex 2
sample_Normal = "sample_Normal.npy"
X_Normal = np.load(sample_Normal)

# a
plt.hist(X_Normal, bins=50)
plt.title("hist Normal")
plt.show()

# b
# log_L_Normal = -(n/2) * ln(2*pi) - (n/2) * ln(t2) - (1/(2*t2) * sum((xi - t1)**2)
# t1 = media
# t2 = dispersia

log_L_Normal = lambda X, n, t1, t2: -(n / 2) * np.log(2 * np.pi) - (n / 2) * np.log(t2) - (1 / (2 * t2)) * np.sum((X - t1) ** 2)
T1 = np.linspace(-1, 1, 100)
T2 = np.linspace(0, 0.1, 100)

n = len(X_Normal)
values = np.array([[log_L_Normal(X_Normal, n, t1, t2) for t1 in T1] for t2 in T2])

ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
T1, T2 = np.meshgrid(T1, T2)
ax.plot_surface(T1, T2, values)
ax.set_title("log L Normal")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()

# c
mle_t1 = (1 / n) * np.sum(X_Normal)
mle_t2 = (1 / n) * np.sum((X_Normal - mle_t1) ** 2)
print("mle theta Normal = (", mle_t1, ", ", mle_t2, ")")

# d
ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
ax.plot_surface(T1, T2, values)
ax.scatter(mle_t1, mle_t2, log_L_Normal(X_Normal, n, mle_t1, mle_t2), c="darkred", marker='o', s=100)
ax.set_title("log L Normal with mle")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()
