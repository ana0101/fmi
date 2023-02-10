n = int(input("n = "))

# nr[i] = numarul de moduri in care se poate ajunge pe treapta i
# nr[i] = nr[i-1] + nr[i-2] + nr[i-3]
# nr[0] = 1
nr = [0] * (n+1)
nr[0] = 1

for i in range(1, n+1):
    if i == 1:
        nr[i] = nr[0]
    elif i == 2:
        nr[i] = nr[0] + nr[1]
    else:
        nr[i] = nr[i-1] + nr[i-2] + nr[i-3]

print(nr[n])
