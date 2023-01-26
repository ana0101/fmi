a = int(input("a = "))
b = int(input("b = "))
c = int(input("c = "))

d = b*b - 4*a*c

if d < 0:
    print("ecuatia nu are nicio radacina")
else:
    if d == 0:
        x = (-b) / (2*a)
        print("ecuatia are radacina x = ", x)
    else:
        x1 = (-b + d**0.5) / (2*a)
        x2 = (-b - d**0.5) / (2*a)
        print("ecuatia are radacinile x1 = ", x1, " si x2 = ", x2)
        