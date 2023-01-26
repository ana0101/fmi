# a
#l = [chr(x) for x in range(ord('a'), ord('z')+1)]
#print(l)

# b
# n = int(input("n = "))
# l = [x if x%2!=0 else -x for x in range(1, n+1)]
# print(l)

# c
# l1 = [int(x) for x in input("numere: ").split()]
# l2 = [x for x in l1 if x%2==1]
# print(l2)

# d
# l1 = [int(x) for x in input("numere: ").split()]
# n = len(l1)
# l2 = [l1[i] for i in range(1, n, 2)]
# print(l2)

# e
# l1 = [int(x) for x in input("numere: ").split()]
# n = len(l1)
# l2 = [l1[i] for i in range(n) if l1[i]%2 == i%2]
# print(l2)

# f
# l1 = [int(x) for x in input("numere: ").split()]
# n = len(l1)
# l2 = [(l1[i], l1[i+1]) for i in range(n-1)]
# print(l2)

# g
# n = int(input("n = "))
# l = [[f"{x}*{y}={x*y}" for y in range(1, n+1)] for x in range(1, n+1)]
# for i in l:
#     print(*i)

# h
# s = input("sir: ")
# n = len(s)
# l = [s[i:] + s[:i] for i in range (n)]
# print(l)

# i
n = int(input("n = "))
l = [[i]*i for i in range(n)]
print(l)
