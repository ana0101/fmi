fin = open("v1_date.in", "r")
n = int(fin.readline())
v = [int(x) for x in fin.readline().split()]
fin.close()

st = 0
dr = n-1

while st <= dr:
    mij = (st+dr) // 2
    if v[mij-1] < v[mij] > v[mij+1]:
        vf = v[mij]
        break
    elif v[mij-1] > v[mij]:
        dr = mij-1
    elif v[mij] < v[mij+1]:
        st = mij+1

fout = open("v1_date.out", "w")
fout.writelines(str(vf))
fout.close()