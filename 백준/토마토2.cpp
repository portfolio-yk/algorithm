#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define MAX 101

using namespace std;

int N, M, H;
vector<int> row; 

int graph[MAX][MAX][MAX];

struct Point {
    int x, y, z;
};

queue<Point> q;

int dx[6] = {-1, 1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {0, 0, 0, 0, -1, 1};

void bfs() {
    while(q.size()) {
        struct Point point = q.front();
        q.pop();
        int x = point.x;
        int y = point.y;
        int z = point.z;

        
        //사방 감염
        for(int i =0; i < 6; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];

            if(nx < 0 || nx > M - 1 || ny < 0 || ny > N - 1 or nz < 0 || nz > H - 1) continue;

            if(graph[nz][nx][ny] == 0) {
                graph[nz][nx][ny] = graph[z][x][y] + 1;
                q.push({nx, ny, nz});
            }
        }
    }
}


int main() {
    cin >> N >> M >> H;
    

    //썩은 토마토 큐에 삽입
    for(int k = 0; k < H; k++){
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                cin >> graph[k][i][j];
                if(graph[k][i][j] == 1) {
                    q.push({i, j, k});
                }
            }
        }
    }
    
    
    bfs();

    int answer = 0;

    for(int k = 0; k < H; k++){
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(graph[k][i][j] == 0) {
                    cout << "-1";
                    return 0;
                }

                if(answer < graph[k][i][j]) {
                    answer = graph[k][i][j];
                }
                
            }
        }
    }

    cout << answer - 1;
    return 0;
}