import sys
N = int(sys.stdin.readline())

arr = [0] * (N + 1)

def fibo(N):
    arr[1] = 1
    arr[2] = 1
    for i in range(3, N):
        arr[i] = arr[i - 1] + arr[i - 2]

fibo(N+1)
print(arr[N], N - 2)