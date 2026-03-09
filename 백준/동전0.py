N, total = map(int, input().split())
coinList = []

for i in range(N):
    coinList.append(int(input()))

count = 0
i = 0

coin = coinList[N - 1]
while True:
    if(total - coin >= 0):
        c = total // coin
        count += c
        total = total - (coin * c)
    else: 
        i += 1
        coin = coinList[N - i - 1]

    if(total == 0): break

print(count)
