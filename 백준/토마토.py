from collections import deque
import sys
input = sys.stdin.readline
N, M = map(int, input().split())

graph = []
visited = []

for _ in range(M):
    graph.append(list(map(int, input().split())))
    visited.append([0] * N)
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
    


queue = deque()
for i in range(M):
    for j in range(N):
        if graph[i][j] == 1:
            visited[i][j] = 1
            queue.append((i, j))

def bfs():
    global queue
    while queue:
        x, y = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]

            if nx < 0 or nx > M - 1 or ny < 0 or ny > N - 1:
                continue

            if graph[nx][ny] == 0:
                graph[nx][ny] = 1
                visited[nx][ny] += visited[x][y] + 1
                queue.append((nx, ny))
            
            

bfs()
day = 0
for i in range(M):
    for j in range(N):
        if graph[i][j] == 0 and visited[i][j] == 0:
            print(-1)
            exit(0)
    day = max(day, max(visited[i]))
print(day - 1)