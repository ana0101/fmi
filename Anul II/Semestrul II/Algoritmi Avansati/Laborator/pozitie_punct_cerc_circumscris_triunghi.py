def calc_det(xa, ya, xb, yb, xc, yc, xd, yd):
    xa = xa - xd
    ya = ya - yd
    xb = xb - xd
    yb = yb - yd
    xc = xc - xd
    yc = yc - yd
    return (xa * yb * (xc**2 + yc**2)) + (ya * xc * (xb**2 + yb**2)) + (xb * yc * (xa**2 + ya**2)) - (xc * yb * (xa**2 + ya**2)) - (ya * xb * (xc**2 + yc**2)) - (xa * yc * (xb**2 + yb**2))

xa, ya = [int(x) for x in input().split()]
xb, yb = [int(x) for x in input().split()]
xc, yc = [int(x) for x in input().split()]

m = int(input())

for _ in range(m):
    xd, yd = [int(x) for x in input().split()]
    det = calc_det(xa, ya, xb, yb, xc, yc, xd, yd)
    if det == 0:
        print('BOUNDARY')
    elif det > 0:
        print('INSIDE')
    else:
        print('OUTSIDE')