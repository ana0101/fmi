p = int(input("p = "))
numeFisier = input("nume fisier = ")
fin = open(numeFisier, "r")
listaCuv = fin.read().split()
fin.close()
d = {}

for cuv in listaCuv:
    sufix = cuv[-p:]
    if sufix not in d.keys():
        d[sufix] = [cuv]
    else:
        d[sufix].append(cuv)

var = sorted(d.values(), key = lambda lista: -len(lista))

fout = open("rime.txt", "w")
print(var)
for i in d.keys():
    d[i].sort(reverse = True)
for linie in var:
    fout.writelines(" ".join(linie))
    fout.writelines("\n")
