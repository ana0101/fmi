def mediana(a, b, n):
    if n == 1:
        return (a[0] + b[0]) / 2
    elif n == 2:
        return (max(a[0], b[0]) + min(a[1], b[1])) / 2
    else:
        ma = mediana2(a, n)
        mb = mediana2(b, n)
        if ma == mb:
            return ma
        elif ma < mb:
            if n%2 == 1:
                return mediana(a[n//2:], b[:n//2+1], n//2+1)
            else:
                return mediana(a[n//2-1:], b[:n//2+1], n//2+1)
        elif ma > mb:
            if n%2 == 1:
                return mediana(a[:n//2+1], b[n//2:], n//2+1)
            else:
                return mediana(a[:n//2+1], b[n//2-1:], n//2+1)

def mediana2(v, n):
    if n%2 == 0:
        return (v[n//2-1] + v[n//2]) / 2
    else:
        return v[n//2]

fin = open("v2_date.in", "r")
n = int(fin.readline())
a = [int(x) for x in fin.readline().split()]
b = [int(x) for x in fin.readline().split()]
fin.close()

m = mediana(a, b, n)
fout = open("v2_date.out", "w")
fout.writelines(str(m))