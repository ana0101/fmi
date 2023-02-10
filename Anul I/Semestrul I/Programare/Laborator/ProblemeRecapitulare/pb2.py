# a
def deviruseaza(propM):
    listaCuvM = propM.split()
    listaCuvC = []
    for i in range(len(listaCuvM)-1, -1, -1):
        if len(listaCuvM[i]) > 1:
            cuv = listaCuvM[i][len(listaCuvM[i])-1] + listaCuvM[i][1:len(listaCuvM[i])-1] + listaCuvM[i][0]
        else:
            cuv = listaCuvM[i]
        listaCuvC.append(cuv)
    propC = " ".join(listaCuvC)
    return propC

prop = deviruseaza("aorectc aropozitip este aceasta")
print(prop)


# b
def prime(n, numarMaxim = 0):
    import math
    lista = []
    ok = False
    if numarMaxim != 0:
        ok = True
    if n == 0 or n == 1:
        return lista
    lista.append(2)
    if ok == True:
        numarMaxim -= 1
    if n >= 3:
        if (ok == False) or (ok == True and numarMaxim > 0):
            lista.append(3)
            numarMaxim -= 1

    for nr in range(4, n):
        if (ok == False) or (ok == True and numarMaxim > 0):
            for d in range(2, int(math.sqrt(n))+1):
                if nr % d == 0:
                    break
            else:
                lista.append(nr)
                if ok == True:
                    numarMaxim -= 1
        else:
            break

    return lista

lista = prime(15, 3)
print(lista)


# c
fin = open("intrare.in", "r")
text = fin.read().split("\n")
fin.close()
fout = open("intrare_devirusata.out", "w")

listaPrime = prime(len(text)+1)
for i in range(len(text)):
    j = i+1
    if j in listaPrime:
        prop = deviruseaza(text[i])
    else:
        prop = text[i]
    fout.writelines(prop + "\n")

fout.close()