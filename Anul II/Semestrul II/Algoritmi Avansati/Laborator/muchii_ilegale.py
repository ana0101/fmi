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
xd, yd = [int(x) for x in input().split()]

det_d = calc_det(xa, ya, xb, yb, xc, yc, xd, yd)
if det_d <= 0:
    print('AC: LEGAL')
else:
    print('AC: ILLEGAL')

det_a = calc_det(xb, yb, xc, yc, xd, yd, xa, ya)
if det_a <= 0:
    print('BD: LEGAL')
else:
    print('BD: ILLEGAL')