L, C = input().split(" ")
password = input()
chars = password.split(" ")
chars.sort()
vowels = "aeiou"
v_count = 0
c_count = 0

def dfs_combination(start, path, n, data):
    global v_count, c_count
    # n개를 다 뽑았으면 출력
    if len(path) == n and v_count >= 1 and c_count >= 2:
        print("".join(path))
        return

    # start 인덱스부터 시작해서 '앞으로'만 전진 (나보다 작은 숫자는 무시)
    for i in range(start, len(data)):
        if data[i] in vowels:
            v_count += 1
        else:
            c_count += 1
        
        path.append(data[i])
        # 지금 뽑은 요소의 '다음' 인덱스부터 탐색하도록 넘겨줌
        dfs_combination(i + 1, path, n, data)
        if data[i] in vowels:
            v_count -= 1
        else:
            c_count -= 1
        path.pop()


dfs_combination(0, [], int(L), chars)