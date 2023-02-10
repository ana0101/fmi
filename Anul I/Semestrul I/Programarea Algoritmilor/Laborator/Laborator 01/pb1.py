n = int(input("n = "))
cn = n
ogl = 0
while n > 0:
    ogl = ogl*10 + n%10
    n //= 10

n = cn
if n == ogl:
    print("n este palindrom")
else:
    print("n nu este palindrom")
