l = int(input())
x0 = input()
x1 = input()
i = int(input())

x2 = x0[:i] + x1[i:]
x3 = x1[:i] + x0[i:]

print(x2)
print(x3)
