import numpy as np
import matplotlib.pyplot as plt

# ex 1
# a
p_boala = 0.02
p_test_boala = 0.98
p_test_nu_boala = 0.05
N = 100000

def moneda_masluita(p):
    x = np.random.rand()
    if x < p:
        return 1
    else:
        return 0
    
def simulare():
    boala = moneda_masluita(p_boala)

    if boala:
        test = moneda_masluita(p_test_boala)
    else:
        test = moneda_masluita(p_test_nu_boala)
    return boala, test

p_test_si_boala = 0
p_test = 0
for i in range(N):
    boala, test = simulare()
    if boala == 1 and test == 1:
        p_test_si_boala += 1
    if test:
        p_test += 1

print(p_test_si_boala / p_test * 100)


# b
def simulare2():
    boala = moneda_masluita(p_boala)

    if boala:
        test1 = moneda_masluita(p_test_boala)
        test2 = moneda_masluita(p_test_boala)
    else:
        test1 = moneda_masluita(p_test_nu_boala)
        test2 = moneda_masluita(p_test_nu_boala)
    return boala, test1, test2

p_teste_si_boala = 0
p_teste = 0
for i in range(N):
    boala, test1, test2 = simulare2()
    if boala == 1 and test1 == 1 and test2 == 1:
        p_teste_si_boala += 1
    if test1 == 1 and test2 == 1:
        p_teste += 1

print(p_teste_si_boala / p_teste * 100)


# c
p_poz_neg_si_boala = 0
p_poz_neg = 0
for i in range(N):
    boala, test1, test2 = simulare2()
    if boala == 1 and ((test1 == 1 and test2 == 0) or (test1 == 0 and test2 == 1)):
        p_poz_neg_si_boala += 1
    if (test1 == 1 and test2 == 0) or (test1 == 0 and test2 == 1):
        p_poz_neg += 1

print(p_poz_neg_si_boala / p_poz_neg * 100)


# histograme
# note = np.array([6, 10, 9, 8, 3, 7, 5, 5, 5, 5, 4, 7, 10, 10, 10])
# plt.hist(note, bins=30)
# plt.show()
