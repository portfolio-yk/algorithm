N = int(input())
arr = list(map(int, input().split()))

M = int(input())
arr_cmp = list(map(int, input().split()))

arr.sort()

for i in arr_cmp:
    left = 0
    right = len(arr) - 1
    flag=False
    while right >= left:
        mid = (right + left) // 2
        if arr[mid] == i:
            flag=True
            print(1)
            break

        if arr[mid] < i:
            left = mid + 1
        else:
            right = mid - 1

    if flag == False:
        print(0)