INF = 1000000000

n = int(input())
x_min, y_min = -INF, -INF
x_max, y_max = INF, INF

for _ in range(n):
    a, b, c = [int(x) for x in input().split()]
    # calculam noile valori minime si maxime pentru x si y
    # ax + by + c <= 0
    # semiplan orizontal => a = 0 => by + c <= 0 => 
    #     => 1) b > 0 => y_max = min(y_max, -c / b)
    #     => 2) b < 0 => y_min = max(y_min, -c / b)
    # semiplan vertical => b = 0 => ax + c <= 0 =>
    #     => 1) a > 0 => x_max = min(x_max, -c / a)
    #     => 2) a < 0 => x_min = max(x_min, -c / a)

    if a == 0:
        if b > 0:
            y_max = min(y_max, -c / b)
        else:
            y_min = max(y_min, -c / b)
    elif b == 0:
        if a > 0:
            x_max = min(x_max, -c / a)
        else:
            x_min = max(x_min, -c / a)

# verificam daca intersectia e vida
if x_min > x_max or y_min > y_max:
    print('VOID')
# verificam daca intersectia este marginita (adica exista toate cele 4)
elif x_min != -INF and x_max != INF and y_min != -INF and y_max != INF:
    print('BOUNDED')
else:
    print('UNBOUNDED')