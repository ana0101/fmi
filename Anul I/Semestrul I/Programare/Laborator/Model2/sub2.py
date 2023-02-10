# a
fin = open("cinema.in", "r")
info = fin.read().split("\n")
date = {}

for linie in info:
    linie = linie.split("%")

    cinema = linie[0].strip()
    date.setdefault(cinema)
    if date[cinema] == None:
        date[cinema] = {}

    film = linie[1].strip()
    ore = linie[2].strip().split()

    date[cinema][film] = ore

print(date)

# b
# def sterge_ore(date, cinema, film, ore):
#     for ora in ore:
#         date[cinema][film].remove(ora)
#
#     if date[cinema][film] == []:
#         date[cinema].pop(film)
#
#     lista = []
#     for f in date[cinema]:
#         lista.append(f)
#     return lista
#
#
# f = input("film: ")
# c = input("cinematograf: ")
# o = {input("ora: ")}
#
# lista = sterge_ore(date, c, f, o)
# print(lista)
#
# print(date)

# c
def cinema_film(date, *cinemauri, ora_minima, ora_maxima):
    lista = []
    for cinema in cinemauri:
        for film in date[cinema]:
            print(film)
            lista_ore = []
            for ora in date[cinema][film]:
                if ora_minima <= ora <= ora_maxima:
                    lista_ore.append(ora)
            if lista_ore != []:
                tuplu = (film, cinema, lista_ore)
                lista.append(tuplu)

    lista.sort(key = lambda t: (t[0], -len(t[2])))
    return lista

print(cinema_film(date, "Cinema 1", "Cinema 2", ora_minima = "14:00", ora_maxima = "22:00"))
