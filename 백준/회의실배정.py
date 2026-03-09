#시간초과
# import math

# N = int(input())
# meetList = []
# for _ in range(N):
#     meetList.append(list(map(int, input().split())))

# realStart = 0
# resultList = []
# maxStart = 0
# count = 0

# maxStart = max(map(lambda x : x[0], meetList))
# while realStart < maxStart:
#     start = realStart
#     while True:
#         start_meets = [math.inf, math.inf]
#         for meet in meetList:
#             if meet[0] == start:
#                 if start_meets[1] > meet[1]:
#                     start_meets = meet

#         if start > maxStart:
#             break

#         if start_meets[0] == math.inf:
#             start = start + 1
#         else:
#             resultList.append(start_meets)
#             start = start_meets[1]
#     realStart += 1
#     if count < len(resultList):
#         count = len(resultList)
#     resultList = []
# print(count)



# 활동선택문제
# 끝나는 시간 순으로 정렬
# 겹치지 않는 것 선택

import sys
N = int(sys.stdin.readline())
meetList = []
for _ in range(N):
    meetList.append(list(map(int, sys.stdin.readline().split())))
meetList.sort(key=lambda x : (x[1], x[0]))

meetListLen = len(meetList)
max_count = 0
end = 0

for j in range(meetListLen):
    [cur_s, cur_e] = meetList[j]
    if cur_s >= end:
        end = cur_e
        max_count += 1
print(max_count)