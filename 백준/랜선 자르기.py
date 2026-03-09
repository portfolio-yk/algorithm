K, N = map(int, input().split())

LANs = []

max_num = 0

for _ in range(K):
    inp = int(input())
    if max_num < inp:
        max_num = inp
    LANs.append(inp)


left = 1
right = max_num

result = 0

while left <= right:
    mid = (left + right) // 2

    count = 0
    for LAN in LANs:
        count += LAN // mid


    if count >= N:
        result = mid
        left = mid + 1
    else:
        right = mid - 1


print(result)