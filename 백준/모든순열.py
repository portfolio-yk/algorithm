N = int(input())
numbers = []

for i in range(N):
    numbers.append(i + 1)

visited = [False] * N
path = []

def dfs(depth):
    if depth == N:
        print(*path)
        return
    
    for i in range(N):
        if visited[i] == False:
            path.append(numbers[i])
            visited[i] = True
            dfs(depth + 1)
            path.pop()
            visited[i] = False
dfs(0)

    
