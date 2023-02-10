from random import *
from string import *

fin = open("date.in", "r")
date = fin.read().split("\n")
fin.close()
fout = open("date.out", "w")

for linie in date:
    linie = linie.split()
    nume = linie[0].lower()
    prenume = linie[1].lower()
    email = prenume + "." + nume + "@s.unibuc.ro"
    parola = "".join(choices(ascii_letters, k=4) + choices(digits, k=3)).title()
    rezLinie = email + "," + parola + "\n"
    fout.writelines(rezLinie)
