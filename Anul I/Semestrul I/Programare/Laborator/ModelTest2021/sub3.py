# a
fin = open("magazine.in", "r")
info = fin.read().split("\n")
fin.close()

print(info)

linie = info[0].split()
m = int(linie[0])
n = int(linie[1])

date = dict()

for i in range(1, m+1):
    linie = info[i].split(maxsplit=1)
    cod = int(linie[0])
    date[cod] = dict()
    nume = linie[1]
    date[cod]["nume magazin"] = nume

for i in range(m+1, m+n+1):
    lista = []
    linie = info[i].split(maxsplit=5)
    cod_mag = int(linie[0])
    cod_prod = int(linie[1])
    nr = int(linie[2])
    pret = float(linie[3])
    greutate = int(linie[4])
    nume_prod = linie[5]
    lista.append(nr)
    lista.append(pret)
    lista.append(greutate)
    lista.append(nume_prod)

    date[cod_mag][cod_prod] = lista

print(date)

# b
# def sterge_produs(date, cod_prod):
#     nume_mag = ""
#     for cod_mag in date.keys():
#         for cod_prod1 in date[cod_mag].keys():
#             if cod_prod == cod_prod1:
#                 nume_mag = date[cod_mag]["nume magazin"]
#                 date[cod_mag].pop(cod_prod)
#                 break
#     if nume_mag == "":
#         return None
#     else:
#         return nume_mag
#
# cod_prod = int(input("cod produs = "))
# nume_mag = sterge_produs(date, cod_prod)
#
# if nume_mag == None:
#     print("Produsul nu exista.")
# else:
#     print(f"Produsul se gasea la magazinul numit {nume_mag}.")
#
# print(date)

# c
def produse_magazin(date, cod_mag):
    if cod_mag not in date.keys():
        return []

    nume_mag = date[cod_mag]["nume magazin"]
    lista = list()

    for cod_prod in date[cod_mag].keys():
        if cod_prod != "nume magazin":
            nume_prod = date[cod_mag][cod_prod][3]
            nr = date[cod_mag][cod_prod][2]
            pret = date[cod_mag][cod_prod][1]
            greutate = date[cod_mag][cod_prod][0]
            tuplu = (nume_prod, nr, pret, greutate)
            lista.append(tuplu)
    lista.sort(key = lambda t: (-t[1], t[2]/t[3], t[0]))

    return nume_mag, lista

cod_mag = int(input("cod magazin = "))
print(produse_magazin(date, cod_mag))
