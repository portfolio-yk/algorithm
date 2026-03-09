N, size = map(int, input().split())

res = [-1] * N
visited = [False] * N

def dfs(N, size, depth):
    if depth == size:
        print(" ".join(map(str, (n for n in res if n > 0))))
        return
    
    for i in range(N):
        if visited[i] == False:
            visited[i] = True
            res[depth] = i + 1
            dfs(N, size, depth + 1)
            visited[i] = False

dfs(N, size, 0)
