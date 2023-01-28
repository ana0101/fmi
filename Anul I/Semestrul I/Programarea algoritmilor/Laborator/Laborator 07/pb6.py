fin = open("pb6_date.in", "r")
n = int(fin.readline())
nr = [int(x) for x in fin.readline().split()]
nr.insert(0, 0)
m = int(fin.readline())
fin.close()

# matrice[i][j] = 1, daca se poate obtine suma j cu primele i numere din nr
#               = 0, daca nu se poate obtine suma j cu primele i numere din nr

matrice = [[-1] * (m+1) for i in range(n+1)]
for i in range(n+1):
    matrice[i][0] = 0
for j in range(m+1):
    matrice[0][j] = 0

for i in range(1, n+1):
    for j in range(1, m+1):
        if nr[i] == j:
            matrice[i][j] = 1
        elif nr[i] > j:
            matrice[i][j] = matrice[i-1][j]
        elif nr[i] < j:
            matrice[i][j] = max(matrice[i-1][j], matrice[i-1][j-nr[i]])

for linie in matrice:
    print(*linie)

fout = open("pb6_date.out", "w")

if matrice[n][m] == 0:
    fout.writelines("Nu exista")
    fout.close()
else:
    j = m
    sol = []
    while j > 0:
        for i in range(n+1):
            if matrice[i][j] == 1:
                sol.append(nr[i])
                j -= nr[i]
                break

    sol.reverse()
    sol = [str(x) for x in sol]
    sol = " ".join(sol)
    fout.writelines(sol)
    fout.close()