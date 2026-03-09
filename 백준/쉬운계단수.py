N = int(input())

dp = [1, 3, 3, 4, 4, 4, 4, 4, 3, 2]
MOD = 1000000000
tmp = [0] * 10
for i in range(4, N+1):
    for j in range(10):
        if j == 0:
            tmp[j] = dp[j+1]
        elif j == 9:
            tmp[j] = dp[j-1]
        else:
            tmp[j] = dp[j+1] + dp[j-1]
    dp = tmp
    tmp = [0] * 10
if N == 1:
    print(9)
elif N == 2:
    print(17)
else:
    print(sum(dp) % MOD)
