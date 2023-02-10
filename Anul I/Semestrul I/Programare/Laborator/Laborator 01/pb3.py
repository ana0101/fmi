l1 = float(input("l1 = "))
l2 = float(input("l2 = "))

cl1 = l1
cl2 = l2

while l2 > 0:
    r = l1 % l2
    l1 = l2
    l2 = r

lat = l1
nr = (cl1*cl2) / (lat*lat)

print(nr, " de placi, fiecare cu latura de ", lat, " cm")
