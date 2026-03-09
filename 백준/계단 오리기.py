N = int(input())
s = []

for i in range(N):
    s.append(int(input()))

dp = [0] * N

if len(s) > 0:
    dp[0] = s[0]
if len(s) > 1:
    dp[1] = s[0] + s[1]

for i in range(2, N):
    dp[i] = max(dp[i - 3] + s[i - 1] + s[i], dp[i -2] + s[i])

print(dp[N - 1]) 