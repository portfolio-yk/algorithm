T = int(input())
output = '#{} {}'
for tc in range(1, T + 1):
    N, P = map(int, input().split())
    studied_days = list(map(int, input().split()))
    result = -1
    start = 0
    for end in range(N):
        while (studied_days[end] - studied_days[start] + 1) - (end - start + 1) > P:
            start += 1
        result = max(result, end - start + 1 + P)
 
    print(output.format(tc, result))