def drept(colt1, colt2, copaci):
    global arie_max, dr1, dr2
    ok = True
    for c in copaci:
        if colt1[0] < c[0] < colt2[0] and colt1[1] < c[1] < colt2[1]:
            ok = False
            c1 = (colt1[0], colt1[1])
            c2 = (c[0], colt2[1])
            drept(c1, c2, copaci)

            c1 = (c[0], colt1[1])
            c2 = (colt2[0], colt2[1])
            drept(c1, c2, copaci)

            c1 = (colt1[0], colt1[1])
            c2 = (colt2[0], c[1])
            drept(c1, c2, copaci)

            c1 = (colt1[0], c[0])
            c2 = (colt2[0], colt2[1])
            drept(c1, c2, copaci)

    if ok == True:
        arie = (colt2[0] - colt1[0]) * (colt2[1] - colt1[1])
        if arie > arie_max:
            arie_max = arie
            dr1 = colt1
            dr2 = colt2


fin = open("pb1_copaci.in", "r")
date = fin.read().split("\n")

padure = []
copaci = []

for i in range(len(date)):
    linie = date[i].split()
    linie = [int(x) for x in linie]
    t = (linie[0], linie[1])
    if i < 2:
        padure.append(t)
    else:
        copaci.append(t)

arie_max = 0
dr1 = (0, 0)
dr2 = (0, 0)

drept(padure[0], padure[1], copaci)

fout = open("pb1_copaci.out", "w")

fout.writelines("Dreptunghiul:\n")

lista_dr1 = [dr1[0], dr1[1]]
lista_dr1 = [str(x) for x in lista_dr1]
str_dr1 = " ".join(lista_dr1)
fout.writelines(str_dr1 + "\n")

lista_dr2 = [dr2[0], dr2[1]]
lista_dr2 = [str(x) for x in lista_dr2]
str_dr2 = " ".join(lista_dr2)
fout.writelines(str_dr2 + "\n")

fout.writelines("Aria maxima:\n")
fout.writelines(str(arie_max))
