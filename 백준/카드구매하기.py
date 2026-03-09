N = int(input())
cards = list(map(int, input().split()))

dp = [0] * N

dp[0] = cards[0]

for i in range(1, N):
    m = cards[i]
    n = 0
    if i % 2:
        n = 1
    for j in range(i // 2 + n):
        if m < dp[i - j - 1] + dp[j]:
            m = dp[i - j - 1] + dp[j]
        dp[i] = m

print(dp[N-1])