import numpy as np
import matplotlib.pyplot as plt

plt.figure()

# Ex 1
# a
def aruncare_corecta():
    x = np.random.rand()
    if x < 0.5:
        return 'H'
    else:
        return 'T'
    
# b
def aruncare_masluita(ph):
    x = np.random.rand()
    if x < ph:
        return 'H'
    else:
        return 'T'
    
# c
N = 100
nh = 0
v_prob_corect = list()
v_prob_corect.append(0)
for i in range(1, N+1):
    if aruncare_corecta() == 'H':
        nh += 1
    v_prob_corect.append(nh / i)
ph = nh / N
print("Prob head corect: ", ph)

nh = 0
v_prob_masluit = list()
v_prob_masluit.append(0)
for i in range(1, N+1):
    if aruncare_masluita(0.7) == 'H':
        nh += 1
    v_prob_masluit.append(nh / i)
ph = nh / N
print("Prob head masluit: ", ph)

# d
plt.xlim([0,N+1])
plt.ylim([0,1])
for i in range(1, N+1):
    plt.plot(i, v_prob_corect[i], marker="o", markersize=2, markeredgecolor="pink", markerfacecolor="pink")
plt.show()

plt.xlim([0,N+1])
plt.ylim([0,1])
for i in range(1, N+1):
    plt.plot(i, v_prob_masluit[i], marker="o", markersize=2, markeredgecolor="pink", markerfacecolor="pink")
plt.show()


# Ex 2
# a
def zar_corect():
    x = np.random.rand() * 6
    return int(x+1)

# b
def zar_masluit(p):
    x = np.random.rand()
    if x < p[1]:
        return 1
    elif x < p[2]:
        return 2
    elif x < p[3]:
        return 3
    elif x < p[4]:
        return 4
    elif x < p[5]:
        return 5
    elif x < p[6]:
        return 6

# c
N = 1000
prob = [0] * 7
for i in range(1, N+1):
    rez = zar_corect()
    prob[rez] += 1

for i in range(1, 7):
    prob[i] /= N

print("Prob zar corect:")
for i in range(1, 7):
    print("Prob ", i, " :", prob[i])

p = [0, 0.25, 0.25, 0.2, 0.15, 0.1, 0.05]
for i in range(7):
        p[i] += p[i-1]
prob = [0] * 7
for i in range(1, N+1):
    rez = zar_masluit(p)
    prob[rez] += 1

for i in range(1, 7):
    prob[i] /= N

print("Prob zar masluit:")
for i in range(1, 7):
    print("Prob ", i, " :", prob[i])


# Ex 3
def secventa(nr, k):
    N = 10000
    p = 0
    rez = [0] * (nr)
    for i in range(N):
        for j in range(nr):
            rez[j] = aruncare_corecta()
        # print(rez)

        lh = 0
        lt = 0
        ok = False

        if rez[0] == 'H':
            lh += 1
        else:
            lt += 1

        for j in range(1, nr):
            if rez[j] == rez[j-1]:
                if rez[j] == 'H':
                    lh += 1
                    if lh >= k:
                        ok = True
                else:
                    lt += 1
                    if lt >= k:
                        ok = True
            else:
                if rez[j] == 'H':
                    lh = 1
                    lt = 0
                else:
                    lt = 1
                    lh = 0

        if ok:
            p += 1

    p /= N
    return p
    
print(secventa(10, 4))
print(secventa(20, 4))


# Ex 4
zar1 = [1, 4]
p1 = [1/6, 5/6]

zar2 = [3, 6]
p2 = [5/6, 1/6]

zar3 = [2, 5]
p3 = [1/2, 1/2]

def aruncare_zar(zar, p):
    x = np.random.rand()
    if x < p[0]:
        return zar[0]
    else:
        return zar[1]

# probabilitatea ca zar1 sa bata zar2    
def prob_castig(zar1, p1, zar2, p2):
    N = 10000
    fav = 0
    for i in range(N):
        rez1 = aruncare_zar(zar1, p1)
        rez2 = aruncare_zar(zar2, p2)
        if rez1 > rez2:
            fav += 1
    return fav / N
