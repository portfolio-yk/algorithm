import math

N = int(input())

dp = [[0] * N for _ in range(N)]
input_arr = []


for i in range(N):
    v = list(map(int, input().split()))
    input_arr.append(v)
    if i >= 1:
        dp[i] = [math.inf] * 3

dp[0] = input_arr[0]

for i in range(N - 1):
    for j in range(3):
        for k in range(3):
            if k != j:
                m = input_arr[i+1][k] + input_arr[i][j] 
                if dp[i+1][k] > m:
                    dp[i+1][k] = m
    input_arr[i+1] = dp[i+1]

print(min(dp[len(dp)-1]))
        