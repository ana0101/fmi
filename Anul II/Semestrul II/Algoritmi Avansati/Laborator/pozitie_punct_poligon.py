def orientation_test(x1, y1, x2, y2, x, y):
    det = x2 * y + x1 * y2 + x * y1 - x2 * y1 - x * y2 - x1 * y
    if det == 0:
        return 'TOUCH'
    elif det < 0:
        return 'RIGHT'
    else:
        return 'LEFT'
    
def generate_new_m(xm, ym):
    return xm + 11, ym + 17

def is_point_on_segment(orientation, x1, y1, x2, y2, x, y):
    if orientation != 'TOUCH':
        return False
    if not (min(x1, x2) <= x <= max(x1, x2) and min(y1, y2) <= y <= max(y1, y2)):
        return False
    if (x2 - x1) * (y - y1) != (x - x1) * (y2 - y1):
        return False
    return True

def compute_position(vertices, xp, yp, xm, ym):
    intersections = 0
    for i in range(len(vertices) - 1):
        x1, y1 = vertices[i]
        x2, y2 = vertices[i + 1]

        # verificam daca cumva punctul p este acelasi cu 1 sau 2
        if (xp, yp) == (x1, y1) or (xp, yp) == (x2, y2):
            return 'BOUNDARY'

        ok = False
        while not ok:
            ok = True
            orientation_p = orientation_test(x1, y1, x2, y2, xp, yp)
            orientation_m = orientation_test(x1, y1, x2, y2, xm, ym)
            orientation_1 = orientation_test(xp, yp, xm, ym, x1, y1)
            orientation_2 = orientation_test(xp, yp, xm, ym, x2, y2)

            # verificam daca punctul p este pe segmentul (1, 2)
            if is_point_on_segment(orientation_p, x1, y1, x2, y2, xp, yp):
                return 'BOUNDARY'
            # verificam daca segmentul (p, m) trece prin punctul 1 sau 2
            # daca da atunci trebuie sa schimbam m-ul
            elif is_point_on_segment(orientation_1, xm, ym, xp, yp, x1, y1):
                xm, ym = generate_new_m(xm, ym)
                ok = False
            elif is_point_on_segment(orientation_2, xm, ym, xp, yp, x2, y2):
                xm, ym = generate_new_m(xm, ym)
                ok = False
            # (p, m) si (1, 2) se intersecteaza daca p si m sunt pe parti diferite fata de (1, 2)
            # si 1 si 2 sunt pe parti diferite fata de (p, m)
            elif orientation_p != orientation_m and orientation_1 != orientation_2:
                intersections += 1

    if intersections % 2 == 0:
        return 'OUTSIDE'
    return 'INSIDE'


n = int(input())
vertices = []

# m este punctul "departe" de poligon (in dreapta sus)
xm, ym = 0, 0

for _ in range(n):
    x, y = [int(x) for x in input().split()]
    vertices.append((x, y))
    if x > xm:
        xm = x + 3
    if y > ym:
        ym = y + 5

# adaugam primul punct la final pentru usurinta
vertices.append(vertices[0])

m = int(input())
for _ in range(m):
    x, y = [int(x) for x in input().split()]
    print(compute_position(vertices, x, y, xm, ym))