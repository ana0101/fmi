n = int(input("n = "))
t = [int(x) for x in input("numere: ").split()]

# lungMax[i] = lungimea maxima a unui subsir care se termina pe pozitia i
lungMax = [1] * n

# pred[i] = pozitia numarului care vine in fata numarului de pe pozitia i
pred = [-1] * n

for i in range(1, n):
    for j in range(0, i):
        if t[i] >= t[j] and lungMax[j] + 1 > lungMax[i]:
            lungMax[i] = lungMax[j] + 1
            pred[i] = j

lmax = 0
for i in range(n):
    if lungMax[i] > lmax:
        lmax = lungMax[i]
        pmax = i

sol = []
i = pmax
sol.append(t[i])
while pred[i] != -1:
    sol.append(t[pred[i]])
    i = pred[i]

sol.reverse()

print(*sol)