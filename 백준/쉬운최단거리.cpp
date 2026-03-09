#include <iostream>
#include <queue>

using namespace std;

int board[1000][1000];
int dis_board[1000][1000];

int n, m;

queue<pair<int, int>> q;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(int x, int y) {
    q.push({x, y});

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();

        int x = xy.first;
        int y = xy.second;

        board[x][y] = -1;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > n - 1 || ny < 0 || ny > m - 1) continue;

            if(board[nx][ny] !=0 && board[nx][ny] != -1) {
                board[nx][ny] = -1;
                dis_board[nx][ny] = dis_board[x][y] + 1;
                q.push({nx, ny});
            } 

        }
    }
}

int main() {
    cin >> n >> m;

    int s_x, s_y;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num;
            cin >> num;
            board[i][j] = num;

            if(num == 2) {
                s_x = i;
                s_y = j;
            }
        }
    }

    bfs(s_x, s_y);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num = dis_board[i][j];
            if(dis_board[i][j] == 0 && board[i][j] == 1) {
                cout << "-1" << " ";
            } else {
                cout << dis_board[i][j] << " ";
            }
            
        }
        cout << "\n";
    }
    
}
