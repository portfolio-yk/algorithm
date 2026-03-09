from queue import PriorityQueue

N = int(input())
priorityQueue = PriorityQueue()
for _ in range(N):
    card = int(input())
    priorityQueue.put(card)
    
answer = 0

while True:
    if priorityQueue.qsize() == 0:
        break
    if priorityQueue.qsize() == 1:
        break

    first = priorityQueue.get()
    second = priorityQueue.get()


    sum = first + second
    answer += sum
    priorityQueue.put(sum)


print(answer)