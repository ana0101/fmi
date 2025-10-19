n, c = input().split()
n = int(n)
c = int(c)

v = [int(x) for x in input().split()]
g = [int(x) for x in input().split()]

r = [(v[i] / g[i], i) for i in range(n)]
r.sort(reverse=True)

s = 0

for x in r:
    i = x[1]
    if c - g[i] >= 0:
        # luam tot obiectul
        c -= g[i]
        s += v[i]
    else:
        # luam o parte din obiect
        p = c / g[i]
        s += p * v[i]
        break

print(s)
