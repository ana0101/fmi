left_turns, right_turns, forward = 0, 0, 0

n = int(input())
x1, y1 = [int(x) for x in input().split()]
x2, y2 = [int(x) for x in input().split()]
x3, y3 = 0, 0
x0, y0 = x1, y1

for _ in range(n - 2):
    x3, y3 = [int(x) for x in input().split()]
    det = x2 * y3 + x1 * y2 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3
    if det == 0:
        forward += 1
    elif det < 0:
        right_turns += 1
    else:
        left_turns += 1

    x1, y1 = x2, y2
    x2, y2 = x3, y3

x3, y3 = x0, y0
det = x2 * y3 + x1 * y2 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3
if det == 0:
    forward += 1
elif det < 0:
    right_turns += 1
else:
    left_turns += 1

print(left_turns, right_turns, forward)