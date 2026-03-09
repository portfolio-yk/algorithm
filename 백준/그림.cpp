#include <iostream>
#include <queue>
#define MAX 501
using namespace std;

int n, m;
int graph[MAX][MAX];
int visited[MAX][MAX];

queue<pair<int, int>> q;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1};

int bfs(int start, int end) {
    if(graph[start][end] == 0 || visited[start][end] != 0) {
        return 0;
    }

    q.push({ start, end });
    int c = 1;
    visited[start][end] = 1;

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;

        for(int i = 0; i < 4; i++) { 
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > n - 1 || ny < 0 || ny > m - 1) continue;

            if(visited[nx][ny] == 0 && graph[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                c++;
                q.push({ nx, ny });
            }  
        }
    }

    return c;
}

int main() {
    cin >> n >> m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num;
            cin >> num;
            graph[i][j] = num;
        }
    }
    int max_count = 0;
    int c = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int res = bfs(i, j);
            if(res > 0) {
                max_count = max(max_count, res);
                c++;
            }
        }
    }
    cout << c << "\n" << max_count;
}