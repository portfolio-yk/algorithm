import math

INF = math.inf

N, M, R = map(int, input().split())

item_count_list = [0] + list(map(int, input().split()))

graph = [[INF] * (N + 1) for _ in range(N + 1)]

for i in range(1, N + 1):
    graph[i][i] = 0

for i in range(R):
    u, v, w = map(int, input().split())
    graph[u][v] = w
    graph[v][u] = w


def floid():
    for k in range(1, N + 1):
        for i in range(1, N + 1):
            for j in range(1, N + 1):
                if graph[i][j] > graph[i][k] + graph[k][j]:
                    graph[i][j] = graph[i][k] + graph[k][j]


floid()

max_item_count = 0

for i in range(1, N + 1):
    count = 0

    for j in range(len(graph[i])):
        d = graph[i][j]
        if d <= M:
            count += item_count_list[j]

    max_item_count = max(max_item_count, count)

print(max_item_count)