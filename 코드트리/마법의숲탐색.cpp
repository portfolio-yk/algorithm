#include <iostream>
#include <queue>
#include <cstring>
#define MAX 75
using namespace std;

int R, C, K;


typedef struct pos {
    int x;
    int y;
} pos;

typedef struct golem {
    int num;
    pos center;
    int dir;
} golem;

int board[MAX][MAX];
golem golem_list[1005];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_board() {
    for(int i = 0; i < R + 3; i++) {
        for(int j = 0; j < C; j++) {
            cout << board[i][j] << "  ";
        }
        cout << "\n";
    }
}

void clear_board() {
    for(int i = 0; i < R + 3; i++) {
        for(int j = 0; j < C; j++) {
            board[i][j] = 0;
        }
    }
}

pos get_exit(golem g, int dir) {
    if(dir == 0) return { g.center.x - 1, g.center.y };
    if(dir == 1) return { g.center.x, g.center.y + 1 };
    if(dir == 2) return { g.center.x + 1, g.center.y };
    else return { g.center.x, g.center.y - 1 };
}

int is_down(golem g) {
    pos p = g.center;
    if(p.x + 2 > (R + 3) - 1) return 0;

    if(board[p.x + 2][p.y] == 0 && board[p.x + 1][p.y + 1] == 0 && board[p.x + 1][p.y - 1] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_left(golem g) {
    pos p = g.center;
    if(p.y - 2 < 0) return 0;
    if(p.x + 2 > (R + 3) - 1) return 0;

    if(board[p.x][p.y - 2] == 0 && board[p.x - 1][p.y - 1] == 0 && board[p.x + 1][p.y - 1] == 0 && board[p.x + 2][p.y - 1] == 0 && board[p.x + 1][p.y - 2] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_right(golem g) {
    pos p = g.center;
    if(p.y + 2 > C - 1) return 0;
    if(p.x + 2 > (R + 3) - 1) return 0;
    if(board[p.x][p.y + 2] == 0 && board[p.x - 1][p.y + 1] == 0 && board[p.x + 1][p.y + 1] == 0 && board[p.x + 2][p.y + 1] == 0 && board[p.x + 1][p.y + 2] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_over() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < C; j++) {
            if(board[i][j] != 0) {
                return 1;
            } 
        }
    }
    return 0;
}

int visited[MAX][MAX];

int calculate(golem g) {
    int max_row = g.center.x + 1;
    // cout << "??" << max_row << "\n";
    pos exit_pos = get_exit(g, g.dir);
    for(int i = 0; i < 4; i++) {
        int nx = exit_pos.x + dx[i];
        int ny = exit_pos.y + dy[i];

        if(nx < 0 || nx > (R + 3) - 1 || ny < 0 || ny > C - 1) continue;

        if(visited[nx][ny] == 0 && board[nx][ny] != 0 && board[nx][ny] != g.num) {
            // cout << "?" << board[nx][ny] << "\n";
            visited[nx][ny] = 1;
            int row = calculate(golem_list[board[nx][ny]]);
            visited[nx][ny] = 0;
            // cout << "???" << row << "\n";
            max_row = max(max_row, row);
        }
    }
    return max_row;
}


int bfs(int start_x, int start_y) {
    queue<pos> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;

    int max_row = 0;

    while(q.size()) {
        pos p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > (R + 3) - 1 || ny < 0 || ny > C - 1) continue;

            golem g = golem_list[board[nx][ny]];
            pos exit_pos = get_exit(g, g.dir);

            if(visited[nx][ny] == 0 && visited[exit_pos.x][exit_pos.y] == 0 && board[nx][ny] != 0 && board[nx][ny] != board[x][y]) {
                visited[nx][ny] = 1;
                int row = g.center.x + 1;
                max_row = max(max_row, row);
                q.push({ exit_pos.x, exit_pos.y });
            }
        }
    }
    return max_row;
}



int main() {
    cin >> R >> C >> K;
    int ans = 0;
    for(int i = 1; i <= K; i++) {
        int c, d;
        cin >> c >> d;
        // 0 : 북, 1 : 동, 2 : 남, 3 : 서
        golem g = { i, { 1, c - 1 }, d };
        golem_list[i] = g;
        int isChange = 1;
        while(isChange) {
            isChange = 0;
            //남쪽 이동
            if(is_down(g)) {
                g.center.x++;
                isChange = 1;
                continue;
            }
            

            //서쪽 이동
            if(is_left(g)) {
                g.center.y--;
                g.center.x++;
                g.dir = (4 + (g.dir - 1)) % 4;
                isChange = 1;
                continue;
            }
            
            //동쪽 이동
            if(is_right(g)) {
                g.center.y++;
                g.center.x++;
                g.dir = (g.dir + 1) % 4;
                isChange = 1;
                continue;
            }
        }
        
        
        //배치
        golem_list[i] = g;
        board[g.center.x][g.center.y] = g.num;
        for(int j = 0; j < 4; j++) {
            // cout << "? \n";
            int nx = g.center.x + dx[j];
            int ny = g.center.y + dy[j];
            board[nx][ny] = g.num;
        }
        // print_board();
        // cout << "\n";

        if(is_over()) {
            clear_board();
            continue;
        }

        pos exit_pos = get_exit(g, g.dir);
        int max_row = g.center.x + 1;
        int row = bfs(exit_pos.x, exit_pos.y);
        memset(visited, 0, sizeof(visited));
        int a = max(max_row, row);
        // cout << a << "\n";
        ans += a - 2;
    }
    // print_board();

    cout << ans;
}