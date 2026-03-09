N = int(input())
sites = []

for _ in range(N):
    sites.append(list(map(int,input().split())))

def fac(num):
    if num < 2:
        return 1
    return num * fac(num - 1)

for [l, r] in sites:
    print(int(fac(r)  / (fac(r - l) * fac(l))))
