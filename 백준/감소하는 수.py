numbers = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]

path = []

down_list = []

def dfs(depth, start, max_depth):
    global down_list, count
    if depth == max_depth:
        down_list = ["".join(map(str, path))] + down_list 
        return

    for i in range(start, 10):
        path.append(numbers[i])
        dfs(depth + 1, i + 1, max_depth)
        path.pop()
i = 1
real_down_list = []
while i < 11:
    dfs(0, 0, i)
    real_down_list += down_list
    down_list = []
    i += 1

N = int(input())
if len(real_down_list) <= N:
    print(-1)
else:
    print(real_down_list[N])