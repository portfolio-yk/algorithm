from collections import defaultdict

N = int(input())
arr = list(map(int, input().split()))

M = int(input())
arr_cmp = list(map(int, input().split()))



arr_count = defaultdict(int)

for e in arr:
    arr_count[e] += 1

s_arr = list(set(arr))

s_arr.sort()

for i in arr_cmp:
    left = 0
    right = len(s_arr) - 1
    count = 0
    flag = False
    while right >= left:
        mid = (right + left) // 2
        if s_arr[mid] == i:
            flag = True
            print(arr_count[i], end=" ")
            break

        if s_arr[mid] < i:
            left = mid + 1
        else:
            right = mid - 1
    
    if flag == False:
        print(0, end=" ")
 