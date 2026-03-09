s = input()
arr = []

for i in range(len(s)):
    arr.append(s[i:])

arr.sort()
for a in arr:
    print(a)