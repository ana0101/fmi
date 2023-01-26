s = input("fraza: ")
s = s.split()
c = None
p = None
sum = 0.0

for i in s:
    if '0' <= i[0] <= '9':
        if c is None:
            c = float(i)
        else:
            p = float(i)
            sum += p+c
            c = None

print(sum, " RON")
