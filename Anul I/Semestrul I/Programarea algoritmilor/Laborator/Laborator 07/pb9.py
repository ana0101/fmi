fin = open("pb9_date.in", "r")
n, p = fin.readline().split()
n = int(n)
p = int(p)

cub = list()
for i in range(n):
    aux = fin.readline().split()
    aux = [int(x) for x in aux]
    aux = tuple(aux)
    cub.append(aux)

cub.sort(key = lambda t: (-t[0], t[1]))
cub.insert(0,(0,0))
print(cub)

# hmax[i] = inaltimea maxima a unui turn care se termina cu cubul i
# pred[i] = indicele cubului peste care este cubul i
# nr[i] = in cate moduri se poate obtine inaltimea maxima a unui turn care se termina cu cubul i

hmax = [0] * (n+1)
pred = [0] * (n+1)
nr = [1] * (n+1)

for i in range(1, n+1):
    h = 0
    k = 1
    for j in range(1, i):
        if cub[i][1] != cub[j][1] and cub[i][0] != cub[j][0]:
            if hmax[j] > h:
                h = hmax[j]
                pred[i] = j
                nr[i] = nr[pred[i]]
            elif hmax[j] == h:
                nr[i] += nr[pred[i]]
    hmax[i] = cub[i][0] + h

print(hmax)
print(nr)

hMax = max(hmax)
nrMax = 0
for i in range(1, n+1):
    if hmax[i] == hMax:
        nrMax += nr[i]
        ind = i

sol = list()
while hMax > 0:
    sol.append(cub[ind])
    hMax -= cub[ind][0]
    ind = pred[ind]

sol.reverse()
print(sol)

fout = open("pb9_date.out", "w")
for i in range(len(sol)):
    aux = " ".join([str(x) for x in sol[i]])
    fout.writelines(aux + "\n")
fout.writelines(str(nrMax))
fout.close()