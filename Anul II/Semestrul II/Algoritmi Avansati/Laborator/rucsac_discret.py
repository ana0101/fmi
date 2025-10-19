n, c = input().split()
n = int(n)
c = int(c)

v = [int(x) for x in input().split()]
g = [int(x) for x in input().split()]

r = [(v[i] / g[i], i) for i in range(n)]
r.sort(reverse=True)

d = [0 for i in range(c+1)]

for i in range(1, n+1):
    for gr in range(c, 0, -1):
        if g[i-1] <= gr:
            d[gr] = max(d[gr], d[gr - g[i-1]] + v[i-1])

print(d[c])
