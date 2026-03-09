N = int(input())
s = []
aa = {}
for _ in range(N):
    z = [""] * 8
    inp = input()
    for i in range(len(inp)):
        z[8 - len(inp) + i] = inp[i]
        if inp[i] not in aa:
            aa[inp[i]] = 0
    
    s.append(z)


for i in range(8):
    c = list(map(lambda x: x[i], s))
    for j in range(len(c)):
        a = c[j]
        if a:
            aa[a] += 10 ** (8 - i- 1)

aa_values_ = list(aa.values())
aa_values_.sort(reverse=True)

number = 9
answer = 0
for v in aa_values_:
    answer += number * v
    number -= 1
print(answer)