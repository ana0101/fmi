import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize
from scipy.optimize import fsolve
from scipy.special import gamma
from scipy.special import digamma

# ex 1
sample_Gamma = "sample_Gamma.npy"
X_Gamma = np.load(sample_Gamma)

# a
plt.hist(X_Gamma, bins=50)
plt.title("hist Gamma")
plt.show()

# b
# f(x, a, b) = (b**a / gamma(a)) * (e ** (-b*x)) * (x ** (a-1))
# log L (x1, x2, .., xn, (t1, t2)) = sum(t1 * log(t2) - log(gamma(t1)) - t2 * xi + (t1 - 1) * log(xi))
# t1 = mle alpha, t2 = mle beta

# t2 = n * t1 / sum(xi)

# var 1: 
# inlocuiesc t2 in log L => functie care depinde doar de date si de t1
# maximizez in functie de t1 - scipy.optimize.minimize (maximizarea lui log L = minimizarea lui -log L)

log_L_Gamma = lambda X, t1, t2: np.sum(t1 * np.log(t2) - np.log(gamma(t1)) - t2 * X + (t1 - 1) * np.log(X))
log_L_Gamma_t1 = lambda X, n, t1: np.sum(t1 * np.log((n * t1)/np.sum(X)) - np.log(gamma(t1)) - ((n * t1)/np.sum(X)) * X + (t1 - 1) * np.log(X))
log_L_Gamma_t1_minus = lambda X, n, t1: -np.sum(t1 * np.log((n * t1)/np.sum(X)) - np.log(gamma(t1)) - ((n * t1)/np.sum(X)) * X + (t1 - 1) * np.log(X))

n = len(X_Gamma)
maxx = minimize(lambda t1: log_L_Gamma_t1_minus(X_Gamma, n, t1), 1) # 1 = pct de pornire

mle_t1 = maxx.x[0]
mle_t2 = (n * mle_t1) / np.sum(X_Gamma)

print("mle t1 var 1 =", mle_t1)
print("mle t2 var 1=", mle_t2)

# c
# i
T1 = np.linspace(0, 10, 50)
T2 = np.linspace(0, 1, 50)

values = np.array([[log_L_Gamma(X_Gamma, t1, t2) for t1 in T1] for t2 in T2])

ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
T1, T2 = np.meshgrid(T1, T2)
ax.plot_surface(T1, T2, values)
ax.set_title("log L Gamma")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()

# ii
T1 = np.linspace(0, 10, 50)
T2 = np.linspace(0, 5, 50)

values = np.array([[log_L_Gamma(X_Gamma, t1, t2) for t1 in T1] for t2 in T2])

ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
T1, T2 = np.meshgrid(T1, T2)
ax.plot_surface(T1, T2, values)
ax.set_title("log L Gamma")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()

# d
# i
T1 = np.linspace(0, 10, 50)
T2 = np.linspace(0, 1, 50)

values = np.array([[log_L_Gamma(X_Gamma, t1, t2) for t1 in T1] for t2 in T2])

ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
T1, T2 = np.meshgrid(T1, T2)
ax.plot_surface(T1, T2, values)
ax.scatter(mle_t1, mle_t2, log_L_Gamma(X_Gamma, mle_t1, mle_t2), c="darkred", marker='o', s=100)
ax.set_title("log L Gamma with mle")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()

# ii
T1 = np.linspace(0, 10, 50)
T2 = np.linspace(0, 5, 50)

values = np.array([[log_L_Gamma(X_Gamma, t1, t2) for t1 in T1] for t2 in T2])

ax = plt.figure().add_subplot(1, 1, 1, projection='3d')
T1, T2 = np.meshgrid(T1, T2)
ax.plot_surface(T1, T2, values)
ax.scatter(mle_t1, mle_t2, log_L_Gamma(X_Gamma, mle_t1, mle_t2), c="darkred", marker='o', s=100)
ax.set_title("log L Gamma with mle")
ax.set_xlabel("T1")
ax.set_ylabel("T2")
ax.set_zlabel("log L")
plt.show()


# var 2:
# inlocuiesc t2 in derivata in functie de t1 din log L => functie care depinde doar de date si t1
# caut radacini (scipy.optimize.solve)

deriv_log_L_Gamma = lambda X, n, t1, t2: n * np.log(t2) - n * (digamma(t1) / gamma(t1)) + np.sum(np.log(X))
deriv_log_L_Gamma_t1 = lambda X, n, t1: n * np.log((n * t1)/np.sum(X)) - n * (digamma(t1) / gamma(t1)) + np.sum(np.log(X))

n = len(X_Gamma)
roots = fsolve(lambda t1: deriv_log_L_Gamma_t1(X_Gamma, n, t1), 1)

mle_t1 = roots[0]
mle_t2 = (n * mle_t1) / np.sum(X_Gamma)

print("mle t1 var 2 =", mle_t1)
print("mle t2 var 2 =", mle_t2)
