from collections import deque

N, M = map(int, input().split())

graph = []

for _ in range(N):
    graph.append(list(map(int,input().split())))

index = []

queue = []
for i in range(N):
    for j in range(M):
        if graph[i][j] == 2:
            queue.append((i, j))
        if graph[i][j] == 0:
            index.append((i,j))

r_queue = deque()
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
def bfs(x,y):
    r_queue.append((x,y))
    while r_queue:
        x,y = r_queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
        
            if nx < 0 or nx > N - 1 or ny < 0 or ny > M - 1 or graph[nx][ny] == 1:
                continue
            if graph[nx][ny] == 0:
                graph[nx][ny] = 2
                r_queue.append((nx, ny))


def count():
    c = 0
    for i in range(N):
        for j in range(M):
            if graph[i][j] == 0:
                c += 1
            if (i,j) not in queue and graph[i][j] == 2:
                graph[i][j] = 0
    return c


answer = 0


path = []
p_list = []
def dfs(depth, start):
    if depth == 3:
        p = []
        for x,y in path:
            p.append((x,y))
        p_list.append(p)
        return
    
    for i in range(start, len(index)):
        path.append(index[i])
        dfs(depth + 1, i + 1)
        path.pop()
dfs(0, 0)

for p in p_list:
    for x,y in p:
        graph[x][y] = 1
    for x,y in queue:
        bfs(x,y)
    answer = max(answer, count())
    for x,y in p:
        graph[x][y] = 0

print(answer)


                        
        