import itertools
from collections import deque

N, M = map(int, input().split()) 
graph = []
for i in range(N):
    graph.append(list(map(int, input().split())))


chickens = []
homes = []
for i in range(N):
    for j in range(N):
        if graph[i][j] == 2:
            chickens.append((i, j))
        if graph[i][j] == 1:
            homes.append((i, j))
chickens_com = list(itertools.combinations(chickens, M))

    

ans_list=[]
for chicken in chickens_com:
    d_list = []
    ans = 0
    for home in homes:
        h_x, h_y = home
        for x, y in chicken:
            d_list.append(abs(x - h_x) + abs(y - h_y))
        ans += min(d_list)
        d_list=[]
    ans_list.append(ans)

print(min(ans_list))
    



