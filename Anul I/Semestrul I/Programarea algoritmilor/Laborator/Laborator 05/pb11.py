import queue
pq = queue.PriorityQueue()

fin = open("pb11_lungimi.txt", "r")
k = 0
for linie in fin:
    lista = linie.split()
    pq.put((int(lista[1]), lista[0]))
    k += 1
fin.close()

fout = open("pb11_interclasari.txt", "w")
deplasari = []

i = 1
while pq.qsize() >= 2:
    fout.writelines("Pas " + str(i) + ":\n")
    fout.writelines("Structura contine: ")
    fout.writelines(str(pq.queue))
    fout.writelines("\n")

    v1 = pq.get()
    v2 = pq.get()
    lung = v1[0] + v2[0]
    deplasari.append(lung)

    v3 = (lung, "L" + str(i+k))
    pq.put(v3)

    fout.writelines("Din vectorii (" + str(v1[0]) + "," + str(v1[1]) + ")" + " si (" + str(v2[0]) + "," + str(v2[1]) + ")" + " rezulta (" + str(v3[0]) + "," + str(v3[1]) + ")\n\n")

    i += 1

fout.writelines("Pas " + str(i) + ":\n")
fout.writelines("Structura contine: ")
fout.writelines(str(pq.queue))

fout.writelines("\n\nNumar total deplasari: ")
suma = sum(deplasari)
deplasari = [str(x) for x in deplasari]
linie = " + ".join(deplasari)
linie += " = " + str(suma)
fout.writelines(linie)
fout.close()
