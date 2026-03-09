N = int(input())

if N == 1:
    print(10)
    exit(0)

dp = [[1] * 10 for _ in range(N)]

for i in range(N - 1):
    for j in range(9):
        dp[i + 1][j + 1] = dp[i][j + 1] + dp[i + 1][j]

print(sum(dp[N - 1]) % 10007)