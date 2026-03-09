N = int(input())
people = list(map(int, input().split()))
people.sort()

time = 0
total_time = 0
for person in people:
    time += person
    total_time += time
print(total_time)