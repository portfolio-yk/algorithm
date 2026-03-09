import heapq

N = int(input())
question_list = []
for _ in range(N):
    question = list(map(int, input().split()))
    question_list.append(question)

question_list.sort(key=lambda x : (x[0], -x[1]))

day = 1

select = []

for [deadline, count] in question_list:
    if deadline >= day:
        heapq.heappush(select, (count, deadline))
        day += 1
    else:
        s_count, s_deadline = heapq.heappop(select)
        if s_count < count:
            heapq.heappush(select, (count, deadline))
        else:
            heapq.heappush(select, (s_count, s_deadline))

count_sum = sum([count for count, _ in select])
print(count_sum)
