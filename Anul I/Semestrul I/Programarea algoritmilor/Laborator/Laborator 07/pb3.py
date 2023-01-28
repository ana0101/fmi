fin = open("pb3_date.in", "r")
v = [int(x) for x in fin.read().split()]
fin.close()

# s[i] = suma maxima a subsecventei care se termina pe pozitia i
s = [0] * (len(v) + 1)
s[0] = v[0]
smax = v[0]

for i in range(1, len(v)):
    s[i] = max(v[i], v[i] + s[i-1])
    if s[i] > smax:
        smax = s[i]
        pmax = i

sol = []
while smax > 0:
    sol.append(v[pmax])
    smax -= v[pmax]
    pmax -= 1

sol.reverse()
sol = [str(x) for x in sol]
sol = " ".join(sol)

fout = open("pb3_date.out", "w")
fout.writelines(sol)
fout.close()