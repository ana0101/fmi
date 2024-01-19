from pydataset import data
from scipy.stats import linregress
import numpy as np
import matplotlib.pyplot as plt

D = data

def calc_var(X, medie_X):
    X2 = [x ** 2 for x in X]
    var_X = sum(X2) / len(X2) - medie_X ** 2
    return var_X

# ex 1
# a
d = data('iris')
dnp = d.to_numpy()

# sepal length
X = dnp[:,0].astype('float')
# petal length
Y = dnp[:,2].astype('float')

plt.scatter(X, Y)
x = np.linspace(0, max(max(X), max(Y)))
plt.xlabel("sepal length")
plt.ylabel("petal length")
plt.title("ex 1 a")

# a - d
medie_X = np.average(X)
medie_Y = np.average(Y)
medie_XY = np.average(X * Y)
cov = medie_XY - medie_X * medie_Y
print("cov a =", cov)

var_X = calc_var(X, medie_X)
var_Y = calc_var(Y, medie_Y)
cor = cov / (np.sqrt(var_X) * np.sqrt(var_Y))
print("cor a =", cor)

# a - e
alfa = cov / var_X
print("alfa a =", alfa)

beta = medie_Y - alfa * medie_X
print("beta a =", beta)

# a - f
x = np.linspace(min(X), max(X), 10000)
plt.plot(x, alfa * x + beta, label='dreapta de regresie')
plt.show()

# cov(X, Y) = E(X*Y) - E(X) * E(Y)
# alfa = cov(X, Y) / var (X) = coef regresie liniara
# X indep de Y => cov(X, Y) = 0 (reciproca e falsa)
# corelatia(X, Y) = cov(X, Y) / (sqrt(var(X)) * sqrt(var(Y)))


# ex 2
# data('LakeHuron', show_doc=True)
d = data('LakeHuron')
dnp = d.to_numpy()

def calc_var(X, medie_X):
    X2 = [x ** 2 for x in X]
    var_X = sum(X2) / len(X2) - medie_X ** 2
    return var_X

def cov_cor_alfa_beta(X, Y):
    medie_X = np.average(X)
    medie_Y = np.average(Y)
    medie_XY = np.average(X * Y)
    cov = medie_XY - medie_X * medie_Y

    var_X = calc_var(X, medie_X)
    var_Y = calc_var(Y, medie_Y)
    cor = cov / (np.sqrt(var_X) * np.sqrt(var_Y))

    alfa = cov / var_X
    beta = medie_Y - alfa * medie_X

    return cov, cor, alfa, beta

# a
# year
X = dnp[:,0].astype('float')
# water level (feet)
Y = dnp[:,1].astype('float')

plt.scatter(X, Y)
x = np.linspace(0, max(max(X), max(Y)))
plt.xlabel("year")
plt.ylabel("water level")
plt.title("ex 2 a")
plt.show()

# b
cov, cor, alfa, beta = cov_cor_alfa_beta(X, Y)
print("covarianta =", cov)
print("corelatie =", cor)

# c
print("alfa =", alfa)
print("beta =", beta)

# d
plt.scatter(X, Y)
x = np.linspace(0, max(max(X), max(Y)))
plt.xlabel("year")
plt.ylabel("water level")
x = np.linspace(min(X), max(X), 10000)
plt.plot(x, alfa * x + beta, label='dreapta de regresie')
plt.title("ex 2 d")
plt.show()

# e
indici_sample = np.random.choice(len(X), size=round(len(X) * 0.8), replace=False)
X_sample = X[indici_sample]
Y_sample = Y[indici_sample]

cov, cor, alfa, beta = cov_cor_alfa_beta(X_sample, Y_sample)
print("alfa sample =", alfa)
print("beta sample =", beta)

indici_test = [i for i in range(0, len(X)) if i not in indici_sample]
X_test = X[indici_test]
Y_test = Y[indici_test]

predictie = [alfa * x + beta for x in X_test]

for pred_y, y in zip(predictie, Y_test):
    print("predictie =", pred_y, ", valoare =", y)

plt.scatter(X_test, Y_test)
plt.scatter(X_test, predictie)
plt.xlabel("year")
plt.ylabel("water level")
plt.title("ex 2 e")
plt.show()
