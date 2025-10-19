import math


def calc_nr_biti(a, b, p):
    return int(math.log2((b - a) * (10 ** p))) + 1


def calc_pas_discretizare(a, b, l):
    return (b - a) / (2 ** l)


def codificare(x, a, d, l):
    index = int((x - a) / d)
    return bin(index).lstrip('0b').zfill(l)


def decodificare(binar, a, d):
    index = int(binar, 2)
    return format(a + index * d, '.6f')


a, b = input().split()
a = int(a)
b = int(b)
p = int(input())

l = calc_nr_biti(a, b, p)
d = calc_pas_discretizare(a, b, l)

m = int(input())

for i in range(m):
    tip = input()
    if tip == "TO":
        x = float(input())
        print(codificare(x, a, d, l))
    elif tip == "FROM":
        binar = input()
        print(decodificare(binar, a, d))
