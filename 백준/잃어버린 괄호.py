## -를 기준으로 쪼개야 최솟값이 나온다.

str_input = input()
list = str_input.split('-')

sum_list = []

for ex in list:
    list_2 = ex.split('+')
    
    sum = 0
    for ex_2 in list_2:
        sum += int(ex_2)
    sum_list.append(sum)
    sum = 0

answer = sum_list[0]
for i in range(len(sum_list) - 1):
    answer -= sum_list[i + 1]

print(answer)