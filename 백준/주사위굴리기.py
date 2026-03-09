a = [0,0,0]
b = [0, 0, 0, 0]

def move_down():
    global a,b
    a[1] = b[0]
    b = [b[3]] + b
    b.pop()
    

def move_up():
    global a,b
    a[1] = b[2]
    b = b[1:] + [b[0]]
    

def move_right():
    global a,b
    b[1] = a[0]
    a = [a[2]] + a
    a.pop()
    a[0], b[3] = b[3], a[0]

def move_left():
    global a,b
    b[1] = a[2]
    a = a[1:] + [a[0]]
    a[2], b[3] = b[3], a[2]
    

def dest(n):
    global a,b
    b[3] = n


N, M, x, y, K = map(int, input().split())
_map = []
for _ in range(N):
    _map.append(list(map(int, input().split())))
operands = list(map(int, input().split()))


for operand in operands:
    if operand == 4:
        x += 1
        if x > N - 1:
            x -=1
            continue
        move_down()
        if _map[x][y] == 0:
            _map[x][y] = b[3]
        else:
            dest(_map[x][y])
            _map[x][y] = 0
        print(b[1])
    elif operand == 3:
        x -=1
        if x < 0:
            x +=1
            continue
        move_up()
        if _map[x][y] == 0:
            _map[x][y] = b[3]
        else:
            dest(_map[x][y])
            _map[x][y] = 0
        print(b[1])
    elif operand == 2:
        y -= 1
        if y < 0:
            y +=1
            continue
        move_left()
        if _map[x][y] == 0:
            _map[x][y] = b[3]
        else:
            dest(_map[x][y])
            _map[x][y] = 0
        print(b[1])
    elif operand == 1:
        y += 1
        if y > M - 1:
            y -=1
            continue
        move_right()
        if _map[x][y] == 0:
            _map[x][y] = b[3]
        else:
            dest(_map[x][y])
            _map[x][y] = 0
        print(b[1])

