#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

int K, M;
int board[6][6];
queue<int> q;

typedef struct pos {
    int x;
    int y;
} pos;

void print_board() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void rotate_90(int c_x, int c_y) {
    int temp[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int nx = (c_x - 1) + i;
            int ny = (c_y - 1) + j;

            int x = nx - c_x;
            int y = ny - c_y;
            temp[y + 1][1 - x] = board[nx][ny];
        }
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int nx = (c_x - 1) + i;
            int ny = (c_y - 1) + j;

            board[nx][ny] = temp[i][j];
        }
    }
}

int visited[5][5];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int bfs(int start_x, int start_y) {
    queue<pos> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;
    int t = board[start_x][start_y];
    int c = 1;

    while(q.size()) {
        pos p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;

            if(visited[nx][ny] == 0 && board[nx][ny] == t) {
                visited[nx][ny] = 1;
                c++;
                q.push({ nx, ny });
            }
        }
    }
    return c; 
}

vector<pos> bfs_crash(int start_x, int start_y) {
    vector<pos> remove;
    queue<pos> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;
    int t = board[start_x][start_y];

    while(q.size()) {
        pos p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;

        remove.push_back({ x, y });

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;

            if(visited[nx][ny] == 0 && board[nx][ny] == t) {
                visited[nx][ny] = 1;
                q.push({ nx, ny });
            }
        }
    }
    return remove; 
}

int get_crash_count() {
    int c = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            int result = bfs(i, j);
            if(result >= 3) {
                c += result;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    return c;
}

void fill_board() {
    for(int i = 0; i < 5; i++) {
        for(int j = 4; j >= 0; j--) {
            if(board[j][i] == 0) {
                board[j][i] = q.front();
                q.pop();
            }
            
        }
    }
}

int crash() {
    int c = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            vector<pos> result = bfs_crash(i, j);
            if(result.size() >= 3) {
                for(pos p : result) {
                    board[p.x][p.y] = 0;
                }
                c += result.size();
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    return c;
}

int main() {
    cin >> K >> M;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < M; i++) {
        int num;
        cin >> num;
        q.push(num);
    }

    while(K--) {
        int max_count = 0;
        int max_x = 1;
        int max_y = 1;
        int a = 0;
        //90도 회전
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                int x = j + 1;
                int y = i + 1;

                rotate_90(x, y);
                int c_90 = get_crash_count(); 
                if(max_count < c_90) {
                    max_count = c_90;
                    max_x = x;
                    max_y = y;
                    a = 90;
                }
                
                //롤백
                rotate_90(x, y);
                rotate_90(x, y);
                rotate_90(x, y);
            }
        }

        //180도 회전
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                int x = j + 1;
                int y = i + 1;

                rotate_90(x, y);
                rotate_90(x, y);
                int c_180 = get_crash_count(); 
                if(max_count < c_180) {
                    max_count = c_180;
                    max_x = x;
                    max_y = y;
                    a = 180;
                }
                
                //롤백
                rotate_90(x, y);
                rotate_90(x, y);
            }
        }

        //270도 회전
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                int x = j + 1;
                int y = i + 1;

                rotate_90(x, y);
                rotate_90(x, y);
                rotate_90(x, y);
                int c_270 = get_crash_count(); 
                if(max_count < c_270) {
                    max_count = c_270;
                    max_x = x;
                    max_y = y;
                    a = 270;
                }
                
                //롤백
                rotate_90(x, y);
            }
        }
        // cout << max_x << " " << max_y << " " << " " << a << "\n";
        for(int i = 0; i < a / 90; i++) {
            rotate_90(max_x, max_y);
        }

        int result = crash();
        // cout << result << "\n";
        // print_board();
        fill_board();
        // cout << "\n";
        // print_board();
        // cout << "\n";
        int ans = result;
        while(result) {
            result = crash();
            // cout << result << "\n";
            ans += result;
            // print_board();
            // cout << "\n";
            fill_board();
            // print_board();
            // cout << "\n";
        }

        if(ans == 0) break;
        cout << ans << " ";
    }
}