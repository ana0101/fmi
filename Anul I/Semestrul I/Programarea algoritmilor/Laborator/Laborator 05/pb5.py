def citire_date():
    with open("pb5_activitati.txt", "r") as fin:
        n = int(fin.readline().strip())
        # nr_activitate, durata, termen
        lista_activitati = [(i + 1,) + tuple([int(x) for x in linie.split()]) for i, linie in enumerate(fin)]
        return lista_activitati


def greedy(lista_activitati):
    # lista_activitati contine (nr_activ, durata, termen)
    lista = sorted(lista_activitati, key=lambda x: x[2])
    T = 0
    # in solutie avem (nr_acitv, durata, termen, start, intarziere) (nr, d, t, s, h)
    h = max(0, T + lista[0][1] - lista[0][2])  # s + d - t
    solutie = [lista[0] + (T, h)]
    T += lista[0][1]

    for a in lista[1:]:
        h = max(0, T + a[1] - a[2])  # s + d - t
        solutie.append(a + (T, h))
        T += a[1]

    h_max = max([a[-1] for a in solutie])
    return solutie, h_max


def afisare(lista, h_max):
    with open("pb5_intarzieri.txt", "w") as fout:
        sir = "interval\ttermen\tintarziere\n"
        fout.write(sir)
        # in lista avem (nr_activ, durata, termen, start, intarziere)
        lista_siruri = [f"{f'({a[3]}-->{a[3] + a[1]})' : <10}\t{a[2] : ^6}\t{a[4] : >10}\n" for a in lista]
        fout.writelines(lista_siruri)
        sir = f"intarzierea maxima = {h_max}"
        fout.write(sir)


activitati = citire_date()
print(activitati)

rez = greedy(activitati)
afisare(*rez)

# lista_numere = [(i, nr) for i, nr in enumerate(fin.readline().split())]
# lista_numere = [(i, nr) for i, nr in enumerate(input("numere: ").split())]
