print_list = []
while True:
    c_list = []
    i = input().split()
    C = i[0]
    if C == '0':
        break
    c_list = i[1:]

    print_list.append(c_list)


def dfs(start, path, n, data):
    if len(path) == n:
        print(" ".join(path))
        return

    for i in range(start, len(data)):
        path.append(data[i])
        dfs(i + 1, path, n, data)
        path.pop()

for p in print_list:
    dfs(0, [], 6, p)
    print()