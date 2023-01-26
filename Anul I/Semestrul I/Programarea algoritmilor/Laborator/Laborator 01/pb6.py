n = int(input("n = "))
cn = n
maxim = 0
minim = 0
p2 = 1

while cn > 0:
    cfMin = 10

    while n > 0:
        if n % 10 < cfMin:
            cfMin = n % 10
        n //= 10

    n = cn
    ok = False
    p1 = 1

    while ok == False:
        if (n // p1) % 10 == cfMin:
            n = n // (p1 * 10) * p1 + n % p1
            ok = True
        else:
            p1 *= 10
    cn = n

    minim = minim * 10 + cfMin
    maxim = maxim + cfMin * p2
    p2 *= 10

print("cel mai mare numar: ", maxim)
print("cel mai mic numar: ", minim)
