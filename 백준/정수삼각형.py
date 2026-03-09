N = int(input())
int_arr = [[0] * N for _ in range(N)]

for i in range(N):
    l = list(map(int, input().split()))
    for j in range(len(l)):
        int_arr[i][j] = l[j]


dp = [[-1] * N for _ in range(N)]

dp[0] = int_arr[0]

for i in range(N - 1):
    for j in range(N-1):
        v1 = int_arr[i][j] + int_arr[i+1][j]
        v2 = int_arr[i][j] + int_arr[i+1][j + 1]

        if dp[i+1][j] < v1:
            dp[i+1][j] = v1
        if dp[i+1][j+1] < v2:
            dp[i+1][j+1] = v2
    int_arr[i+1] = dp[i+1]

print(max(dp[len(dp)-1]))