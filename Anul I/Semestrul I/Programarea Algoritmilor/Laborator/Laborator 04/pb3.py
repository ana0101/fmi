fin = open("test.in", "r")
test = fin.read().split()
fin.close()

rezTest = open("test.out", "w")
nota = 1

for linie in test:
    n1 = 0
    n2 = 0
    r = 0
    i = 0
    while linie[i] != "*":
        n1 = n1*10 + int(linie[i])
        i += 1
    i += 1
    while linie[i] != "=":
        n2 = n2*10 + int(linie[i])
        i += 1
    i += 1
    while i < len(linie):
        r = r*10 + int(linie[i])
        i += 1
    if n1*n2 == r:
        rezLinie = linie + " Corect\n"
        nota += 1
    else:
        rezLinie = linie + " Gresit " + str(n1*n2) + "\n"
    rezTest.writelines(rezLinie)
rezLinie = "Nota " + str(nota)
rezTest.writelines(rezLinie)

rezTest.close()
