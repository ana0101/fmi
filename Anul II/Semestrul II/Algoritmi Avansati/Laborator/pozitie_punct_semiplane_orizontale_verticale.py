INF = 1000000000

# cauta binar y maxim din arr ai y < x
def binary_search_min(arr, x):
    l, r = 0, len(arr) - 1
    while l <= r:
        m = (l + r) // 2
        if arr[m] < x and (m + 1 > len(arr) - 1 or arr[m + 1] >= x):
            return arr[m]
        elif arr[m] < x:
            l = m + 1
        else:
            r = m - 1
    return INF

# cauta binar y minim din arr ai y > x
def binary_search_max(arr, x):
    l, r = 0, len(arr) - 1
    while l <= r:
        m = (l + r) // 2
        if arr[m] > x and (m - 1 < 0 or arr[m - 1] <= x):
            return arr[m]
        elif arr[m] <= x:
            l = m + 1
        else:
            r = m - 1
    return -INF

n = int(input())
x_min, x_max, y_min, y_max = [], [], [], []

# tin minte pentru fiecare semiplan ce restrictie impune
# ori x_min, ori x_max, ori y_min, ori y_max

for _ in range(n):
    a, b, c = [int(x) for x in input().split()]
    if a == 0:
        if b > 0:
            y_max.append(-c / b)
        else:
            y_min.append(-c / b)
    elif b == 0:
        if a > 0:
            x_max.append(-c / a)
        else:
            x_min.append(-c / a)

# sortez listele
x_min.sort()
x_max.sort()
y_min.sort()
y_max.sort()

# print('x_min:', x_min)
# print('x_max:', x_max)
# print('y_min:', y_min)
# print('y_max:', y_max)

m = int(input())
for _ in range(m):
    x, y = [float(x) for x in input().split()]
    # caut binar sa vad daca punctul se afla in vreo interectie
    x_min_val = binary_search_min(x_min, x)
    # print('x_min_val:', x_min_val)
    if x_min_val == INF:
        print('NO')
        continue

    x_max_val = binary_search_max(x_max, x)
    # print('x_max_val:', x_max_val)
    if x_max_val == -INF:
        print('NO')
        continue

    y_min_val = binary_search_min(y_min, y)
    # print('y_min_val:', y_min_val)
    if y_min_val == INF:
        print('NO')
        continue

    y_max_val = binary_search_max(y_max, y)
    # print('y_max_val:', y_max_val)
    if y_max_val == -INF:
        print('NO')
        continue

    area = (x_max_val - x_min_val) * (y_max_val - y_min_val)
    print('YES')
    print('{:.6f}'.format(area))