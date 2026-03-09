import sys
sys.setrecursionlimit(10**5)

n = int(input())

def dfs(now, d):
    visited[now] = True
    depth[now] = d

    for next in graph[now]:
        if visited[next]:
            continue
        parent[next] = now
        dfs(next, d + 1)

def lca(node_1, node_2):
    while depth[node_1] != depth[node_2]:
        if depth[node_1] > depth[node_2]:
            node_1 = parent[node_1]
        else:
            node_2 = parent[node_2]

    while node_1 != node_2:
        node_1 = parent[node_1]
        node_2 = parent[node_2]
    
    return node_1


arr = []
maxN = 0
for _ in range(n-1):
    x, y = map(int, input().split())
    arr.append([x, y])
    maxN = max(maxN, max([x, y]))

graph = [[] for _ in range(maxN + 1)]
for x, y in arr:
    graph[x].append(y)
    graph[y].append(x)

parent = [0] * (maxN + 1)

depth = [0] * (maxN + 1)
visited = [0] * (maxN + 1)

dfs(1, 0)


M = int(input())

for _ in range(M):
    x, y = map(int, input().split())
    print(lca(x, y))
