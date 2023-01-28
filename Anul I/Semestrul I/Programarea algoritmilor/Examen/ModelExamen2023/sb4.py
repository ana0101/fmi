def bkt(k):
    global sol
    global n
    for val in range(1, n+1):
        sol[k] = val
        ok = True
        for i in range(1, k):
            if sol[i] == sol[k]:
                ok = False
        if ok == True:
            if k == n:
                print(*sol[1:])
            else:
                bkt(k+1)

n = int(input("n = "))
sol = [0] * (n+1)
bkt(1)