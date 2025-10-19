# 1
class NodArbore:
    def __init__(self, informatie, parinte=None):
        self.informatie = informatie
        self.parinte = parinte

    # c
    def __str__(self):
        return str(self.informatie)

    # d
    def __repr__(self):
        return "{}, ({})".format(str(self.informatie), "->".join([str(x) for x in self.drum_radacina()]))

    # a
    def drum_radacina(self):
        nod = self
        l_drum = []
        while nod:
            l_drum.append(nod)
            nod = nod.parinte

        return l_drum[::-1]

    # b
    def in_drum(self, infonod):
        nod = self
        while nod:
            if nod.informatie == infonod:
                return True
            nod = nod.parinte
        return False


# 2
class Graf:
    # a
    def __init__(self, matrice, start, scopuri):
        self.matrice = matrice
        self.start = start
        self.scopuri = scopuri

    # b
    def scop(self, informatie_nod):
        return informatie_nod in self.scopuri

    # c
    def succesori(self, nod):
        l_succesori = []
        for info_succesor in range(len(self.matrice)):
            if self.matrice[nod.informatie][info_succesor] == 1 and not nod.in_drum(info_succesor):
                l_succesori.append(NodArbore(info_succesor, nod))

        return l_succesori


# 3
def breadth_first(graf, nsol=1):
    coada = [NodArbore(graf.start)]
    while coada:
        nod_curent = coada.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1
            if nsol == 0:
                return

        l_succesori = graf.succesori(nod_curent)
        coada += l_succesori


# 6
def breadth_first2(graf, nsol=1):
    start = NodArbore(graf.start)
    if graf.scop(start):
        print(repr(start))
        nsol -= 1
        if nsol == 0:
            return
    coada = [start]
    while coada:
        nod_curent = coada.pop(0)
        for succesor in graf.succesori(nod_curent):
            if graf.scop(succesor.informatie):
                print(repr(succesor))
                nsol -= 1
                if nsol == 0:
                    return
            coada.append(succesor)


# 4
nsol = 3
def recursive_depth_first(graf, nod_curent):
    global nsol
    if nsol == 0:
        return
    if graf.scop(nod_curent.informatie):
        print(repr(nod_curent))
        nsol -= 1

    for succesor in graf.succesori(nod_curent):
        recursive_depth_first(graf, succesor)


# d
def iterative_depth_first(graf, nsol=3):
    stiva = [NodArbore(graf.start)]
    while stiva:
        nod_curent = stiva.pop()
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1
            if nsol == 0:
                return
        for succesor in graf.succesori(nod_curent):
            stiva.append(succesor)


m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
]

start = 0
scopuri = [5, 9]

graf = Graf(m, start, scopuri)
breadth_first(graf, nsol=3)
print()
breadth_first2(graf, nsol=3)
print()
recursive_depth_first(graf, nod_curent=NodArbore(graf.start))
print()
iterative_depth_first(graf, nsol=3)
