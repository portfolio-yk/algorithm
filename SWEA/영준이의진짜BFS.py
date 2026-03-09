from collections import deque
import sys

sys.setrecursionlimit(10**5)

T = int(input())

for t in range(T):
    N = int(input())
    arr = list(map(int, input().split()))
    graph = [[] for _ in range(N + 1)]

    #그래프 세팅
    for i in range(len(arr)):
        graph[arr[i]].append(i + 2)
        graph[i + 2].append(arr[i])

    #공통조상 찾기
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

    #깊이 설정
    def dfs(start, d):
        stack = [(start, d)]
        visted[start] = True
        depth[start] = d

        while stack:
            curr, dep = stack.pop()
            for next in graph[curr]:
                if visted[next]:
                    continue
                visted[next] = True
                parent[next] = curr
                depth[next] = dep + 1
                stack.append((next, dep + 1))


    parent = [0] * (N + 1)
    depth = [0] * (N + 1)
    visted = [0] * (N + 1)
    dfs(1, 0)

    #탐색 경로 찾기
    path = []
    visted = [0] * (N + 1)
    def bfs(start):
        queue = deque()
        nodes = graph[start]
        path.append(start)
        visted[start] = True

        for node in nodes:
            queue.append(node)
        
        while queue:
            node = queue.popleft()
            visted[node] = True
            path.append(node)

            for n in graph[node]:
                if visted[n] == False:
                    queue.append(n)
    bfs(1)


    #공통조상 활용해 노드간 거리 구하기
    def get_distance(node_1, node_2):
        h_1 = depth[node_1]
        h_2 = depth[node_2]

        h_c = depth[lca(node_1, node_2)]

        return h_1 + h_2 - h_c * 2
    distance = 0
    for i in range(len(path) - 1):
        distance += get_distance(path[i], path[i + 1])


    print(f"#{t + 1} {distance}")