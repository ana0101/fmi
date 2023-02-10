from queue import Queue
n = int(input("n = "))
# pasi[i] = din cati pasi se ajunge la 1 de la numarul i
# pasi[i] => pasi[2*i] = pasi[i] + 1
#            pasi[(n-1)/3] = pasi[i] + 1, daca n-1 se divide cu 3
pasi = dict()
pasi[1] = 0

coada = Queue(maxsize=0)
coada.put(1)
i = coada.get()

while i != n:
    if i*2 not in pasi.keys():
        pasi[i*2] = pasi[i] + 1
        coada.put(i*2)
    if (i-1) % 3 == 0 and (i-1)//3 not in pasi.keys() and (i-1)//3 != 0:
        pasi[(i-1)//3] = pasi[i] + 1
        coada.put((i-1)//3)
    i = coada.get()

print(pasi[n])