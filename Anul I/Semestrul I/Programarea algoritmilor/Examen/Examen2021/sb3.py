n = int(input("n = "))
cuv = input("sir cuvinte = ").split()
n = len(cuv)

# lung[i] = lungimea maxima a unui sir care se termina cu cuvantul i
lung = [1] * n

# pred[i] = indicele cuvantului care este inaintea cuvantului i in sir
pred = [-1] * n

# nr[i] = numarul de moduri prin care se poate obtine lungimea maxima a unui sir care se termina cu cuvantul i
nr = [1] * n

for i in range(1, n):
    for j in range(i):
        if abs(ord(cuv[i][0]) - ord(cuv[j][-1])) == 1:
            if lung[j] + 1 > lung[i]:
                lung[i] = lung[j] + 1
                pred[i] = j
                nr[i] = nr[j]
            elif lung[j] + 1 == lung[i]:
                nr[i] += nr[j]

lmax = max(lung)
unic = True
k = 0
for i in range(n):
    if lung[i] == lmax:
        ind_max = i
        k += 1
if k > 1:
    unic = False

if nr[ind_max] > 1:
    unic = False

cuv_rel = list()
i = ind_max
while pred[i] != -1:
    cuv_rel.append(cuv[i])
    i = pred[i]
cuv_rel.append(cuv[i])

cuv_rel.reverse()
sol = list()
for i in range(n):
    if cuv[i] not in cuv_rel:
        sol.append(cuv[i])

#print(*lung)
#print(*nr)
#print(*cuv_rel)

print(*sol)
if unic == True:
    print("solutia este unica")
else:
    print("solutia nu este unica")