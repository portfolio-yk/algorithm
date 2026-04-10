#include <iostream>
#include <set>
#include <vector>
using namespace std;

int L, N, Q;

int board[45][45];
int warrior_board[45][45];

typedef struct warrior {
    int num;
    int r;
    int c;
    int h;
    int w;
    int hp;
    int is_over;
    int o_hp;
} warrior;

warrior warrior_list[35];

void print_w_board() {
    for(int i = 0; i < L; i++) {
        for(int j = 0; j < L; j++) {
            cout << warrior_board[i][j] << " ";
        }
        cout << "\n";
    }
}

int is_near_ob(warrior w, int dir) {
    if(dir == 0) {
        int x = w.r;
        if(x - 1 < 0) return -1;

        for(int i = 0; i < w.w; i++) {
            int y = w.c + i;

            if(board[x - 1][y] == 2) {
                return -1;
            }
        }
    } else if(dir == 1) {
        int y = w.c + w.w - 1;
        // cout << "b" << y << "\n";
        if(y + 1 > L - 1) return -1;
        for(int i = 0; i < w.h; i++) {
            int x = w.r + i;

            if(board[x][y + 1] == 2) {
                return -1;
            }
        }
    } else if(dir == 2) {
        int x = w.r + w.h - 1;
        if(x + 1 >  L - 1) return -1;

        for(int i = 0; i < w.w; i++) {
            int y = w.c + i;

            if(board[x + 1][y] == 2) {
                return -1;
            }
        }
    } else {
        int y = w.c;
        if(y - 1 < 0) return -1;
        for(int i = 0; i < w.h; i++) {
            int x = w.r + i;

            if(board[x][y - 1] == 2) {
                return -1;
            }
        }
    }
    return 1;
}

set<int> get_near_warriors(warrior w, int dir) {
    set<int> warriors;
    if(dir == 0) {
        int x = w.r;
        if(x - 1 < 0) return warriors;

        for(int i = 0; i < w.w; i++) {
            int y = w.c + i;

            if(warrior_board[x - 1][y] != 0) {
                warriors.insert(warrior_board[x - 1][y]);
            }
        }
    } else if(dir == 1) {
        int y = w.c + w.w - 1;
        if(y + 1 > L - 1) return warriors;
        for(int i = 0; i < w.h; i++) {
            int x = w.r + i;

            if(warrior_board[x][y + 1] != 0) {
                warriors.insert(warrior_board[x][y + 1]);
            }
        }
    } else if(dir == 2) {
        int x = w.r + w.h - 1;
        if(x + 1 >  L - 1) return warriors;

        for(int i = 0; i < w.w; i++) {
            int y = w.c + i;

            if(warrior_board[x + 1][y] != 0) {
                warriors.insert(warrior_board[x + 1][y]);
            }
        }
    } else {
        int y = w.c;
        if(y - 1 < 0) return warriors;
        for(int i = 0; i < w.h; i++) {
            int x = w.r + i;

            if(warrior_board[x][y - 1] != 0) {
                warriors.insert(warrior_board[x][y - 1]);
            }
        }
    }
    return warriors;
}

void move(int num, int dir) {
    warrior w = warrior_list[num];
    int temp[45][45];
    if(dir == 0) {
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c] = 0;
                temp[i + w.r - 1][j + w.c] = w.num;
            }
        }
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r - 1][j + w.c] = temp[i + w.r - 1][j + w.c];
            }
        }
        warrior_list[num].r--;
        return;
    } else if(dir == 1) {
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c] = 0;
                temp[i + w.r][j + w.c + 1] = w.num;
            }
        }
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c + 1] = temp[i + w.r][j + w.c + 1];
            }
        }
        warrior_list[num].c++;
        return;
    } else if(dir == 2) {
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c] = 0;
                temp[i + w.r + 1][j + w.c] = w.num;
            }
        }
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r + 1][j + w.c] = temp[i + w.r + 1][j + w.c];
            }
        }
        warrior_list[num].r++;
        return;
    } else {
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c] = 0;
                temp[i + w.r][j + w.c - 1] = w.num;
            }
        }
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c - 1] = temp[i + w.r][j + w.c - 1];
            }
        }
        warrior_list[num].c--;
        return;
    }
}

void damage(int num) {
    warrior w = warrior_list[num];
    int c = 0;
    for(int i = 0; i < w.h; i++) {
        for(int j = 0; j < w.w; j++) {
            if(board[i + w.r][j + w.c] == 1) {
                c++;
            }
        }
    }
    warrior_list[num].hp -= c;
    if(warrior_list[num].hp <= 0) {
        for(int i = 0; i < w.h; i++) {
            for(int j = 0; j < w.w; j++) {
                warrior_board[i + w.r][j + w.c] = 0;
            }
        }
        warrior_list[num].is_over = 1;
    }
}

bool can_push(int num, int dir) {
    warrior w = warrior_list[num];

    int result = is_near_ob(w, dir);
    if(result == -1) return false;

    set<int> near_warriors = get_near_warriors(w, dir); 
    for(int near_num : near_warriors) {
        if(!can_push(near_num, dir)) {
            return false;
        }
    }

    return true;
}

void push(int num, int dir) {
    warrior w = warrior_list[num];

    set<int> near_warriors = get_near_warriors(w, dir); 

    for(int near_num : near_warriors) {
        push(near_num, dir);
    }

    move(num, dir);
    damage(num);
}

bool order(int num, int dir, int start) {
    warrior w = warrior_list[num];

    int result = is_near_ob(w, dir);
    if(result == -1) return false;

    set<int> near_warriors = get_near_warriors(w, dir); 

    for(int near_num : near_warriors) {
        if(!can_push(near_num, dir)) {
            return false;
        }
    }

    for(int near_num : near_warriors) {
        push(near_num, dir);
    }

    move(num, dir);
    return true;
}

void put_warrior(warrior w) {
    for(int i = 0; i < w.h; i++) {
        for(int j = 0; j < w.w; j++) {
            warrior_board[i + w.r][j + w.c] = w.num;
        }
    }
}

int main() {
    cin >> L >> N >> Q;

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < L; j++) {
            cin >> board[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        int r, c, h, w, hp;
        cin >> r >> c >> h >> w >> hp;
        warrior_list[i] = { i, r - 1, c - 1, h, w, hp, 0 , hp };
        put_warrior(warrior_list[i]);
    }

    while(Q--) {
        int num, dir;
        //0 : 위, 1 : 오른, 2 : 아래, 3 : 왼
        cin >> num >> dir;
        //죽은 애처리
        if(warrior_list[num].is_over == 0) {
            order(num, dir, num);
        }
    }

    int ans = 0;

    for(int i = 1; i <= N; i++) {
        if(warrior_list[i].is_over == 0) {
            ans += warrior_list[i].o_hp - warrior_list[i].hp;
        }
    }

    cout << ans;
}