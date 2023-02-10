# a
def nrMaxime(*numere):
    rez = 0
    for nr in numere:
        cfMax = 0
        while nr > 0:
            if nr%10 > cfMax:
                cfMax = nr%10
            nr //= 10
        rez = rez*10 + cfMax
    return rez

rez = nrMaxime(4521, 73, 8, 133)
print(rez)


# b
def binare(a, b, c):
    nr = nrMaxime(a, b, c)
    while nr > 0:
        if nr%10 > 1:
            return False
        nr //= 10
    return True

print(binare(1001, 17, 100))
