N = int(input())
M = int(input())

graph = {}

for _ in range(M):
    node_1, node_2 = map(int, input().split())
    if node_1 in graph:
        graph[node_1].append(node_2)
    else:
        graph[node_1] = [node_2] 

    if node_2 in graph:
        graph[node_2].append(node_1)
    else:
        graph[node_2] = [node_1] 

visited = [0] * N
visited[0] = 0

def dfs(node):
    global visited, virus_count

    visited[node - 1] = 1

    if node not in graph:
        return

    nodes = graph[node]
    for node_c in nodes:
        if visited[node_c - 1] < 1:
            dfs(node_c)
    
    
dfs(1)
print(sum(visited) - 1)