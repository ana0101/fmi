# a
fin = open("cinema.in", "r")
text = fin.read().split("\n")
date = {}
for linie in text:
    linie = linie.split(" % ")
    if linie[0] in date:
        film = date[linie[0]]
    else:
        film = {}
    ore = linie[2].split(" ")
    film[linie[1]] = ore
    date[linie[0]] = film
print(date)


# b
# def sterge_ore(date, cinema, film, ore):
#     for ora in ore:
#         if ora in date[cinema][film]:
#             date[cinema][film].remove(ora)
#     lista = []
#
#     if date[cinema][film] == []:
#         date[cinema].pop(film)
#     else:
#         lista.append(film)
#
#     for f in date[cinema]:
#         lista.append(f)
#
#     return lista
#
# f = input("nume film = ")
# c = input("nume cinematograf = ")
# o = [input("ora = ")]
#
# print(sterge_ore(date, c, f, o))
# print(date)


# c
def cinema_film(date, *cinematografe, ora_minima, ora_maxima):
    lista = []
    for nume_cinema in cinematografe:
        for nume_film in date[nume_cinema]:
            lista_de_ore = []
            for ora in date[nume_cinema][nume_film]:
                if ora >= ora_minima and ora <= ora_maxima:
                    lista_de_ore.append(ora)
            if lista_de_ore != []:
                tuplu = (nume_film, nume_cinema, lista_de_ore)
                lista.append(tuplu)

    lista.sort(key = lambda t: (t[0], -len(t[2])))
    return lista

print(cinema_film(date, "Cinema 1", "Cinema 2", ora_minima = "14:00", ora_maxima = "22:00"))
