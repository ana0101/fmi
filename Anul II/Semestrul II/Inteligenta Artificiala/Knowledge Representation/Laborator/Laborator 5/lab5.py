import copy

class NodArbore:
    def __init__(self, informatie, g=0, h=0, parinte=None):
        self.informatie = informatie
        self.g = g
        self.h = h
        self.f = g + h
        self.parinte = parinte

    def __str__(self):
        return f"({self.informatie}, g:{self.g}, f:{self.f})"

    def __repr__(self):
        return "{}, ({})".format(str(self.informatie), " -> ".join([str(x) for x in self.drum_radacina()]))

    def __eq__(self, other):
        return self.f == other.f and self.g == other.g

    def __lt__(self, other):
        return self.f < other.f or (self.f == other.f and self.g > other.g)

    def drum_radacina(self):
        nod = self
        l_drum = []
        while nod:
            l_drum.append(nod)
            nod = nod.parinte

        return l_drum[::-1]

    def in_drum(self, infonod):
        nod = self
        while nod:
            if nod.informatie == infonod:
                return True
            nod = nod.parinte
        return False


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def valideaza(self):
        matrice_desfasurata = self.start[0] + self.start[1] + self.start[2]
        nr_inversiuni = 0
        for i, placuta in enumerate(matrice_desfasurata):
            for placuta2 in matrice_desfasurata[i+1:]:
                if placuta > placuta2 and placuta2:
                    nr_inversiuni += 1
        return nr_inversiuni % 2 == 0

    def scop(self, informatie_nod):
        return informatie_nod in self.scopuri

    def estimeaza_h(self, info_nod, euristica):
        if self.scop(info_nod):
            return 0

        if euristica == "banala":
            return 1

        if euristica == "euristica mutari":
            min_h = float("inf")
            for scop in self.scopuri:
                h = 0
                for i_linie, linie in enumerate(scop):
                    for i_placuta, placuta in enumerate(linie):
                        if info_nod[i_linie][i_placuta] != placuta:
                            h += 1
                if h < min_h:
                    min_h = h
            return min_h

        if euristica == "euristica costuri":
            min_h = float("inf")
            for scop in self.scopuri:
                h = 0
                for i_linie, linie in enumerate(scop):
                    for i_placuta, placuta in enumerate(linie):
                        if info_nod[i_linie][i_placuta] != placuta:
                            h += placuta
                if h < min_h:
                    min_h = h
            return min_h

        if euristica == "euristica manhattan":
            min_h = float("inf")
            for scop in self.scopuri:
                h = 0
                for i_linie, linie in enumerate(scop):
                    for i_placuta, placuta in enumerate(linie):
                        if info_nod[i_linie][i_placuta] != placuta and info_nod[i_linie][i_placuta] != 0:
                            poz_finala = info_nod[i_linie][i_placuta] - 1
                            l_finala = int(poz_finala / 3)
                            c_finala = poz_finala % 3
                            h += (abs(l_finala - i_linie) + abs(c_finala - i_placuta))

                if h < min_h:
                    min_h = h
            print(min_h)
            return min_h

            # 1 0 3   1 2 3
            # 4 2 5   4 0 5
            # 7 8 6   7 8 6

        if euristica == "euristica neadmisibila":
            return self.estimeaza_h(info_nod, "euristica mutari") * 10

    def succesori(self, nod, euristica):
        def gaseste_gol(matrice):
            for l in range(3):
                for c in range(3):
                    if matrice[l][c] == 0:
                        return l, c

        l_succesori = []
        l_gol, c_gol = gaseste_gol(nod.informatie)

        directii = [[0, 1], [1, 0], [0, -1], [-1, 0]]

        for d in directii:
            l_placuta = l_gol + d[0]
            c_placuta = c_gol + d[1]

            if not (0 <= l_placuta <= 2 and 0 <= c_placuta <= 2):
                continue

            info_succesor = copy.deepcopy(nod.informatie)
            info_succesor[l_gol][c_gol], info_succesor[l_placuta][c_placuta] = info_succesor[l_placuta][c_placuta], info_succesor[l_gol][c_gol]

            if not nod.in_drum(info_succesor):
                l_succesori.append(NodArbore(info_succesor, nod.g + 1, self.estimeaza_h(info_succesor, euristica), nod))

        return l_succesori


def a_star(graf, euristica):
    if not graf.valideaza():
        print("Nu are solutii")
        return

    open = [NodArbore(graf.start)]
    closed = []
    while open:
        nod_curent = open.pop(0)
        closed.append(nod_curent)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            return

        l_succesori = graf.succesori(nod_curent, euristica)
        for succesor in l_succesori:
            gasit_open = False
            for nod_coada in open:
                if succesor.informatie == nod_coada.informatie:
                    gasit_open = True
                    if succesor < nod_coada:
                        open.remove(nod_coada)
                    else:
                        l_succesori.remove(succesor)

            if not gasit_open:
                for nod_coada in closed:
                    if succesor.informatie == nod_coada.informatie:
                        gasit_open = True
                        if succesor < nod_curent:
                            closed.remove(nod_curent)
                        else:
                            l_succesori.remove(succesor)

        open += l_succesori
        open.sort()


f = open("input5.txt", "r")
continut = f.read()
start = [list(map(int, linie.strip().split())) for linie in continut.strip().split("\n")]
scopuri = [
    [[1, 2, 3],
     [4, 5, 6],
     [7, 8, 0]]
]

graf = Graf(start, scopuri)
# a_star(graf, "banala")
# a_star(graf, "euristica mutari")
# a_star(graf, "euristica costuri")
a_star(graf, "euristica manhattan")
# a_star(graf, "euristica neadmisibila")

# tema: 3
