import math
import heapq
import sys

input = sys.stdin.readline

INF = math.inf

V, E = map(int, input().split())
K = int(input())

graph = [[] for _ in range(V + 1)]

for i in range(E):
    u, v, w = map(int, input().split())
    graph[u].append((v, w))

dist = [INF] * (V + 1)

def dijkstra(start):
    heap = []
    d, node = start
    dist[node] = d
    heapq.heappush(heap, (d, node))

    while heap:
        d, node = heapq.heappop(heap)

        if dist[node] < d: continue

        for nod, dis in graph[node]:
            if dist[nod] > dist[node] + dis:
                dist[nod] = dist[node] + dis
                heapq.heappush(heap, (dist[nod], nod))


dijkstra((0, K))

for i in range(1, len(dist)):
    e = dist[i]
    if e == INF:
        print("INF")
    else:
        print(e)
            


