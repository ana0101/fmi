# a
# l = [int(x) for x in input("numere: ").split()]
# l.sort(key = lambda x:str(x))
# print(l)

# b
# l = [int(x) for x in input("numere: ").split()]
# l.sort(key = lambda x: str(x)[::-1])
# print(l)

# c
# l = [int(x) for x in input("numere: ").split()]
# l.sort(key = lambda x: (len(str(x))), reverse = True)
# print(l)

# d
# l = [int(x) for x in input("numere: ").split()]
# l.sort(key = lambda x: (len(set(str(x)))))
# print(l)

# e
l = [int(x) for x in input("numere: ").split()]
l.sort(key = lambda x: (len(str(x)), x))
print(l)
