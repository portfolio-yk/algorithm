from collections import deque

N, M, V = map(int, input().split())

graph = {}

for _ in range(M):
    l, r = map(int, input().split())
    if l not in graph:
        graph[l] = [r]
    else:
        graph[l].append(r)
    
    if r not in graph:
        graph[r] = [l]
    else:
        graph[r].append(l)

for i in graph.keys():
    graph[i].sort()



visited = [0] * N
path = []
def dfs(v):
    if v not in graph:
        return
    
    for i in graph[v]:
        if (visited[i - 1] == 0):
            path.append(i)
            visited[i - 1] = 1
            dfs(i)

path.append(V)
visited[V - 1] = 1
dfs(V)
print(*path)


visited = [0] * N
path = []
def bfs():
    queue = deque()
    queue.append(V)

    while queue:
        v = queue.popleft()
        if visited[v - 1] == 0:
            path.append(v)
            visited[v - 1] = 1
            if v in graph:
                for i in graph[v]:
                    queue.append(i)
bfs()
print(*path)
