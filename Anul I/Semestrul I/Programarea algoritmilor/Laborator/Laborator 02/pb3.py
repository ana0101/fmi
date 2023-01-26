s = input("sir: ")
l = len(s)
k = 0

while k < l//2+1:
    print(s[k:(l-k)].center(10))
    k += 1
