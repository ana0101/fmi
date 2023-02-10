s = "subsir"
t = "rustic"

# lung[i][j] = lungimea maxima a unui subsir comun din primele i litere ale lui s si primele j litere ale lui t
lung = [[0] * (len(t)+1) for i in range(len(s)+1)]

for i in range(1, len(s)+1):
    for j in range(1, len(t)+1):
        if s[i-1] == t[j-1]:
            lung[i][j] = 1 + lung[i-1][j-1]
        else:
            lung[i][j] = max(lung[i-1][j], lung[i][j-1])

for linie in lung:
    print(*linie)

i = len(s)
j = len(t)
sol = []

while lung[i][j] != 0:
    if s[i-1] == t[j-1]:
        sol.append(s[i-1])
        i -= 1
        j -= 1
    elif lung[i][j] == lung[i-1][j] == lung[i][j-1]:
        i -= 1
        j -= 1
    elif lung[i][j] == lung[i-1][j]:
        i -= 1
    elif lung[i][j] == lung[i][j-1]:
        j -= 1

sol.reverse()
print(*sol)
