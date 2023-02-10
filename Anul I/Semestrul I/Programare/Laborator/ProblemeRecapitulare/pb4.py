# a
fin = open("fisier.in", "r")
text = fin.read().split("\n")
fin.close()
date = {}

for linie in text:
    linie = linie.split()
    cod = linie[0]
    numar = int(linie[1])
    jucarie = " ".join(linie[2:])

    if cod not in date.keys():
        date[cod] = []
    lista = date[cod]
    for tuplu in lista:
        if tuplu[0] == jucarie:
            numar += tuplu[1]
            lista.remove(tuplu)
    tuplu = (jucarie, numar)
    lista.append(tuplu)

print(date)


# b
def despre_spiridus(date, cod):
    lista = date[cod]
    lista.sort(key = lambda t: (-t[1], t[0]))
    return lista

lista = despre_spiridus(date, "S1")
print(lista)


# c
def jucarii(date):
    multime = []
    for cod in date.keys():
        for tuplu in date[cod]:
            if tuplu[0] not in multime:
                multime.append(tuplu[0])
    multime = set(multime)
    return multime

multime = jucarii(date)
multime = list(multime)
afis = ",".join(multime)
print(afis)


# d
def spiridusi(date):
    lista = []
    for cod in date.keys():
        numar = len(date[cod])
        cantitate = 0
        for tuplu in date[cod]:
            cantitate += tuplu[1]
        t = (cod, numar, cantitate)
        lista.append(t)

    lista.sort(key = lambda t: (-t[1], -t[2], t[0]))
    return lista

lista = spiridusi(date)
for tuplu in lista:
    print(tuplu)


# e
def actualizare(date, cod, jucarie):
    if len(date[cod]) < 2:
        return False
    for i in range(len(date[cod])):
        if date[cod][i][0] == jucarie:
            date[cod].pop(i)
            return True

ok = actualizare(date, "S1", "trenulet")

lista = despre_spiridus(date, "S1")
print(lista)
