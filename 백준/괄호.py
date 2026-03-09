N = int(input())
PS_LIST = []
for _ in range(N):
    PS = list(input())
    PS_LIST.append(PS)

stack = []
for PS in PS_LIST:
    for i in range(len(PS)):
        ps = PS[i]
        if len(stack) == 0:
            stack.append(ps)
        else:
            if ps == ')' and  stack[len(stack)-1] == '(':
                stack.pop()
            else:
                stack.append(ps)

    if len(stack) > 0:
        print("NO")
    else:
        print("YES")
    stack = []