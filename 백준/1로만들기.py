import math
N = int(input())

dp = [0] * (N+3)
dp[1] = 0
dp[2] = 1
dp[3] = 1

for i in range(4, N+1):
    c = []
    if i % 3 == 0:
        c.append(i // 3)
    if i % 2 == 0:
        c.append(i // 2)
    
    c.append(i - 1)

    min = math.inf 
    for j in c:
        if min > dp[j]:
            min = dp[j]
    
    dp[i] = min + 1

    c =[]

print(dp[N])
        
    
