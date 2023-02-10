fin = open("pb4_date.in", "r")
cuv = fin.read().split()
fin.close()

# lung[i] = lungimea subsirului maxim care se termina pe pozitia i
lung = [1] * (len(cuv)+1)

# pred[i] = pozitia cuvantului din fata celui de pe pozitia i
pred = [-1] * (len(cuv)+1)

lmax = 1

for i in range(len(cuv)):
    for j in range(i):
        if cuv[i][:2] == cuv[j][-2:] and lung[j] + 1 > lung[i]:
            lung[i] = lung[j] + 1
            pred[i] = j
            if lung[i] > lmax:
                lmax = lung[i]
                pmax = i

sol = [cuv[pmax]]
while pred[pmax] != -1:
    sol.append(cuv[pred[pmax]])
    pmax = pred[pmax]

sol.reverse()
sol = "\n".join(sol)

fout = open("pb4_date.out", "w")
fout.writelines(sol)
fout.close()
