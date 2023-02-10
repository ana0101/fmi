# a
def litere(*cuvinte):
    dictionar = dict()
    for cuv in cuvinte:
        dictionar[cuv] = dict()
        litereCuv = list(cuv)
        setLitere = set(litereCuv)
        for lit in setLitere:
            frecv = litereCuv.count(lit)
            dictionar[cuv][lit] = frecv
    return dictionar

print(litere("teste", "programare"))

# b
numere = [x for x in range(10, 100) if x%2==0 and x%6!=0]
print(numere)

# c
# T(n) = aT(n/b) + f(n)
# a = 2, b = 2, p = 2
# logb(a) < p
# T(n) = O(f(n)) = O(n**2)