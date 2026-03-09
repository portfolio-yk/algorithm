from collections import deque

class RESULT:    
    def __init__(self):
        self.cnt = 0
        self.IDs = [0, 0, 0, 0, 0]

SIZE = 0
current_time = 0
worm_list = []

DR = [-1, 0, 1, 0]
DC = [0, 1, 0, -1]

def init(N: int) -> None:
    global SIZE, current_time, worm_list
    SIZE = N
    current_time = 0
    worm_list = []


def go(target_time: int):
    global current_time, worm_list
    while current_time < target_time:
        current_time += 1
        
        for worm in worm_list:
            hy, hx = worm["body"][0]
            is_straight_row = True
            is_straight_col = True
            
            for p in worm["body"]:
                if p[0] != hy:
                    is_straight_row = False
                if p[1] != hx:
                    is_straight_col = False
                
                if not is_straight_row and not is_straight_col:
                    break
            
            if is_straight_row or is_straight_col:
                worm["dir"] = (worm["dir"] + 1) % 4
                
            next_head = (hy + DR[worm["dir"]], hx + DC[worm["dir"]])
            worm["body"].appendleft(next_head)

            if worm["potential"] > 0:
                worm["potential"] -= 1
            else:
                worm["body"].pop()


        deads = set()
        potential_gains = {}
        head_map = {}
        body_map = {}

        for worm in worm_list:
            body = worm["body"]
            head = body[0]
            

            head_map.setdefault(head, []).append(worm["num"])
            if not (0 <= head[0] < SIZE and 0 <= head[1] < SIZE):
                deads.add(worm["num"])
            
            for i in range(1, len(body)):
                body_map.setdefault(body[i], []).append(worm["num"])

        for worm in worm_list:
            head = worm["body"][0]
            
            if len(head_map[head]) > 1:
                deads.add(worm["num"])

            # 머리가 몸통
            if head in body_map:
                deads.add(worm["num"])
                for target_id in body_map[head]:
                    potential_gains[target_id] = potential_gains.get(target_id, 0) + len(worm["body"])

        next_worms = []
        for worm in worm_list:
            if worm["num"] not in deads:
                worm["potential"] += potential_gains.get(worm["num"], 0)
                next_worms.append(worm)
        worm_list = next_worms

def join(mTime: int, mID: int, mX: int, mY: int, mLength: int) -> None:
    go(mTime)
    body = deque()
    for i in range(mLength):
        body.append((mY + i, mX))
    
    worm_list.append({
        "num": mID,
        "body": body,
        "potential": 0,
        "dir": 0 
    })

def top5(mTime: int) -> RESULT:
    go(mTime)

    sorted_worms = sorted(worm_list, key=lambda w: (-len(w["body"]), -w["num"]))
    
    res = RESULT()
    res.cnt = min(len(sorted_worms), 5)
    for i in range(res.cnt):
        res.IDs[i] = sorted_worms[i]["num"]
    return res

import sys

CMD_INIT = 100
CMD_JOIN = 200
CMD_TOP5 = 300

def run():
    Q = int(input())
    okay = False
    for q in range(Q):
        input_iter = iter(input().split())
        cmd = int(next(input_iter))
        if cmd == CMD_INIT:
            N = int(next(input_iter))
            init(N)
            okay = True
        elif cmd == CMD_JOIN:
            mTime = int(next(input_iter))
            mID = int(next(input_iter))
            mX = int(next(input_iter))
            mY = int(next(input_iter))
            mLength = int(next(input_iter))
            join(mTime, mID, mX, mY, mLength)
        elif cmd == CMD_TOP5:
            mTime = int(next(input_iter))
            user_ans = top5(mTime)
            correct_ans = int(next(input_iter))
            if user_ans.cnt != correct_ans:
                okay = False
            for i in range(correct_ans):
                correct_keyword = int(next(input_iter))
                if correct_keyword != user_ans.IDs[i]:
                    okay = False
        else:
            okay = False
    return okay


# sys.stdin = open('sample_input.txt', 'r')

T, MARK = map(int, input().split())

for tc in range(1, T + 1):
    score = MARK if run() else 0
    print("#%d %d" % (tc, score), flush = True)