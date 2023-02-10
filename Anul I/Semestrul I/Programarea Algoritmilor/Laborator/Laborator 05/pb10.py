fin = open("pb10_intervale.txt", "r")
date = fin.read().split("\n")
fin.close()

intervale = []
for linie in date:
    lista = linie.split()
    lista = [int(x) for x in lista]
    intervale.append((lista[0], lista[1]))

intervale.sort(key = lambda t: (t[0], -t[1]))

fout = open("pb10_reuniune.txt", "w")
fout.writelines("Reuniunea intervalelor:\n")

lung = 0
st = intervale[0][0]
dr = intervale[0][1]

for i in range(1, len(intervale)):
    if intervale[i][0] <= dr:
        if intervale[i][1] > dr:
            dr = intervale[i][1]
    else:
        fout.writelines("[" + str(st) + "," + str(dr) + "]\n")
        lung += dr-st
        st = intervale[i][0]
        dr = intervale[i][1]

fout.writelines("[" + str(st) + "," + str(dr) + "]\n")
lung += dr-st

fout.writelines("\nLungimea reuniunii: " + str(lung))
fout.close()
