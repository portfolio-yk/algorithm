#include <iostream>
#include <vector>
#include <queue>

#define MAX 51
using namespace std;

int N, L, R;

int graph[MAX][MAX];
int visited[MAX][MAX];

vector<pair<int, int>> s;
queue<pair<int, int>> q;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int bfs(int start, int end, int new_graph[MAX][MAX]) {
    int sum = 0;

    q.push({ start, end });

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;
        
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

            if(visited[nx][ny] == 0) {
                if(abs(new_graph[x][y] - new_graph[nx][ny]) >= L  && abs(new_graph[x][y] - new_graph[nx][ny]) <= R) {
                    visited[nx][ny] = 1;
                    s.push_back({ nx, ny });
                    sum += new_graph[nx][ny];
                    q.push({ nx, ny });
                }
            }
        }
    }

    return sum;
}

void clear_visited() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }
}

int move(int graph[MAX][MAX]) {
    int new_graph[MAX][MAX];
    memcpy(new_graph, graph, sizeof(new_graph));
    int c = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int sum = bfs(i, j, new_graph);
            
            if(!sum) continue;

            c++;

            int avg = int(sum / s.size());

            for(pair<int, int> e: s) {
                int x = e.first;
                int y = e.second;
                graph[x][y] = avg;
            }
            s.clear();
            
        }
    }
    clear_visited();
    return c > 0;
}

int main() {
    cin >> N >> L >> R;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int num;
            cin >> num;
            graph[i][j] = num;
        }
    }

    int c = 0;
    while(1) {
        if(move(graph)) {
            c++;
        } else {
            break;
        }
    }
    
    cout << c;
}