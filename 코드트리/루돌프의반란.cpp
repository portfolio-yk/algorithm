#include <iostream>
#include <queue>
using namespace std;

int N, M, P, C, D;
int current_turn = 0;

typedef struct pos {
    int x;
    int y;
} pos;

pos rudolf;

typedef struct santa {
    int num;
    int x;
    int y;
    int block_turn;
    int is_over;
    int score;
} santa;

santa santa_list[35];

int board[55][55];


void print_board() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int get_dist(int r1, int c1, int r2, int c2) {
    return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

int get_rudolf_dir(santa s) {
    if(rudolf.y == s.y && rudolf.x > s.x) return 0;
    else if(rudolf.y < s.y && rudolf.x > s.x) return 1;
    else if(rudolf.y < s.y && rudolf.x == s.x) return 2;
    else if(rudolf.y < s.y && rudolf.x < s.x) return 3;
    else if(rudolf.y == s.y && rudolf.x < s.x) return 4;
    else if(rudolf.y > s.y && rudolf.x < s.x) return 5;
    else if(rudolf.y > s.y && rudolf.x == s.x) return 6;
    else return 7;
}
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void push_santa(santa s, int dir, int dist) {
    int nx = s.x + dx[dir] * dist;
    int ny = s.y + dy[dir] * dist;

    //영역 넘김 죽음
    if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) {
        santa_list[board[s.x][s.y]].is_over = 1;
        board[s.x][s.y] = 0;
        return;
    }

    //갈 곳에 다른 산타가 있으면 한 칸 밀어
    if(board[nx][ny] > 0 && board[nx][ny] != s.num) {
        santa n_s = santa_list[board[nx][ny]];
        push_santa(n_s, dir, 1);    
    }
    //이동
    santa_list[board[s.x][s.y]].x = nx;
    santa_list[board[s.x][s.y]].y = ny;
    if(board[nx][ny] != s.num) {
        board[s.x][s.y] = 0;
    }
    board[nx][ny] = s.num;
    
    
}

void go_rudolf(int dir) {
    int nx = rudolf.x + dx[dir];
    int ny = rudolf.y + dy[dir];
    
    if(board[nx][ny] > 0) {
        //해당 산타 C만큼 점수 얻음
        santa_list[board[nx][ny]].score += C;
        santa_list[board[nx][ny]].block_turn = current_turn + 2;
        push_santa(santa_list[board[nx][ny]], dir, C);
    }

    
    board[nx][ny] = -1;
    board[rudolf.x][rudolf.y] = 0;
    rudolf.x = nx;
    rudolf.y = ny;
}

santa find_closest_santa() {
    int min_dist = 1e9;
    int min_x;
    int min_y;
    for(int i = N - 1; i >= 0; i--) {
        for(int j = N - 1; j >= 0; j--) {
            if(board[i][j] > 0) {
                santa s = santa_list[board[i][j]];
                if(s.is_over == 1) continue;
                
                int dist = get_dist(rudolf.x, rudolf.y, s.x, s.y);
                if(min_dist > dist) {
                    min_dist = dist;
                    min_x = s.x;
                    min_y = s.y;
                }
            }
        }
    }
    return santa_list[board[min_x][min_y]];
}

int is_all_over() {
    int is_live = 0;
    for(int i = 1; i <= P; i++) {
        if(santa_list[i].is_over == 0){
            is_live = 1;
        }
    }
    return is_live != 1;
}

void go_santa() {
    for(int i = 1; i <= P; i++) {
        santa s = santa_list[i];

        if(s.is_over == 1 || s.block_turn > current_turn) continue;

        int min_dist = get_dist(s.x, s.y, rudolf.x, rudolf.y);
        int min_x = s.x;
        int min_y = s.y;
        int dir = -1;
        for(int i2 = 0; i2 < 8; i2 += 2) {
            int nx = s.x + dx[i2];
            int ny = s.y + dy[i2];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N -1) continue; 
            
            if(board[nx][ny] > 0) continue;
            int dist = get_dist(nx, ny, rudolf.x, rudolf.y);
            if(dist < min_dist) {
                min_dist = dist;
                min_x = nx;
                min_y = ny; 
                dir = i2;
            }
        }

        //가까워질 수 있는 방법이 없네
        if(min_x == s.x && min_y == s.y) continue;
        //갈 곳이 루돌프
        if(board[min_x][min_y] == -1) {
            santa_list[i].score += D;
            santa_list[i].block_turn = current_turn + 2;
            //반대로 튕기기
            push_santa(s, (dir + 4) % 8, D - 1);
        } else {
            board[min_x][min_y] = board[s.x][s.y];
            board[s.x][s.y] = 0;
            santa_list[i].x = min_x;
            santa_list[i].y = min_y;
        }

    }
}

int main() {
    cin >> N >> M >> P >> C >> D;

    cin >> rudolf.x >> rudolf.y;
    rudolf.x--;
    rudolf.y--;

    for(int i = 0; i < P; i++) {
        int num, r, c;
        cin >> num >> r >> c;
        santa_list[num] = { num, r - 1, c - 1, 0, 0, 0 };
        board[r - 1][c - 1] = num;
    }

    board[rudolf.x][rudolf.y] = -1;
    
    while(M--) {
        //다 죽음
        if(is_all_over()) break;
        
        
        //가장 가까운 산타 찾기
        santa s = find_closest_santa();
        //가장 가까운 산타와 방향
        int dir = get_rudolf_dir(s);
        //루돌프 1칸 움직임
        go_rudolf(dir);
        //산타들 움직임
        go_santa();
        
        //탈락하지 않은 산타 1점 씩 추가 부여
        for(int i = 1; i <= P; i++) {
            if(santa_list[i].is_over == 0) {
                santa_list[i].score += 1;
            }
        }
        current_turn++;
    }
    
    for(int i = 1; i <= P; i++) {
        cout << santa_list[i].score << " ";
    }
    
}
