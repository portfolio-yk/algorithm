result = 0

arr = []

def hanoi(count, FROM, TMP, TO):
    global result
    if count == 1:
        result += 1
        arr.append([FROM, TO])
        return
    hanoi(count - 1, FROM, TO, TMP)
    result += 1
    arr.append([FROM, TO])
    hanoi(count - 1, TMP, FROM, TO)

N = int(input())
hanoi(N, 1, 2, 3)
print(result)
for i,j in arr:
    print(i, j)
