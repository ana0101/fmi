# a
def citire_matrice(nume_fisier):
    fin = open("matrice.in", "r")
    date = fin.read().split("\n")
    fin.close()
    matrice = []
    lung = None

    for linie in date:
        linie = linie.split()
        linie = [int(x) for x in linie]
        if lung == None:
            lung = len(linie)
        else:
            if lung != len(linie):
                return None
        matrice.append(linie)
    return matrice

matrice = citire_matrice("matrice.in")
print(matrice)

# b
def multimi(matrice, *indici):
    inter_neg = set()
    reun_poz = set()

    for i in indici:
        neg = set()
        poz = set()
        for nr in matrice[i]:
            if nr < 0 and nr not in neg:
                neg.add(nr)
            if nr > 0 and str(nr)[0] == str(nr)[len(str(nr))-1]:
                poz.add(nr)

        if inter_neg == set():
            inter_neg = neg
        else:
            inter_neg = inter_neg.intersection(neg)

        reun_poz = reun_poz.union(poz)

    return inter_neg, reun_poz

inter_neg, reun_poz = multimi(matrice, 0, 1, 3)
print(inter_neg)
print(reun_poz)

# c
mat = citire_matrice("matrice.in")

neg, poz = multimi(mat, len(mat)-1, len(mat)-2, len(mat)-3)
poz = list(poz)
poz.sort(key = lambda x: x)
print(*poz)

neg, poz = multimi(mat, 0, len(mat)-1)
nr = len(neg)
print(nr)
