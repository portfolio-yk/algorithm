import heapq
import sys


N = int(sys.stdin.readline())
size = 0
heap = []
numList = []
for _ in range(N):
    numList.append(int(sys.stdin.readline()))


for num in numList:
    if num == 0:
        if not heap:
            print(0)
        else:
            print((-1) * heapq.heappop(heap))
    else:
        heapq.heappush(heap, (-1) * num)

