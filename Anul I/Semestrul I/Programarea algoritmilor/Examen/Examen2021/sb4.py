def bktf(k):
    global solf
    for val in range(solf[k-1]+1, nrf+1):
        solf[k] = val
        if k == s//2:
            bktb(1)
        else:
            bktf(k+1)

def bktb(k):
    global solf
    global solb
    global sol
    for val in range(solb[k-1]+1, nrb+1):
        solb[k] = val
        if k == s//2:
            solb = [(x + nrf) for x in solb]
            sol = solf + solb
            if sol[1] == 1 and sol[s//2+2] == nrf+1:
                print(*sol[1:s//2+1] + sol[s//2+2:])
            solb = [(x - nrf) for x in solb]
        else:
            bktb(k+1)

nrf = int(input("nrf = "))
nrb = int(input("nrb = "))
s = int(input("s = "))

mins = min(nrf, nrb)
if mins * 2 < s:
    print("Imposibil")
else:
    solf = [0] * (s//2 + 1)
    solb = [0] * (s//2 + 1)
    sol = [0] * (s + 1)
    bktf(1)