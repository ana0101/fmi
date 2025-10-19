t = int(input())

for _ in range(t):
    xp, yp, xq, yq, xr, yr = [int(x) for x in input().split()]
    det = xq * yr + xp * yq + xr * yp - xq * yp - xr * yq - xp * yr
    if det == 0:
        print('TOUCH')
    elif det < 0:
        print('RIGHT')
    else:
        print('LEFT')