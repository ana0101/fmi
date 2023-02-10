def acoperire(tabla, n, ln_sus, col_st, ln_g, col_g):
    global k
    if n == 2:
        for i in range(ln_sus, ln_sus+2):
            for j in range(col_st, col_st+2):
                if i == ln_g and j == col_g:
                    continue
                else:
                    tabla[i][j] = k
        k += 1

    else:
        # daca gaura se afla in cadranul 1
        if ln_g <= (ln_sus + (ln_sus+n-1)) // 2 and col_g > (col_st + (col_st+n-1)) // 2:
            m = n//2
            # acopar cadranul 1
            acoperire(tabla, m, ln_sus, col_st + m, ln_g, col_g)
            # pun coltul
            tabla[ln_sus + m - 1][col_st + m - 1] = k
            tabla[ln_sus + m][col_st + m - 1] = k
            tabla[ln_sus + m][col_st + m] = k
            k += 1
            # acopar si restul cadranelor cu gaura pe care am completat-o cu coltul
            # cadranul 2
            acoperire(tabla, m, ln_sus, col_st, ln_sus + m - 1, col_st + m - 1)
            # cadranul 3
            acoperire(tabla, m, ln_sus + m, col_st, ln_sus + m, col_st + m - 1)
            # cadranul 4
            acoperire(tabla, m, ln_sus + m, col_st + m, ln_sus + m, col_st + m)

        # daca gaura se afla in cadranul 2
        elif ln_g <= (ln_sus + (ln_sus+n-1)) // 2 and col_g <= (col_st + (col_st+n-1)) // 2:
            m = n//2
            # acopar cadranul 2
            acoperire(tabla, m, ln_sus, col_st, ln_g, col_g)
            # pun coltul
            tabla[ln_sus + m - 1][col_st + m] = k
            tabla[ln_sus + m][col_st + m - 1] = k
            tabla[ln_sus + m][col_st + m] = k
            k += 1
            # acopar si restul cadranelor cu gaura pe care am completat-o cu coltul
            # cadranul 1
            acoperire(tabla, m, ln_sus, col_st + m, ln_sus + m - 1, col_st + m)
            # cadranul 3
            acoperire(tabla, m, ln_sus + m, col_st, ln_sus + m, col_st + m - 1)
            # cadranul 4
            acoperire(tabla, m, ln_sus + m, col_st + m, ln_sus + m, col_st + m)

        # daca gaura se afla in cadranul 3
        elif ln_g > (ln_sus + (ln_sus+n-1)) // 2 and col_g <= (col_st + (col_st+n-1)) // 2:
            m = n//2
            # acopar cadranul 3
            acoperire(tabla, m, ln_sus + m, col_st, ln_g, col_g)
            # pun coltul
            tabla[ln_sus + m - 1][col_st + m] = k
            tabla[ln_sus + m - 1][col_st + m - 1] = k
            tabla[ln_sus + m][col_st + m] = k
            k += 1
            # acopar si restul cadranelor cu gaura pe care am completat-o cu coltul
            # cadranul 1
            acoperire(tabla, m, ln_sus, col_st + m, ln_sus + m - 1, col_st + m)
            # cadranul 2
            acoperire(tabla, m, ln_sus, col_st, ln_sus + m - 1, col_st + m - 1)
            # cadranul 4
            acoperire(tabla, m, ln_sus + m, col_st + m, ln_sus + m, col_st + m)

        # daca gaura se afla in cadranul 4
        elif ln_g > (ln_sus + (ln_sus + n - 1)) // 2 and col_g > (col_st + (col_st + n - 1)) // 2:
            m = n // 2
            # acopar cadranul 4
            acoperire(tabla, m, ln_sus + m, col_st + m, ln_g, col_g)
            # pun coltul
            tabla[ln_sus + m - 1][col_st + m] = k
            tabla[ln_sus + m - 1][col_st + m - 1] = k
            tabla[ln_sus + m][col_st + m - 1] = k
            k += 1
            # acopar si restul cadranelor cu gaura pe care am completat-o cu coltul
            # cadranul 1
            acoperire(tabla, m, ln_sus, col_st + m, ln_sus + m - 1, col_st + m)
            # cadranul 2
            acoperire(tabla, m, ln_sus, col_st, ln_sus + m - 1, col_st + m - 1)
            # cadranul 3
            acoperire(tabla, m, ln_sus + m, col_st, ln_sus + m, col_st + m - 1)

fin = open("m2_date.in", "r")
n = int(fin.readline())
lg, cg = [int(x) for x in fin.readline().split()]
fin.close()

tabla = [[-1] * (2**n+1) for i in range(2**n+1)]
tabla[lg][cg] = 0
k = 1
acoperire(tabla, 2**n, 1, 1, lg, cg)

fout = open("m2_date.out", "w")
for i in range(1, 2**n+1):
    linie = tabla[i]
    linie.remove(-1)
    linie = [str(x) for x in linie]
    for i in range(len(linie)):
        if len(linie[i]) == 1:
            linie[i] = " " + linie[i]
    linie = " ".join(linie)
    fout.writelines(linie + "\n")
fout.close()