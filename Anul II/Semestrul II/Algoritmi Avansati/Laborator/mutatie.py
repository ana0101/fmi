l, k = input().split()
l = int(l)
k = int(k)
c = [int(i) for i in input()]
k = [int(k2) for k2 in input().split()]

for i in k:
    if c[i] == 0:
        c[i] = 1
    elif c[i] == 1:
        c[i] = 0

c = "".join(str(i) for i in c)
print(c)
