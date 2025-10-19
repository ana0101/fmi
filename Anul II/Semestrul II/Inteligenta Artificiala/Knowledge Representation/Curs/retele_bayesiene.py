import copy

alpha = 1
beta = 1

class Node:
    def __init__(self, informatie, probabilitate, parinti=[], probabilitate_parinti=[]):
        self.informatie = informatie
        self.probabilitate = probabilitate
        self.parinti = copy.deepcopy(parinti)
        self.probabilitate_parinti = copy.deepcopy(probabilitate_parinti)
        self.copii = []

        for parinte in parinti:
            if self not in parinte.copii:
                parinte.copii.append(self)

    def __eq__(self, other):
        self.informatie == other.informatie

    def __hash__(self):
        return id(self)

    def repartitie_uniforma(self):
        return 1

    def conditionat(self, parinti):
        n = len(self.parinti)
        poz = 0
        for i in range(n):
            if self.parinti[i] in parinti:
                poz += 2 ** (n - i - 1)
        return self.probabilitate_parinti[poz]


def interogare_retea(x):
    return suport_except(x, None)

def suport_except(x, v):
    if x.probabilitate:
        return x.probabilitate

    probabilitate_copii = dovezi_except(x, v)
    u = x.parinti
    if not u:
        return alpha * probabilitate_copii * x.probabilitate

    probabilitate_parinti = 1
    p_x = 0
    for ui in u:
        probabilitate_parinti = suport_except(ui, x)
        p_x += x.conditionat(ui)
    return alpha * probabilitate_copii * p_x * probabilitate_parinti * sum([x.conditionat(ui) for ui in u])

def dovezi_except(x, v):
    y = copy.deepcopy(x.copii)
    if v and v in y:
        y.remove(v)
    if not y:
        return x.repartitie_uniforma()
    for yi in y:
        probabilitate_copii = dovezi_except(yi, None)
        zi = copy.deepcopy(x.parinti)
        if x in zi:
            zi.remove(x)
        p_yi = 0
        p_parinti_copii = 1
        for zij in zi:
            p_parinti_copii *= suport_except(zij, yi)
            p_yi += yi.conditionat([x, zij])
    return beta * probabilitate_copii * p_yi * p_parinti_copii


curent = Node('curent', 0.7)
bec = Node('bec', parinti=[curent], probabilitate_parinti=[0.3, 0.7])
print(interogare_retea(bec))
