# 1
# lista = [x for x in input("propozitie cu cuvinte separate prin spatiu: ").split()]
# def cheie(x):
#     return -len(x)
# lista.sort(key = cheie)
# for x in lista:
#     if len(x) < 2:
#         lista.remove(x)
# print(lista)


# 2
# lista = [int(x) for x in input("numere naturale: ").split()]
# lista.sort(key = lambda x: (sum(list(map(int, str(x)))), -x))
# print(lista)


# 3
# a
# n = int(input("n = "))
# lista = []
# for i in range(n):
#     linie = input("linie: ").split()
#     aux = []
#     aux.append(linie[0])
#     aux.append(linie[1])
#     aux.append(int(linie[2]))
#     aux.append([int(nota) for nota in linie[3:]])
#     lista.append(aux)
# print(lista)

# b
# for student in lista:
#     ok = True
#     for nota in student[3]:
#         if nota < 5:
#             ok = False
#             student.append(ok)
#     if ok == True:
#         student.append(True)
# print(lista)

# c
# lista.sort(key = lambda x: (x[2], x[0], x[1]))
# print(lista)


# 4
def cheie(x):
    if x%2 == 0:
        return (-(x%2), -x)
    else:
        return (-(x%2), x)

lista = [int(x) for x in input("numere naturale: ").split()]
lista.sort(key = cheie)

print(lista)
