import sys

input = sys.stdin.readline

N, M = map(int, input().split())

trees = list(map(int, input().split()))

max_tree = max(trees)


left = 0
right = max_tree
ans = 0 

while right >= left:
    count = 0
    mid = (right + left) // 2

    for tree in trees:
        if tree - mid > 0:
            count += tree - mid

    if count == M:
        ans = mid
        break

    if count > M:
        ans = mid
        left = mid + 1
    else:
        right = mid - 1

print(ans)