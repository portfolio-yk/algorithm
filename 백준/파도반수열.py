N = int(input())

inputList = []
for i in range(N):
    inputList.append(int(input()))


dp = [0] * 101
dp[1] = 1
dp[2] = 1
dp[3] = 1
dp[4] = 2
dp[5] = 2


def P(N):
    if N >= 6:
        for i in range(6, N + 1):
            dp[i] = dp[i - 5] + dp[i - 1]


for i in inputList:
    P(i)
    print(dp[i])