N = int(input())

table = []
for i in range(N):
    table.append(list(map(int, input().split())))
players = [i + 1 for i in range(N)]
visited = [False] * N
start = [0] * (N // 2)
link = [0] * (N // 2)



s = [0, 0]
value = 0
min = 1000



def dfs(depth):
    global value, min, players, start, link

    if depth == N // 2:
        link = list(set(players) - set(start))
        #print(start, link)
        v1 = sum(start, 0)
        value = 0
        v2 = sum(link, 0)
        value = 0

        diff = abs(v1 - v2)
        if min > diff:
            min = diff


        return
    

    for i in range(N):
        if visited[i] == False:
            if depth > 0 and start[depth - 1] > players[i]:
                continue
            start[depth] = players[i]
            #print(players)
            visited[i] = True
            dfs(depth + 1)
            visited[i] = False


def sum(p, depth):
    global value, s
    if depth == 2:
        #print(s)
        v = table[s[0] - 1][s[1] - 1]
        value += v
        return

    for i in range(N // 2):
        #print(p)
        s[depth] = p[i]
        sum(p, depth + 1)
    return value


dfs(0)
print(min)
