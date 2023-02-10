# a
def completare_a(matrice_a, n, ln_sus, col_st):
    global k
    if n == 1:
        matrice_a[ln_sus][col_st] = k
        k += 1
    else:
        n //= 2
        completare_a(matrice_a, n, ln_sus, col_st + n)
        completare_a(matrice_a, n, ln_sus + n, col_st)
        completare_a(matrice_a, n, ln_sus, col_st)
        completare_a(matrice_a, n, ln_sus + n, col_st + n)

n = int(input("n = "))
matrice_a = [[0] * (2**n) for i in range(2**n)]

k = 1
completare_a(matrice_a, 2**n, 0, 0)

for linie in matrice_a:
    print(*linie)


# b
def completare_b(matrice_b, n, m, ln_sus, col_st):
    global k
    if n == m == 1:
        matrice_b[ln_sus][col_st] = k
        k += 1
    elif n == 1:
        m //= 2
        completare_b(matrice_b, n, m, ln_sus, col_st)
        completare_b(matrice_b, n, m, ln_sus, col_st + m)
    elif m == 1:
        n //= 2
        completare_b(matrice_b, n, m, ln_sus, col_st)
        completare_b(matrice_b, n, m, ln_sus + n, col_st)
    else:
        n //= 2
        m //= 2
        completare_b(matrice_b, n, m, ln_sus, col_st)
        completare_b(matrice_b, n, m, ln_sus, col_st + m)
        completare_b(matrice_b, n, m, ln_sus + n, col_st)
        completare_b(matrice_b, n, m, ln_sus + n, col_st + m)

n = int(input("n = "))
m = int(input("m = "))
matrice_b = [[0] * (2**m) for i in range(2**n)]

k = 1
completare_b(matrice_b, 2**n, 2**m, 0, 0)

for linie in matrice_b:
    print(*linie)