N, M = map(int, input().split())

table = []

sum_table = []

for _ in range(N):
    r = list(map(int, input().split()))
    table.append(r)
    sum_table.append(r)

xy_list = []

for _ in range(M):
    xy_list.append(list(map(int, input().split())))

for i in range(N):
    for j in range(N):
        if j - 1 >= 0:
            sum_table[i][j] += sum_table[i][j - 1]
        if i - 1 >= 0:
            sum_table[i][j] += sum_table[i - 1][j]
        if j - 1 >= 0 and i - 1 >= 0:
            sum_table[i][j] -= sum_table[i - 1][j -1]


for [x1, y1, x2, y2] in xy_list:
    x1 = x1 - 1
    y1 = y1 - 1
    x2 = x2 - 1
    y2 = y2 - 1
    answer = sum_table[x2][y2]
    if x1 - 1 >= 0:
        answer -= sum_table[x1 - 1][y2]
    if y1 - 1 >= 0:
        answer -= sum_table[x2][y1 - 1]
    if x1 - 1 >= 0 and y1 - 1 >= 0:
        answer += sum_table[x1 - 1][y1 - 1]
    print(answer)
