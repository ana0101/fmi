from queue import PriorityQueue
import time

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
    def __init__(self, matrice, start, scopuri, h):
        self.matrice = matrice
        self.start = start
        self.scopuri = scopuri
        self.h = h

    def scop(self, informatie_nod):
        return informatie_nod in self.scopuri

    def estimeaza_h(self, info_nod):
        return self.h[info_nod]

    def succesori(self, nod):
        l_succesori = []
        for info_succesor in range(len(self.matrice)):
            if self.matrice[nod.informatie][info_succesor] > 0 and not nod.in_drum(info_succesor):
                l_succesori.append(NodArbore(info_succesor, nod.g + self.matrice[nod.informatie][info_succesor],self.estimeaza_h(info_succesor), nod))

        return l_succesori


def a_star_sol_multiple(graf, nsol=1):
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
        coada.sort()


# 3
def a_star_sol_multiple_pq(graf, nsol=1):
    coada = PriorityQueue()
    coada.put(NodArbore(graf.start))
    while not coada.empty():
        nod_curent = coada.get()
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1
            if nsol == 0:
                return

        l_succesori = graf.succesori(nod_curent)
        for succesor in l_succesori:
            coada.put(succesor)


# 4
def a_star_sol_multiple_2(graf, nsol=1):
    coada = [(NodArbore(graf.start))]
    while coada:
        nod_curent = coada.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1
            if nsol == 0:
                return

        l_succesori = graf.succesori(nod_curent)
        for succesor in l_succesori:
            indice = bin_search(coada, succesor, 0, len(coada) - 1)
            coada.insert(indice, succesor)


def bin_search(lista_noduri, nod_nou, ls, ld):
    if len(lista_noduri) == 0:
        return 0
    if ls == ld:
        if nod_nou < lista_noduri[ls]:
            return ls
        else:
            return ld + 1
    else:
        mij = (ls + ld) // 2
        if nod_nou < lista_noduri[mij]:
            return bin_search(lista_noduri, nod_nou, ls, mij)
        else:
            return bin_search(lista_noduri, nod_nou, mij + 1, ld)


m = [
    [0, 3, 5, 10, 0, 0, 100],
    [0, 0, 0, 4, 0, 0, 0],
    [0, 0, 0, 4, 9, 3, 0],
    [0, 3, 0, 0, 2, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 4, 0, 5],
    [0, 0, 3, 0, 0, 0, 0],
]

start = 0
scopuri = [4, 6]
h = [0, 1, 6, 2, 0, 3, 0]


graf = Graf(m, start, scopuri, h)

start_time = time.time()
a_star_sol_multiple(graf, nsol=3)
end_time = time.time()
print(end_time - start_time)
print()

start_time = time.time()
a_star_sol_multiple_pq(graf, nsol=3)
end_time = time.time()
print(end_time - start_time)
print()

start_time = time.time()
a_star_sol_multiple_2(graf, nsol=3)
end_time = time.time()
print(end_time - start_time)
