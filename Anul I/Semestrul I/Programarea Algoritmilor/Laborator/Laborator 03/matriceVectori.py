# 1
# m = int(input("nr linii = "))
# n = int(input("nr coloane = "))
# a = []
# for i in range(m):
#     linie = [int(elem) for elem in input("elemente linie: ").split()]
#     a.append(linie)
# t = [[a[j][i] for j in range(len(a))] for i in range(len(a[0]))]
# for linie in t:
#     print(*linie)


# 2
# m = int(input("nr linii = "))
# n = int(input("nr coloane = "))
# a = []
# for i in range(m):
#     linie = []
#     for j in range(n):
#         elem = int(input("element: "))
#         linie.append(elem)
#     a.append(linie)
# a.sort(key = lambda linie: (linie[0]))
# for linie in a:
#     print(*linie)


# 3
# n = int(input("n = "))
# triP = []
# triP.append([1])
# c = 0
# for i in range(1, n):
#     linie = [1]
#     for j in range(len(triP[i-1])-1):
#         elem = triP[i-1][j] + triP[i-1][j+1]
#         linie.append(elem)
#         if len(str(elem)) > c:
#             c = len(str(elem))
#     linie.append(1)
#     triP.append(linie)
# for linie in triP:
#     for elem in linie:
#         print(str(elem).center(c+1), end = " ")
#     print()


# 4
# n = int(input("n = "))
# lista = [x for x in range(2, n+1)]
# listaCiur = lista.copy()
# print(listaCiur)
# for x in lista:
#     k = int(n/x)
#     for i in range(2, k+1):
#         nr = x*i
#         if nr in listaCiur:
#             listaCiur.remove(nr)
# print(listaCiur)


# 5
lista1 = input("prima lista ordonata crescator: ").split()
lista2 = input("a doua lista ordonata crescator: ").split()
reuniune = []
intersectie = []
i = 0
j = 0

while i < len(lista1) and j < len(lista2):
    if lista1[i] == lista2[j]:
        intersectie.append(lista1[i])
        reuniune.append(lista1[i])
        i += 1
        j += 1
    else:
        if lista1[i] < lista2[j]:
            reuniune.append(lista1[i])
            i += 1
        else:
            reuniune.append(lista2[j])
            j += 1

while i < len(lista1):
    reuniune.append(lista1[i])
    i += 1
while j < len(lista2):
    reuniune.append(lista2[j])
    j += 1

print("reuniunea: ", reuniune)
print("intersectia: ", intersectie)
