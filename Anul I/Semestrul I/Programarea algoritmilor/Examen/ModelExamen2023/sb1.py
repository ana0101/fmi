# a
def divizori(*numere):
    dictionar = dict()
    for nr in numere:
        lista = []
        n = nr
        for div in range(2, nr//2+1):
            if nr % div == 0:
                lista.append(div)
                while nr % div == 0:
                    nr //= div
        dictionar[n] = lista
    return dictionar

print(divizori(50, 21))

# b
litere_10 = [chr(x) for x in range(97, 107)]
print(litere_10)

# c
# T(1) = T(2) = 1
# T(n) = T(n/3) + 2
# a = 1, b = 3, p = 0
# logb(a) = 0 => logb(a) = p
# T(n) = O(n**p * log2(n)) = O(log2(n))