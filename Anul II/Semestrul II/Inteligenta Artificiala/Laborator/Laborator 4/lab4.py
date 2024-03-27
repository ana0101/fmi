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
                for i_stiva, stiva in enumerate(scop):
                    for i_bloc, bloc in enumerate(stiva):
                        try:
                            if info_nod[i_stiva][i_bloc] != bloc:
                                h += 1
                        except: # daca nu exista indicele i_bloc in lista
                            h += 1
                if h < min_h:
                    min_h = h
            return min_h

        if euristica == "euristica costuri":
            min_h = float("inf")
            for scop in self.scopuri:
                h = 0
                for i_stiva, stiva in enumerate(scop):
                    for i_bloc, bloc in enumerate(stiva):
                        try:
                            if info_nod[i_stiva][i_bloc] != bloc:
                                h += ord(bloc) - ord('a') + 1
                        except:  # daca nu exista indicele i_bloc in lista
                            h += ord(bloc) - ord('a') + 1
                if h < min_h:
                    min_h = h
            return min_h

        if euristica == "euristica neadmisibila":
            return self.estimeaza_h(info_nod, "euristica mutari") * 10

    def succesori(self, nod, euristica):
        l_succesori = []
        for i, stiva in enumerate(nod.informatie):
            if not stiva:
                continue

            copie_stive = copy.deepcopy(nod.informatie)
            bloc = copie_stive[i].pop()

            for j in range(len(copie_stive)):
                if i == j:
                    continue

                info_succesor = copy.deepcopy(copie_stive)
                info_succesor[j].append(bloc)

                if not nod.in_drum(info_succesor):
                    l_succesori.append(NodArbore(info_succesor, nod.g + 1, self.estimeaza_h(info_succesor, euristica), nod))

        return l_succesori


def a_star(graf, euristica):
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


def calc_stive(sir):
    return [stiva.strip().split() if stiva != "#" else [] for stiva in sir.strip().split("\n")]


f = open("input4.txt", "r")
sir_start, sir_scopuri = f.read().split("=========")
start = calc_stive(sir_start)
scopuri = [calc_stive(sir_scop) for sir_scop in sir_scopuri.split("---")]

# print(start)
# print(scopuri)

graf = Graf(start, scopuri)
a_star(graf, "banala")
a_star(graf, "euristica mutari")
a_star(graf, "euristica costuri")
a_star(graf, "euristica neadmisibila")

# tema: 3 (euristica costuri + neadmisibila (returnam ori admisibila * 10, ori direct un nr f mare), 4(opt - doar formatare)
