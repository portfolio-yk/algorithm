#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int N, K;

deque<int> belt;
int robot[100] = { 0 };

int main() {
    cin >> N >> K;
    for(int i = 0; i < N * 2; i++) {
        int durablity;
        cin >> durablity;
        belt.push_back(durablity);
    }

    int step = 0;
    while(1) {
        step += 1;

        //1칸 이동 
        int last = belt.back();
        belt.pop_back();
        belt.push_front(last);

        for(int i = N - 2; i >= 0; i--) {
            if(robot[i] == 1){
                robot[i] = 0;
                robot[i + 1] = 1;
            }
        }

        //로봇 내리기
        if(robot[N - 1] == 1) {
            robot[N - 1] = 0;
        }

        //로봇 한 칸 이동
        for(int i = N - 2; i >= 0; i--) {
            if(robot[i] == 1){
                if(robot[i + 1] != 1 && belt[i + 1] != 0){
                    robot[i] = 0;
                    robot[i + 1] = 1;
                    belt[i + 1] -= 1;
                }
            }
        }

        //로봇 내리기
        if(robot[N - 1] == 1) {
            robot[N - 1] = 0;
        }

        //로봇 올리기
        if(belt[0] != 0) {
            robot[0] = 1;
            belt[0] -= 1;
        }

        //종료
        int count = 0;
        for(int i = 0; i < N * 2; i++) {
            if(belt[i] == 0) {
                count += 1;
            } 
        }
        
        if(count >= K) {
            break;
        }
    }

    cout << step;
}