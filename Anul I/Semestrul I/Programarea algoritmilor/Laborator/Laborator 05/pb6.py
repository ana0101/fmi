fin = open("pb6_evenimente.txt", "r")
date = fin.read().split("\n")
fin.close()

lista = []
for linie in date:
    tuplu = ()
    lista1 = linie.split(" ")
    ore = lista1[0].split("-")
    nume = ""
    for i in range(1, len(lista1)):
        nume += lista1[i] + " "
    nume = nume.strip()
    tuplu = (ore[0], ore[1], nume)
    lista.append(tuplu)

lista.sort(key = lambda t: t[0])

sali = {}
k = 1
for tuplu in lista:
    for numeSala in sali.keys():
        if tuplu[0] >= sali[numeSala][len(sali[numeSala])-1][1]:
            sali[numeSala].append(tuplu)
            break
    else:
        numeSala = "Sala " + str(k)
        sali[numeSala] = [tuplu]
        k += 1

fout = open("pb6_sali.txt", "w")
fout.writelines("Numar minim de sali: " + str(k-1) + "\n\n")

for numeSala in sali.keys():
    fout.writelines(numeSala + ":\n")
    lista = []
    for tuplu in sali[numeSala]:
        elem = "(" + tuplu[0] + "-" + tuplu[1] + " " + tuplu[2] + ")"
        lista.append(elem)
    linie = ",".join(lista)
    fout.writelines(linie + "\n\n")

fout.close()
