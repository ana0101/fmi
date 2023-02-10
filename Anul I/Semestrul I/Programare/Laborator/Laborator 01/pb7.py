x = float(input("x = "))
n = float(input("n = "))
p = float(input("p = "))
m = float(input("m = "))

cn = n
d = 0

while m >= n:
    d += x*n
    x = x - p/100*x
    m -= n

d += m*x

print("distanta este de ", d, " cm")
