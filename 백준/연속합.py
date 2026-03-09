import sys

N = int(sys.stdin.readline())
input_list = list(map(int, sys.stdin.readline().split()))

dp = input_list

for i in range(1, N):
    v = dp[i] + dp[i - 1]
    if v > dp[i]:
        dp[i] = v

print(max(dp))