#include <iostream>
#include <queue>
using namespace std;

int N;

int board[101][101];
int visited[101][101];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };


int bfs(int start_x, int start_y, int range) {
    if(visited[start_x][start_y] == 1 || board[start_x][start_y] <= range) {
        return -1;
    }
    queue<pair<int, int>> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();

        int x = xy.first;
        int y = xy.second;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

            if(visited[nx][ny] == 0 && board[nx][ny] > range) {
                visited[nx][ny] = 1;
                q.push({ nx, ny });
            }
        }
    }

    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    int ans = 0;
    int h = 0;
    
    while(1) {
        int c = 0;
        for(int i = 0; i < N; i++) {
           for(int j = 0; j < N; j++) {
                int result = bfs(i, j, h);
                
                if(result == 1) {
                    c++;
                }
            }
        }

        ans = max(ans, c);
        if(c == 0) break;
        h++;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                visited[i][j] = 0;
            }
        }   
    }

    cout << ans;
}