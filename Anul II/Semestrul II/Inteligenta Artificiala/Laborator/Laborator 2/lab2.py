class NodArbore:
    def __init__(self, informatie, parinte=None):
        self.informatie = informatie
        self.parinte = parinte

    def __str__(self):
        return str(self.informatie)

    def __repr__(self):
        return "{}, ({})".format(str(self.informatie), " -> ".join([str(x) for x in self.drum_radacina()]))

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

    def afis_sol_fisier(self, fisier):
        for nod in self.drum_radacina():
            parinte = nod.parinte
            # calculez numarul de misionari si canibali de pe fiecare mal
            # verific unde se afla barca

            if nod.informatie[2] == 1:
                # barca pe malul stang
                mis_mal_curent = nod.informatie[0]
                can_mal_curent = nod.informatie[1]
                mis_mal_opus = Graf.N - mis_mal_curent
                can_mal_opus = Graf.N - can_mal_curent

                # ma uit la parinte pentru a afla cati canibali si misionari s-au mutat cu barca
                if parinte is not None:
                    mis_barca = mis_mal_curent - parinte.informatie[0]
                    can_barca = can_mal_curent - parinte.informatie[1]
                    # afisez miscarea barcii
                    fisier.write(f'Barca s-a deplasat de la malul drept la malul stang cu {mis_barca} misionari si {can_barca} canibali.\n')

                # afisez starea
                fisier.write(f'(Stanga:<barca>) {mis_mal_curent} misionari {can_mal_curent} canibali  ......  (Dreapta) {mis_mal_opus} misionari {can_mal_opus} canibali\n\n')

            else:
                # barca pe malul drept
                mis_mal_opus = nod.informatie[0]
                can_mal_opus = nod.informatie[1]
                mis_mal_curent = Graf.N - mis_mal_opus
                can_mal_curent = Graf.N - can_mal_opus

                # ma uit la parinte pentru a afla cati canibali si misionari s-au mutat cu barca
                if parinte is not None:
                    mis_barca = parinte.informatie[0] - mis_mal_opus
                    can_barca = parinte.informatie[1] - can_mal_opus
                    # afisez miscarea barcii
                    fisier.write(f'Barca s-a deplasat de la malul stang la malul drept cu {mis_barca} misionari si {can_barca} canibali.\n')

                # afisez starea
                fisier.write(f'(Stanga) {mis_mal_opus} misionari {can_mal_opus} canibali  ......  (Dreapta:<barca>) {mis_mal_curent} misionari {can_mal_curent} canibali\n\n')


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, informatie_nod):
        return informatie_nod in self.scopuri

    # (nr misionari mal curent, nr canibali mal curent, mal curent)
    # nr misionari mai curent = nr misionari mal stang (la fel si pt canibali)
    # mal initial = 1
    # mal final = 0
    # mal curent = mal cu barca

    def succesori(self, nod):

        def test_conditie(m, c):
            return m == 0 or m >= c

        l_succesori = []

        if nod.informatie[2] == 1:
            mis_mal_curent = nod.informatie[0]
            can_mal_curent = nod.informatie[1]
            mis_mal_opus = Graf.N - mis_mal_curent
            can_mal_opus = Graf.N - can_mal_curent
        else:
            mis_mal_opus = nod.informatie[0]
            can_mal_opus = nod.informatie[1]
            mis_mal_curent = Graf.N - mis_mal_opus
            can_mal_curent = Graf.N - can_mal_opus

        max_mis_barca = min(mis_mal_curent, Graf.M)
        for mb in range(max_mis_barca + 1):
            if mb == 0:
                min_can_barca = 1
                max_can_barca = min(can_mal_curent, Graf.M)
            else:
                min_can_barca = 0
                max_can_barca = min(can_mal_curent, Graf.M - mb, mb)

            for cb in range(min_can_barca, max_can_barca + 1):
                mis_mal_curent_nou = mis_mal_curent - mb
                can_mal_curent_nou = can_mal_curent - cb
                mis_mal_opus_nou = mis_mal_opus + mb
                can_mal_opus_nou = can_mal_opus + cb

                if not test_conditie(mis_mal_curent_nou, can_mal_curent_nou):
                    continue
                if not test_conditie(mis_mal_opus_nou, can_mal_opus_nou):
                    continue

                if nod.informatie[2] == 1:
                    info_succesor = (mis_mal_curent_nou, can_mal_curent_nou, 0)
                else:
                    info_succesor = (mis_mal_opus_nou, can_mal_opus_nou, 1)

                if not nod.in_drum(info_succesor):
                    l_succesori.append(NodArbore(info_succesor, nod))

        return l_succesori


def breadth_first(graf, nsol=1):
    coada = [NodArbore(graf.start)]
    while coada:
        nod_curent = coada.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nod_curent.afis_sol_fisier(g)
            g.write("\n")
            nsol -= 1
            if nsol == 0:
                return

        l_succesori = graf.succesori(nod_curent)
        coada += l_succesori


# (nr misionari mal curent, nr canibali mal curent, mal curent)
# mal initial = 1
# mal final = 0

f = open("input2.txt", "r")
[Graf.N, Graf.M] = f.readline().strip().split()
Graf.N = int(Graf.N)
Graf.M = int(Graf.M)

g = open("output2.txt", "w")

start = (Graf.N, Graf.N, 1)
scopuri = [(0, 0, 0)]

graf = Graf(start, scopuri)

breadth_first(graf, nsol=2)

# tema: 3, 4(opt)
