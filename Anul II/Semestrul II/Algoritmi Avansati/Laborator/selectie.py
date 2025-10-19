def calc_fitness(x, a, b, c):
    return a * x**2 + b * x + c

def calc_sum_part(f):
    for i in range(1, len(f)):
        f[i] = f[i-1] + f[i]

a, b, c = input().split()
a = int(a)
b = int(b)
c = int(c)

n = int(input())

x = [float(y) for y in input().split()]

f = [calc_fitness(y, a, b, c) for y in x]
calc_sum_part(f)

capete = [0]
suma_fitness = f[len(f) - 1]

for s in f:
    capete.append(s / suma_fitness)

for c in capete:
    print(format(c, '.6f'))
