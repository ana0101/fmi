fin = open("pb4_bani.txt", "r")
date = fin.read().split("\n")
fin.close()

bani = date[0].split()
bani = [int(x) for x in bani]
s = int(date[1])

bani.sort(key = lambda x: -x)

fout = open("pb4_plata.txt", "w")
fout.writelines(str(s) + " = ")

i = 0
while s > 0:
    k = 0
    while s-bani[i] >= 0:
        k += 1
        s -= bani[i]
    if k != 0:
        if s > 0:
            fout.writelines(str(bani[i]) + "*" + str(k) + " + ")
        else:
            fout.writelines(str(bani[i]) + "*" + str(k))
    i += 1

fout.close()
