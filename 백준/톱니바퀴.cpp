#include <iostream>
#include <deque>
using namespace std;

deque<char> A;
deque<char> B;
deque<char> C;
deque<char> D;

deque<char> chain[4] = { A, B, C, D }; 

void right_shift(int target) {
    char b = chain[target].back();
    chain[target].pop_back();
    chain[target].push_front(b);
}

void left_shift(int target) {
    char b = chain[target].front();
    chain[target].pop_front();
    chain[target].push_back(b);
}


void left_rotate(int target, int r_dir)  {
    if(target < 0 || target > 3) return;

    int l = chain[target][6];

    if(r_dir == -1) {
        left_shift(target);
    } else {
        right_shift(target);
    }

    if(target > 0) {
        if(l != chain[target - 1][2]) {
            r_dir = r_dir == 1 ? -1 : 1;
            left_rotate(target - 1, r_dir);
        }
    }
}

void right_rotate(int target, int r_dir)  {
    if(target < 0 || target > 3) return;

    int r = chain[target][2];

    if(r_dir == -1) {
        left_shift(target);
    } else {
        right_shift(target);
    }

    if(target < 3) {
        if(r != chain[target + 1][6]) {
            r_dir = r_dir == 1 ? -1 : 1;
            right_rotate(target + 1, r_dir);
        }
    }
}

int main() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            char c;
            cin >> c;
            chain[i].push_back(c);
        }
    }


    int t;
    cin >> t;
    while(t--) {
        int target, r_dir;
        cin >> target >> r_dir;

        int r = chain[target - 1][2];

        left_rotate(target - 1, r_dir);
        if(target < 4) {
            if(r != chain[target][6]) {
                r_dir = r_dir == 1 ? -1 : 1;
                right_rotate(target, r_dir);
            }
        }
    }


    int score[4] = { 1, 2, 4, 8 };
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        if(chain[i][0] == '1') {
            ans += score[i];
        }
    }

    cout << ans;
}