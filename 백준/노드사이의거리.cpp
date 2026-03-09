#include <iostream>

using namespace std; 

int N, M;

int graph[1001][1001];
int visited[1001];
int c;

void dfs(int start, int end) {
    if(start == end) {
        return ;
    }

    for(int i = 1; i <= N; i++) {
        if(visited[i] == 0 && graph[start][i] != 0) {
            c += graph[start][i];
            visited[i] = c;
            dfs(i, end);
            c -= graph[start][i];
        }
    }
}

int main() {
    
    cin >> N >> M;

    for(int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    for(int i = 0; i < M; i++) {
        int start, end;
        cin >> start >> end;
        visited[start] = -1;
        dfs(start, end);
        if(visited[end] == -1) {
            cout << 0 << "\n";
        } else {
            cout << visited[end] << "\n";
        }
        c = 0;
        for(int i = 0; i <= N; i++) {
            visited[i] = 0;
        }
    }
}