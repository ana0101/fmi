def citire_date():
    with open("pb3_cuburi.txt", "r") as fin:
        n = int(fin.readline().strip())
        lista_cuburi = []
        for linie in fin:
            latura, culoare = linie.strip().split(maxsplit = 1)  # sau split(" ", 1)
            lista_cuburi.append((int(latura), culoare))
    return lista_cuburi

def greedy(lista_cuburi):
    # lista_cuburi contine (latura, culoare)
    lista_cuburi.sort(key = lambda x: -x[0])
    # lista = []
    # lista.clear()
    # lista[:] = []
    solutie = [lista_cuburi[0]]
    h = lista_cuburi[0][0]
    for cub in lista_cuburi[1:]:
        if cub[1] != solutie[-1][1]:
            solutie.append(cub)
            h += cub[0]
    return solutie, h

def afisare(lista_cuburi, h):
    with open("pb3_turn_cuburi.txt", "w") as fout:
        siruri = ["{} {}\n".format(*cub) for cub in lista_cuburi]
        fout.writelines(siruri)
        sir = f"\ninaltime totala = {h}"
        fout.write(sir)

cuburi = citire_date()
print(cuburi)

rezultat = greedy(cuburi)
print(rezultat)

afisare(*rezultat)
