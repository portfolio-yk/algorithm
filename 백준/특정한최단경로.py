import math
import heapq
import sys
input = sys.stdin.readline

INF = math.inf

N, E = map(int, input().split())

graph = [[] for _ in range(N + 1)]
distance = [INF] * (N + 1)

for _ in range(E):
    u, v, w = map(int, input().split())
    graph[u].append((v, w))
    graph[v].append((u, w))

node_1, node_2 = map(int, input().split())

def dijkstra(start):
    q = []
    heapq.heappush(q, (0, start))
    distance[start] = 0

    while q:
        dist, now = heapq.heappop(q)

        if distance[now] < dist:
            continue
        for i in graph[now]:
            cost = dist + i[1]
            if cost < distance[i[0]]:
                distance[i[0]] = cost
                heapq.heappush(q, (cost, i[0]))


paths = list(set([1, node_1, node_2, N]))
paths.sort()

total_distance = []
for p in paths:
    dijkstra(p)
    total_distance.append(distance)
    distance = [INF] * (N + 1)

ans = INF

if len(paths) == 2:
    ans = total_distance[0][N]
elif len(paths) == 3:
    ans = total_distance[0][paths[1]] + total_distance[1][N]
else:
    path_1 = total_distance[0][paths[1]] + total_distance[1][paths[2]] + total_distance[2][N]
    path_2 = total_distance[0][paths[2]] + total_distance[2][paths[1]] + total_distance[1][N]
    ans = min(path_1, path_2)

if ans == INF:
    print(-1)
else:
    print(ans)