import heapq
import sys


N = int(sys.stdin.readline())
size = 0
heap = []
numList = []
m = {}

for _ in range(N):
    numList.append(int(sys.stdin.readline()))


for num in numList:
    if num == 0:
        if not heap:
            print(0)
        else:
            n = heapq.heappop(heap)
            #print(m)
            if(n in m):
                if(m[n] > 0):
                    print((-1) * n)
                    m[n] -= 1
                else:
                    print(n)
            else:
                print(n)
    else:
        if(num < 0):
            if(abs(num) in m):
                m[abs(num)] += 1
            else:
                m[abs(num)] = 1
            heapq.heappush(heap, abs(num))
        else:
            heapq.heappush(heap, num)
