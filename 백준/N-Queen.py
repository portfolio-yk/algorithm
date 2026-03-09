import sys

N = int(sys.stdin.readline())

count = 0
col_used = [False] * N
diag1 = [False] * (2 * N - 1)  # row + col
diag2 = [False] * (2 * N - 1)  # row - col + (N-1)

def dfs(row):
    global count

    if row == N:
        count += 1
        return

    for col in range(N):
        if not col_used[col] and not diag1[row + col] and not diag2[row - col + (N-1)]:
            # 퀸 배치
            col_used[col] = diag1[row + col] = diag2[row - col + (N-1)] = True
            dfs(row + 1)
            # 백트래킹 (원래 상태로 되돌림)
            col_used[col] = diag1[row + col] = diag2[row - col + (N-1)] = False

dfs(0)
print(count)


### 대각선 판단
## y=x r+c가 같다
## y=-x r-c가 같다