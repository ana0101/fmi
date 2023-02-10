n = int(input("n = "))
c1 = float(input("curs = "))

maxim = -1000000

for i in range(2, n+1):
    c2 = float(input("curs = "))
    if c2-c1 > maxim:
        maxim = c2-c1
        zi1 = i-1
        zi2 = i
    c1 = c2
