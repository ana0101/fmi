fin = open("pb8_date.in", "r")
n, m = fin.readline().split()
n = int(n)
m = int(m)

tabla = [[0] * (m+1) for i in range(n+1)]
for i in range(1, n+1):
    tabla[i] = [int(x) for x in fin.readline().split()]
    tabla[i].insert(0, 0)
fin.close()

for linie in tabla:
    print(*linie)
print("\n")

# suma[i][j] = suma maxima care poate fi adunata de la 1,1 pana la i,j

suma = [[0] * (m+1) for i in range(n+1)]

for i in range(1, n+1):
    for j in range(1, m+1):
        suma[i][j] = tabla[i][j] + max(suma[i-1][j], suma[i][j-1])

for linie in suma:
    print(*linie)

smax = suma[n][m]
fout = open("pb8_date.out", "w")
fout.writelines(str(smax) + "\n")

sol = list()
i = n
j = m

while smax > 0:
    sol.append([i, j])
    smax -= tabla[i][j]
    if suma[i-1][j] > suma[i][j-1]:
        i -= 1
    else:
        j -= 1

sol.reverse()
for coord in sol:
    linie = " ".join([str(x) for x in coord])
    fout.writelines(linie + "\n")