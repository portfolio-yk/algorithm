N, re_sum = map(int, input().split())
numbers = list(map(int, input().split()))

path = []
answer = 0

def dfs(depth, start, max_depth):
    global answer
    if depth == max_depth:
        if re_sum == sum(path):
            answer += 1
        return
    
    for i in range(start, N):
        path.append(numbers[i])
        dfs(depth + 1, i + 1, max_depth)
        path.pop()

for i in range(N):
    dfs(0, 0, i + 1)
print(answer)