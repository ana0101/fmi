prop = input("propozitie: ")
s = input("cuvant s: ")
t = input("cuvant t: ")

cuvinte = prop.split()

for i in range(len(cuvinte)):
    if cuvinte[i] == s:
        cuvinte[i] = t

prop = " ".join(cuvinte)

print("noua propozitie: ", prop)
