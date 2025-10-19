def det(p, q, r):
    return q[0] * r[1] + p[0] * q[1] + r[0] * p[1] - q[0] * p[1] - r[0] * q[1] - p[0] * r[1]

def binary_search(p):
    # cautam binar punctul i astfel incat p sa fie la stanga dreptei p0 -> pi si i sa fie maxim
    left, right = 1, n - 1
    while left < right:
        mid = (left + right) // 2
        # daca p este la stanga dreptei p0 -> vertices[mid] si la dreapta dreptei p0 -> vertices[mid + 1]
        if det(p0, vertices[mid], p) >= 0 and det(p0, vertices[mid + 1], p) < 0:
            return mid
        elif det(p0, vertices[mid], p) >= 0:
            left = mid + 1
        else:
            right = mid - 1
    return left

n = int(input())
vertices = []
for _ in range(n):
    x, y = [int(x) for x in input().split()]
    vertices.append((x, y)) 

# gasim punctul cu x minim, y minim (cel mai din stanga, apoi cel mai de jos)
x_min = vertices[0][0]
y_min = vertices[0][1]
index_min = 0
for i in range(1, n):
    if vertices[i][0] < x_min or (vertices[i][0] == x_min and vertices[i][1] < y_min):
        x_min = vertices[i][0]
        y_min = vertices[i][1]
        index_min = i

# rearanjam punctele astfel incat punctul cu x minim sa fie primul
vertices = vertices[index_min:] + vertices[:index_min]

p0 = vertices[0]
p1 = vertices[1]
pn = vertices[n - 1]

m = int(input())
for _ in range(m):
    p = [int(x) for x in input().split()]

    # verificam daca p se afla in interiorul dreptelor po -> p1 si p0 -> pn
    if det(p0, p1, p) < 0 or det(p0, pn, p) > 0:
        print('OUTSIDE')
        continue

    index = binary_search(p)

    # cazuri speciale
    # daca index e n - 1
    if index == n - 1:
        if det(vertices[0], vertices[n - 1], p) == 0 and det(vertices[n - 2], vertices[n - 1], p) >= 0 and det(vertices[0], vertices[1], p) >= 0:
            print('BOUNDARY')
        else:
            print('OUTSIDE')
        continue

    # daca index e 1
    if index == 1:
        if det(vertices[0], vertices[1], p) == 0 and det(vertices[1], vertices[2], p) >= 0:
            print('BOUNDARY')
            continue

    # verificam daca p se afla in interiorul triunghiului p0, vertices[index], vertices[index + 1]
    # adica daca p e la stanga dreptei p[index] -> p[index + 1]
    if det(vertices[index], vertices[index + 1], p) > 0:
        print('INSIDE')
    elif det(vertices[index], vertices[index + 1], p) == 0:
        print('BOUNDARY')
    else:
        print('OUTSIDE')