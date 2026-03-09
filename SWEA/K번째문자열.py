T = int(input())

for t in range(T):
    N = int(input())
    s = input()

    path = []
    arr = []

    for i in range(len(s)):
        for j in range(i, len(s)):
            path.append(s[j])
            arr.append("".join([a for a in path]))
        path = []


    s_arr = list(set(arr))
    s_arr.sort()
    if N >= len(s_arr):
        print("none")
    else:
        print(f"#{t+1}", s_arr[N - 1])
