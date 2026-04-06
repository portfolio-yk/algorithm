#include <iostream>
#include <queue>
#include <algorithm>
#define MAX 55
#define CLEANER -2
using namespace std;

int N, K, L;

int board[MAX][MAX];
int c_board[MAX][MAX];
int visited[MAX][MAX];
pair<int, int> cleaner[MAX];

int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

void print_board() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << board[i][j] << " ";  
        }
        cout << "\n";
    }
}

void print_cboard() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << c_board[i][j] << " ";  
        }
        cout << "\n";
    }
}

void clear_visited() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }
}

bool compare(const pair<int, pair<int, int>>& n1, const pair<int, pair<int, int>>& n2) {
    if(n1.first != n2.first) return n1.first < n2.first;
    if(n1.second.first != n2.second.first) return n1.second.first < n2.second.first;
    return n1.second.second < n2.second.second;
}

pair<int, int> get_next_pos(int start_x, int start_y) {
    vector<pair<int, pair<int, int>>> possible;
    queue<pair<int, int>> q;

    if(board[start_x][start_y] > 0) {
        possible.push_back({0, {start_x, start_y}});
    }

    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;
    // cout << start_x << " " << start_y << "\n";

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;
            // cout << visited[nx][ny] << " " << board[nx][ny] << "\n";
            if(visited[nx][ny] == 0 && board[nx][ny] >= 0 && c_board[nx][ny] == 0) {
                // cout << nx << " " << ny << "\n";
                visited[nx][ny] = visited[x][y] + 1;
                if(board[nx][ny] > 0) {
                    possible.push_back({visited[nx][ny],{ nx, ny }});
                }
                q.push({ nx, ny });
            }
        }
    }

    if(possible.empty()) {
        return {-1, -1}; 
    }


    sort(possible.begin(), possible.end(), compare);
    // for(pair<int, pair<int, int>> a : possible) {
    //     cout << a.first <<"\n";
    //     cout << a.second.first << " " << a.second.second <<"\n";
    // }


    return possible[0].second;
}

void clean(int x, int y) {
    // 작성자님의 원래 완벽했던 방향 배열 (제외할 방향: 좌, 상, 우, 하)
    int dx2[4] = { 0, -1, 0, 1 };
    int dy2[4] = { -1, 0, 1, 0 };

    // 🌟 핵심: 먼지량을 더할 때 벽(-1)은 무시하고, 최대 20까지만 계산하는 람다 함수
    auto get_cleanable_dust = [&](int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) return 0;
        if (board[r][c] <= 0) return 0; // 벽(-1)이나 빈칸(0)은 0으로 처리
        return board[r][c] > 20 ? 20 : board[r][c]; // 20 캡 적용
    };

    // 4방향 + 자기 자신의 "청소 가능한" 먼지 총합 계산
    int total = get_cleanable_dust(x, y);
    for(int i = 0; i < 4; i++) {
        total += get_cleanable_dust(x + dx2[i], y + dy2[i]);
    }

    int max_sum = -1; // 0일 경우 갱신이 안 될 수 있으므로 -1로 시작
    int dir = 0;
    
    // 어느 방향을 '제외'해야 남은 먼지량 합이 최대가 되는지 확인
    for(int i = 0; i < 4; i++) {
        int nx = x + dx2[i];
        int ny = y + dy2[i];

        int exclude_dust = get_cleanable_dust(nx, ny);
        
        if(max_sum < total - exclude_dust) {
            max_sum = total - exclude_dust;
            dir = i;
        }
    }

    // 실제 청소 로직 (작성자님 코드와 거의 동일)
    for(int i = 0; i < 4; i++) {
        int nx = x + dx2[i];
        int ny = y + dy2[i];

        if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;
        if(nx == x + dx2[dir] && ny == y + dy2[dir]) continue;

        if(board[nx][ny] > 0) {
            if(board[nx][ny] <= 20) {
                board[nx][ny] = 0;
            } else {
                board[nx][ny] -= 20;
            }
        }
    }
    if(board[x][y] > 0) {
        if(board[x][y] <= 20) {
            board[x][y] = 0;
        } else {
            board[x][y] -= 20;
        }
    }
}

void append_munji() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] > 0) {
                board[i][j] += 5;
            } 
        }
    }
}

void spread_munji() {
    vector<pair<int, pair<int, int>>> v;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] == 0) {
                int s = 0;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

                    if(board[nx][ny] > 0) {
                        s += board[nx][ny];
                    }
                }

                v.push_back({ s, { i, j }});
            } 
        }
    }
    
    for(int i = 0; i < v.size(); i++) {
        pair<int, pair<int, int>> d = v[i];
        int x = d.second.first;
        int y = d.second.second;
        int spread = d.first;
        
        board[x][y] = spread / 10;
    }

}

int main() {
    cin >> N >> K >> L;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        cleaner[i] = { x, y };
        c_board[x][y] = CLEANER;
    }

    while(L--) {
        //이동
        for(int i = 0; i < K; i++) {
            int x = cleaner[i].first;
            int y = cleaner[i].second;
            pair<int, int> next_pos = get_next_pos(x, y);
            clear_visited();
            int nx = next_pos.first;
            int ny = next_pos.second;
            if(nx != -1 && ny != -1) {
                c_board[x][y] = 0;
                c_board[nx][ny] = CLEANER;
                cleaner[i].first = nx;
                cleaner[i].second = ny;
            }
            
            
        }
        //print_board();
        //청소
        for(int i = 0; i < K; i++) {
            int x = cleaner[i].first;
            int y = cleaner[i].second;

            clean(x, y);
        }

        append_munji();

        spread_munji();

        //print_board();
        int ans = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(board[i][j] > 0) {
                    ans += board[i][j];
                }
            }
        }
        cout << ans << "\n";
    }
}