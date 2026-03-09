i = int(input())
sumList = []
for j in range(i):
    v = int(input())
    sumList.append(v)

count = 0

def calculate(result, m):
    global count
    if(result == 1 or result == 0):
        return 

    result = result - m

    if(result == 1 or result == 0):
        count += 1

    r = 3
    if(result < 3): r = result
    
    
    for i in range(r, 0, -1):
        calculate(result, i)

def sol(num):
    global count
    c = num

    if(c == 1):
        count += 1
        print(count)
        count = 0
        return

    for i in range(3, 0, -1):
        calculate(c, i)
    print(count)
    count = 0


for k in range(i):
    sol(sumList[k])