n = int(input("n = "))
minim = -10000000
max1 = None
max2 = None

for i in range(n):
    x = int(input("x = "))
    if max1 == None:
        max1 = x
    else:
        if max2 == None:
            max2 = x
        else:
            if x > max1:
                max2 = max1
                max1 = x
            else:
                if x > max2 and x != max1:
                    max2 = x

if max1 != None and max2 != None:
    print("cele mai mari doua valori distincte sunt ", max1, " si ", max2)
else:
    print("imposibil")
