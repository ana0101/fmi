t = input("subsir t = ")
s = input("sir s = ")
l = len(t)

# varianta cu metoda find

#p = s.find(t)
#if p == -1:
 #   print("nu exista")
#else:
 #   print("pozitii:")
  #  while p != -1:
   #     print(p)
    #    p = s.find(t, p+1)


# varianta cu metoda index
try:
    p = s.index(t)
except ValueError:
    print("nu exista")
else:
    print("pozitii:")
    print(p)

while True:
    try:
        p = s.index(t, p+1)
    except ValueError:
        break
    else:
        print("pozitii:")
        print(p)
