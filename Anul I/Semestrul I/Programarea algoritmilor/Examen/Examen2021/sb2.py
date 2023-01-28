m = int(input("m = "))
a = [int(x) for x in input("a = ").split()]

n = int(input("n = "))
b = [int(x) for x in input("b = ").split()]

a.sort(key = lambda x: x)
b.sort(key = lambda x: x)

smax = 0
sol = list()

i = 0
while a[i] < 0:
    smax += a[i] * b[i]
    sol.append((a[i], b[i]))
    i += 1

i = m-1
j = n-1
while a[i] > 0:
    smax += a[i] * b[j]
    sol.append((a[i], b[j]))
    i -= 1
    j -=1 

print(smax)
print(sol)