#include <iostream>
#include <queue>

using namespace std;
#define MAX 1001


char graph[MAX][MAX];
int visited[MAX][MAX][2];

int N, M;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

struct three {
    int x, y, z;
};

queue<three> q;

int bfs() {
    visited[0][0][0] = 1;
    q.push({ 0, 0, 0 });

    while(q.size()) {
        struct three xy = q.front();
        q.pop();
        int x = xy.x;
        int y = xy.y;
        int z = xy.z;

        if(x == N - 1 && y == M - 1) return visited[x][y][z];

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int block = z;

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;

            if(graph[nx][ny] == '0' && visited[nx][ny][block] == 0) {
                visited[nx][ny][block] = visited[x][y][block] + 1;
                q.push({ nx, ny, block });
            } else if(graph[nx][ny] == '1' && visited[nx][ny][block] == 0 && block == 0) {
                visited[nx][ny][block + 1] = visited[x][y][block] + 1;
                q.push({ nx, ny, block + 1 });
            }
        }
    }

    return -1;
}


int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> graph[i][j];
        }
    }

    cout << bfs();
}