def left_turn(frontier):
    x1, y1 = frontier[-3]
    x2, y2 = frontier[-2]
    x3, y3 = frontier[-1]
    return x2 * y3 + x1 * y2 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3 > 0

n = int(input())
points = []
for _ in range(n):
    x, y = [int(x) for x in input().split()]
    points.append((x, y))

# gasim punctul cu x minim (cel mai din stanga)
x_min = points[0][0]
index_min = 0
for i in range(1, n):
    if points[i][0] < x_min:
        x_min = points[i][0]
        index_min = i

# rearanjam punctele astfel incat punctul cu x minim sa fie primul
points = points[index_min:] + points[:index_min]

x1, y1 = points[0]
frontier = [(x1, y1)]

if n > 1:
    x2, y2 = points[1]
    frontier.append((x2, y2))

    for i in range(2, n):
        x3, y3 = points[i]
        frontier.append((x3, y3))
        # cat timp frontiera are mai mult de 2 puncte si ultimele 3 puncte nu formeaza un viraj la stanga
        # stergem penultimul punct din frontiera
        while len(frontier) > 2 and not left_turn(frontier):
            frontier.pop(-2)

    # punem primul punct din frontiera la final
    frontier.append(frontier[0])
    while len(frontier) > 2 and not left_turn(frontier):
        frontier.pop(-2)

    # stergem primul punct din frontiera de pe ultima pozitie
    frontier.pop(-1)

print(len(frontier))
for x, y in frontier:
    print(x, y)