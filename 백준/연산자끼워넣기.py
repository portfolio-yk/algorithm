import math

N = int(input())
numList = list(map(int, input().split()))
exCountList = list(map(int, input().split()))

exList = [-1] * (N - 1)


max = -math.inf
min = math.inf



def dfs(depth):
    if depth == N - 1:
        #print(exList)
        cal(exList)
        return

    for i in range(4):
        if exCountList[i] > 0:
            exCountList[i] -= 1
            exList[depth] = i
            dfs(depth + 1)
            exCountList[i] += 1


def cal(list):
    global max
    global min

    result = numList[0]
    for i in range(N - 1):
        num = numList[i + 1]
        ex =  list[i]

        if ex == 0:
            result += num
        elif ex == 1:
            result -= num
        elif ex == 2:
            result *= num
        elif ex == 3:
            if(result < 0):
                result = (-1)*((-1) * result // num)
            else:
                result //= num
    
    if max <= result:
        max = result
    
    if min >= result:
        min = result

    return

dfs(0)

print(max)
print(min)