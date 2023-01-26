# a
def permuta_cuvinte(prop, k):
    prop = prop.split()
    nr = 0
    prop_mod = []

    for cuv in prop:
        if len(cuv) >= k+1:
            cuv = list(cuv)
            nr += 1
            cuv_mod = cuv[k:] + cuv[:k]
            cuv_mod = "".join(cuv_mod)
            prop_mod.append(cuv_mod)
        else:
            prop_mod.append(cuv)

    prop_mod = " ".join(prop_mod)
    return prop_mod, nr

prop, nr = permuta_cuvinte("Ana are multe mere rosii", 3)
print(prop)
print(nr)

# b
def sub_medie(lista):
    if lista == []:
        return None
    k = 0
    medie = sum(lista) / len(lista)
    for nr in lista:
        if nr < medie:
            k += 1
    return medie, k

medie, k = sub_medie([1, 2, 3, 4, 5])
print(medie)
print(k)

# c
fin = open("circular.in", "r")
date = fin.read().split("\n")
fin.close()

k = int(input("k = "))
fout = open("circular.out", "w")
lista_mod = []

for prop in date:
    prop_mod, nr = permuta_cuvinte(prop, k)
    fout.writelines(prop_mod)
    lista_mod.append(nr)

fout.close()

medie, nr = sub_medie(lista_mod)
medie = round(medie, 2)
print(medie, nr)
