def x_monotone():
    # parcurgem punctele de la cel mai din stanga la cel mai din dreapta
    # x-ul trebuie tot timpul sa creasca
    for i in range(index_right):
        if vertices[i][0] > vertices[i + 1][0]:
            return False

    # parcurgem punctele de la cel mai din dreapta la cel mai din stanga
    # x-ul trebuie tot timpul sa scada
    for i in range(index_right, n):
        if vertices[i][0] < vertices[i + 1][0]:
            return False
        
    return True

def y_monotone():
    # parcurgem punctele de la cel mai de sus la cel mai de jos
    # y-ul trebuie tot timpul sa scada
    for i in range(index_bottom):
        if vertices[i][1] < vertices[i + 1][1]:
            return False

    # parcurgem punctele de la cel mai de jos la cel mai de sus
    # y-ul trebuie tot timpul sa creasca
    for i in range(index_bottom, n):
        if vertices[i][1] > vertices[i + 1][1]:
            return False

    return True

n = int(input())
vertices = []
for _ in range(n):
    x, y = [int(x) for x in input().split()]
    vertices.append((x, y))

# gasim punctul cel mai din stanga
x_min = vertices[0][0]
index_left = 0
for i in range(1, n):
    if vertices[i][0] < x_min:
        x_min = vertices[i][0]
        index_left = i

# rearanjam punctele astfel incat punctul cel mai din stanga sa fie primul
vertices = vertices[index_left:] + vertices[:index_left]

# adaugam primul punct la final
vertices.append(vertices[0])

# gasim punctul cel mai din dreapta
x_max = vertices[0][0]
index_right = 0
for i in range(1, n):
    if vertices[i][0] > x_max:
        x_max = vertices[i][0]
        index_right = i

if x_monotone():
    print('YES')
else:
    print('NO')

# scoatem punctul adaugat la final
vertices.pop()


# gasim punctul cel mai de sus
y_max = vertices[0][1]
index_top = 0
for i in range(1, n):
    if vertices[i][1] > y_max:
        y_max = vertices[i][1]
        index_top = i

# rearanjam punctele astfel incat punctul cel mai de sus sa fie primul
vertices = vertices[index_top:] + vertices[:index_top]

# adaugam primul punct la final
vertices.append(vertices[0])

# gasim punctul cel mai de jos
y_min = vertices[0][1]
index_bottom = 0
for i in range(1, n):
    if vertices[i][1] < y_min:
        y_min = vertices[i][1]
        index_bottom = i

if y_monotone():
    print('YES')
else:
    print('NO')