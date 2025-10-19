import numpy as np
from scipy.stats import binom
from scipy.stats import norm
from scipy.stats import chi2
from scipy.optimize import minimize
import matplotlib.pyplot as plt

# examen 2020 --------------------------------------------------------------------------------------------------------
# ex 2
n = 100
k = 4
p = 1/6
p = binom.pmf(k, n, p)
print(p)

# ex 3
m = 0
sigma = 1
p = norm.cdf(-1, loc=m, scale=sigma)
print(p)

# ex 4
# ppf = percent point function = quantile function (qnorm din R)
z = norm.ppf(1 - 0.01 / 2)
print(z)

# ex 5
# np.var calc dispersia (variance)
# ddof = delta degrees of freedom
X = np.array([1, 2, 3, 7])
s = np.var(X, ddof=1)
print(s)

df = 3  # degrees of freedom
alpha = 0.05
chi2_lower = chi2.ppf(alpha/2, df)
chi2_upper = chi2.ppf(1 - alpha/2, df)
print(chi2_lower)
print(chi2_upper)

# ex 6
X = np.array([1, 2, 3, 4])
Y = np.array([1, 2, 3, 4])
s = lambda X, Y, B: np.sum((Y - B[0] - B[1] * X - B[2] * X**2) ** 2)
min_beta = minimize(lambda B: s(X, Y, B), [0, 0, 0])    # [0, 0, 0] = punct de plecare
B = min_beta.x
print(B)

plt.plot(X, B[0] + B[1] * X + B[2] * X ** 2)
plt.show()


# examen 2019 --------------------------------------------------------------------------------------------------------
# ex 2
p = norm.cdf(0.77) # pnorm(0.77)
print(p)

# ex 3
p = norm.ppf(0.4)
print(p)

# ex 5
alpha = 0.1
df = 4
chi2_lower = chi2.ppf(alpha / 2, df)
chi2_upper = chi2.ppf(1 - alpha/2, df)
print(chi2_lower)
print(chi2_upper)

# ex 6
G = 2.197
X2 = 40.111
df = 45
p_value_G = 1 - chi2.cdf(G, df)
p_value_X2 = 1 - chi2.cdf(X2, df)
print(p_value_G)
print(p_value_X2)


# examen model --------------------------------------------------------------------------------------------------------
# ex 5
X = np.array([1, 2, 3, 58])
mean = np.mean(X)
var = np.var(X, ddof=1)
print(mean)
print(var)
