H, W = map(int, input().split())

Hs = list(map(int, input().split()))

sum_count = 0
for i in range(H):
    h = H - i
    count = 0
    start = 0
    for j in range(W):
        if Hs[j] == h and start == 0:
            start = 1
            Hs[j] -= 1
        elif Hs[j] == h and start == 1:
            sum_count += count
            count = 0
            Hs[j] -= 1
        else:
            if start == 1:
                count += 1

print(sum_count)


