N = int(input())
grape_list = []
for i in range(N):
    grape_list.append(int(input()))


dp = [-1] * N

dp[0] = grape_list[0]
if N > 1:
    dp[1] = grape_list[0] + grape_list[1]
if N > 2:
    dp[2] = max(dp[1], grape_list[1] + grape_list[2], grape_list[0]  + grape_list[2])

for i in range(3, N):
    v1 = dp[i - 3] + grape_list[i - 1] + grape_list[i]
    v2 = dp[i - 2] + grape_list[i]
    v3 = max(dp[i-1], v1, v2)
    dp[i] = v3

print(max(dp[len(dp)-1],dp[len(dp)-2]))