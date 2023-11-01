# Tema: construiti o functie care sa genereze puncte distribuite uniform intr-o elipsa de raza (a, b)

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse

plt.figure()
plt.xlim([-3, 3])
plt.ylim([-3, 3])

n = 1000
a = 1
b = 2

e = Ellipse(xy=(0, 0), width=a*2, height=b*2, angle=0)
plt.gca().add_patch(e)

# varianta 1 - generam uniform un punct in elipsa
def punct(a, b):
    theta = 2 * np.pi * np.random.rand()
    r = np.sqrt(np.random.rand())
    x = np.cos(theta) * r * a
    y = np.sin(theta) * r * b
    return x, y

# varianta 2 - generam un punct in dreptunghiul care contine elipsa si verificam daca se
# afla in elipsa; daca nu se afla, generam din nou pana se afla
def punct2(a, b):
    ok = False
    x = y = 0
    while ok == False:
        x = 2 * a * np.random.rand() - a   
        y = 2 * b * np.random.rand() - b    
        if x**2 / a**2 + y**2 / b**2 <= 1:
            ok = True
    return x, y

def generare(a, b, n):
    for i in range(n):
        x, y = punct(a, b)
        plt.plot(x, y, marker="o", markersize=3, markeredgecolor="pink", markerfacecolor="pink")

generare(a, b, n)
plt.show()