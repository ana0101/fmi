fin = open("pb7_date.in", "r")
n = int(fin.readline())
cadou = [int(x) for x in fin.readline().split()]
cadou.insert(0, 0)
fin.close()

sumaTotala = sum(cadou)
sumaJum = sumaTotala // 2
m = sumaJum

# suma[i][j] = suma maxima care se poate obtine din primele i cadouri, mai mica sau egala cu j

suma = [[0] * (m+1) for i in range(n+1)]

for i in range(1, n+1):
    for j in range(1, m+1):
        if cadou[i] + suma[i-1][j] <= j:
            suma[i][j] = cadou[i] + suma[i-1][j]
        elif cadou[i] <= j:
            suma[i][j] = max(cadou[i] + suma[i-1][j-cadou[i]], suma[i-1][j])
        else:
            suma[i][j] = suma[i-1][j]

for linie in suma:
    print(*linie)

s1 = suma[n][m]
sol1 = []
j = suma[n][m]

while j > 0:
    for i in range(n+1):
        if suma[i][j] == j:
            sol1.append(cadou[i])
            j -= cadou[i]
            break

sol1.reverse()

s2 = sumaTotala - s1
sol2 = cadou.copy()
for i in range(len(sol1)):
    if sol1[i] in sol2:
        sol2.remove(sol1[i])
sol2.remove(0)

fout = open("pb7_date.out", "w")

fout.writelines(str(s1) + "\n")
sol1 = " ".join([str(x) for x in sol1])
fout.writelines(sol1 + "\n")

fout.writelines(str(s2) + "\n")
sol2 = " ".join([str(x) for x in sol2])
fout.writelines(sol2)

fout.close()