from collections import deque


T = int(input())
ans = []
for _ in range(T):
    N = int(input())
    s_x, s_y = map(int, input().split())
    d_x, d_y = map(int, input().split())


    board = [[0] * N for _ in range(N)]


    dx = [-2, 2, 0, 0]
    dy = [0, 0, -2, 2]

    d = [-1, 1]

    def bfs(x, y, des_x, des_y):
        queue = deque()
        queue.append((x, y))

        while queue:
            x, y = queue.popleft()

            if x == des_x and y == des_y:
                return board[x][y]

            for i in range(4):
                nx = x + dx[i]
                ny = y + dy[i]
                
                for j in range(2):
                    #x축 이동
                    if i < 2:
                        ny = y + dy[i] + d[j]
                    #y축 이동
                    else:
                        nx =  x + dx[i] + d[j]
                    
                    if nx < 0 or nx > N - 1 or ny < 0 or ny > N - 1:
                        continue
                    
                    if board[nx][ny] == 0:
                        board[nx][ny] = board[x][y] + 1
                        queue.append((nx, ny))
    ans.append(bfs(s_x, s_y, d_x, d_y))


for a in ans:
    print(a)

            
            
            




