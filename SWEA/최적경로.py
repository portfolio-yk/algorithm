T = int(input())

for tc in range(1, T + 1):
    N = int(input())

    li = list(map(int,input().split()))

    i = 0
    office = []
    home = []
    path = []
    path_index = [i for i in range(N + 1)]
    while i < len(li):
        if i == 0:
            office = [li[i], li[i + 1]]
            path.append(office)
        elif i == 2:
            home = [li[i], li[i + 1]]
        else:
            path.append([li[i], li[i + 1]])
        i += 2


    def dis(coord1, coord2):
        x1, y1 = coord1
        x2, y2 = coord2
        return abs(x1 - x2) + abs(y1 - y2)

    def get_distance(path_index):
        distance = 0
        distance += dis(office, path[path_index[0]])
        for i in range(len(path_index) - 1):
            distance += dis(path[path_index[i]], path[path_index[i + 1]])
        distance += dis(home, path[path_index[N - 1]])
        return distance


    dfs_path = [0]
    visited = [0] * (N + 1)

    min_distance = 1000000
    def dfs(sum, prev):
        global min_distance

        if sum > min_distance: return
        
        if len(dfs_path) == N + 1:
            min_distance = min(min_distance, sum + dis(home, prev)) 
            return 
        
        for i in range(1, N + 1):
            if visited[i] == 0:
                dfs_path.append(i)
                visited[i] = 1
                dfs(sum + dis(prev, path[i]), path[i])
                dfs_path.pop()
                visited[i] = 0
    dfs(0, path[0])
    print(f"#{tc} {min_distance}")