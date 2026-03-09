#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> adj[1001];
bool visited[1001];


void dfs(int v){
    visited[v] = true;
    cout << v << " ";
    for (int next : adj[v]) {
        if (!visited[next]) dfs(next);
    }
}

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (int next : adj[v]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}


int main() {
    int N, M, V;

    cin >> N >> M >> V;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 1; i <= N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    dfs(V);
    cout << "\n";

    for(int i = 1; i <= N; i++) visited[i] = false;

    bfs(V);
    cout << "\n";

    return 0;
}