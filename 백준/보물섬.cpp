#include <iostream>
#include <queue>
using namespace std;

int N, M;
char graph[51][51];
int graph_count[51][51];
int graph_visited[51][51];

queue<pair<int, int>> q;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int max_count;

void bfs(int start, int end) {
    if(graph[start][end] != 'L') {
        return;
    }
    q.push({start, end});
    graph_visited[start][end] = 1;

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;

        
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
            
            if(graph[nx][ny] == 'L' && graph_count[nx][ny] == 0 && graph_visited[nx][ny] == 0) {
                graph_visited[nx][ny] = 1;
                graph_count[nx][ny] = graph_count[x][y] + 1;
                max_count = max(max_count, graph_count[nx][ny]);
                q.push({nx, ny});
            }
        }
        
    }
}

void clear_graph() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            graph_count[i][j] = 0;
            graph_visited[i][j] = 0;
        }
    } 
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            bfs(i, j);
            clear_graph();
        }
    }

    
    cout << max_count;
}