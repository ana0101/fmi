import math

# a
def creare_dict(*nume_fisiere):
    d = {}
    for nume in nume_fisiere:
        f = open(nume, "r")
        listaCuv = f.read().split()
        f.close()

        for cuv in listaCuv:
            if cuv not in d.keys():
                d[cuv] = 1
            else:
                d[cuv] += 1
    return d


# b
d = creare_dict("cuvinte1.in", "cuvinte2.in")
var = sorted(d.keys())
print(var)


# c
d = creare_dict("cuvinte1.in")
var = sorted(d.items(), key = lambda t: -t[1])
print(var)


# d
d = creare_dict("cuvinte2.in")
var = min(d.items(), key = lambda t: (-t[1], t[0]))[0]
print(var)


# e
d1 = creare_dict("cuvinte1.in")
d2 = creare_dict("cuvinte2.in")
s1 = sum([d1.get(cuv, 0) * d2.get(cuv, 0) for cuv in set(d1.keys()) | set(d2.keys())])
s2 = sum([d1.get(cuv)*d1.get(cuv) for cuv in d1.keys()])
s3 = sum([d2.get(cuv)*d2.get(cuv) for cuv in d2.keys()])
r = s1 / (math.sqrt(s2) * math.sqrt(s3))
r = round(r, 2)
print(r)
