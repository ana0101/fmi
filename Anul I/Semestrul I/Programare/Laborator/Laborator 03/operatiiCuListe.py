# 1
# l1 = [x for x in input("elemente lista 1: ").split()]
# l2 = [x for x in input("elemente lista 2: ").split()]
# l1 = []


# 2
# lista = [int(x) for x in input("lista numere naturale: ").split()]
# if lista.count(0) < 2:
#     print("nu exista doua zerouri")
# else:
#     poz1 = lista.index(0)
#     poz2 = lista.index(0, poz1+1)
#     lista = lista[:poz1] + lista[poz2+1:]
#     print(lista)


# 3
# lista = [int(x) for x in input("lista numere naturale: ").split()]
# cnt = lista.count(0)
# for i in range(cnt):
#     poz = lista.index(0)
#     lista = lista[:poz] + lista[poz+1:]
# print(lista)


# 4
# lista = [int(x) for x in input("lista numere naturale: ").split()]
# k = int(input("k = "))
# n = len(lista)
# if k > n:
#     print("k este mai mare decat lungimea liste")
# else:
#     sumaMin = 0
#     suma = 0
#     for i in range(k):
#         suma += lista[i]
#     poz1 = 0
#     poz1Min = 0
#     poz2 = k
#     poz2Min = k
#     sumaMin = suma
#     for i in range(k, n):
#         suma -= lista[poz1]
#         suma += lista[i]
#         poz1 += 1
#         poz2 += 1
#         if suma < sumaMin:
#             sumaMin = suma
#             poz1Min = poz1
#             poz2Min = poz2
#     lista = lista[:poz1Min] + lista[poz2Min:]
#     print(lista)


# 5
# lista = [int(x) for x in input("lista numere naturale ordonate crescator: ").split()]
# n = len(lista)
# i = 0
# while i < n-1:
#     if lista[i] == lista[i+1]:
#         lista = lista[:i] + lista[i+1:]
#         n -= 1
#     else:
#         i += 1
# print(lista)


# 6
lista = [float(x) for x in input("lista numere reale: ").split()]
poz = 0
for x in lista:
    if x < 0:
        lista.insert(poz+1, 0)
    poz += 1
print(lista)
