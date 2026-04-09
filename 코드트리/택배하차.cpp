#include <iostream>
#include <queue>
#include <vector>

#define MAX 105
using namespace std;

int N, M;

typedef struct package {
    int k;
    int h; 
    int w;
    int c;
    int r;
} package;

package packages[MAX];

int board[MAX][MAX];


void remove_board(package p) {
    int k = p.k; int h = p.h; int w = p.w; int c = p.c; int r = p.r;

    for(int j = r; j < r + h; j++) {
        for(int s = 0; s < w; s++) {
            board[j][c + s] = 0;
        }
    }
}

void remove(int num) {
    packages[num].k = 0;
    remove_board(packages[num]);
}

void setting(package p) {
    int k = p.k; int h = p.h; int w = p.w; int c = p.c; int r = p.r;
    // cout << r << " " << c << "\n";

    for(int j = r; j < r + h; j++) {
        for(int s = 0; s < w; s++) {
            board[j][c + s] = k;
        }
    }
}

bool is_in_pacakage(int num) {
    return packages[num].k != 0;
}

void update() {
    for(int i = 1; i < MAX; i++) {
        for(int j = 1; j < MAX; j++) {
            if(!is_in_pacakage(j)) continue;

            package p = packages[j];
            
            int r = p.r;
            int c = p.c;

            int d = r + p.h;
            while(d <= N) {
                int isStop = 0;
                for(int j = 0; j < p.w; j++) {
                    if(board[d][c + j] != 0) {
                        isStop = 1;
                        break;
                    }
                }
                if(isStop) {
                    break;
                }
                d++;
            }
            r = d - p.h;
            remove_board(packages[j]);
            packages[j].r = r;
            setting(packages[j]);
        }
    }
}


void print_board() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int find_front(package p, int dir) {
    int is_right_empty = 1;
    int is_left_empty = 1;
    for(int i = p.r; i < p.r + p.h; i++) {
        for(int j = p.c + p.w; j <= N; j++) {
            // cout << i << j << "\n";
            if(board[i][j] != 0) {
                //right
                is_right_empty = 0;
                break;
            }
        }
    }

    for(int i = p.r; i < p.r + p.h; i++) {
        for(int j = p.c - 1; j >= 1; j--) {
            if(board[i][j] != 0) {
                //left
                is_left_empty = 0;
                break;
            }
        }
    }
    if(dir == 0) {
        if(is_left_empty == 1) return 1;
        else return 0;
    } else {
        if(is_right_empty == 1) return 1;
        else return 0;
    }
}

int search_left(int r) {
    int num = -1;
    for(int i = 1; i <= N; i++) {
        if(board[r][i] != 0) {
            if(find_front(packages[board[r][i]], 0) == 0) continue;

            num = board[r][i];
            break;
        }
    }
    return num;
}

int search_right(int r) {
    int num = -1;
    for(int i = N; i >= 1; i--) {
        if(board[r][i] != 0) {
            if(find_front(packages[board[r][i]], 1) == 0) continue;

            num = board[r][i];
            break;
        }
    }
    return num;
}

int main() {
    cin >> N >> M;

    for(int i = 1; i <= M; i++) {
        int k, w, h, c;
        cin >> k >> h >> w >> c;
        
        packages[k] = { k, h, w, c, 1 };

        //setting
        setting(packages[k]);
        update();
    }

    // print_board();

    while(1) {
        //좌측 하차
        priority_queue<int, vector<int>, greater<int>> removal_packages;
        for(int i = 1; i <= N; i++) {
            int num = search_left(i);
            if(num != -1) {
                removal_packages.push(num);
            }
        }
        if(!removal_packages.size()) break;

        int remove_num = removal_packages.top();
        cout << remove_num << "\n";
        remove(remove_num);
        update();

        //우측 하차
        priority_queue<int, vector<int>, greater<int>> removal_packages_r;
        for(int i = 1; i <= N; i++) {
            int num = search_right(i);
            if(num != -1) {
                removal_packages_r.push(num);
            }
        }
        if(!removal_packages_r.size()) break;

        remove_num = removal_packages_r.top();
        cout << remove_num << "\n";
        remove(remove_num);
        update();


        //print_board();
    }
    
    

    
}