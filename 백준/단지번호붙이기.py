N = int(input())

graph = []

for _ in range(N):
    graph.append(list(map(int, input())))

visited = []
for _ in range(N):
    visited.append([0] * N) 
count = 0

def dfs(x, y):
    global count, visited
    
    if x < 0 or x > N - 1 or y < 0 or y > N - 1:
        return

    if graph[x][y] == 0:
        return
    
    if visited[x][y] == 1:
        return
    
    
    count += 1
    visited[x][y] = 1
    

    dfs(x + 1, y)
    dfs(x, y + 1)
    dfs(x - 1, y)
    dfs(x, y - 1)


count_list = []


for i in range(N):
    for j in range(N):
        dfs(i, j)
        if count > 0:
            count_list.append(count)
            count = 0
count_list.sort()
print(len(count_list))
for c in count_list:
    print(c)