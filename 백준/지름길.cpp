#include <iostream>
#include <vector>

const int INF = 10001;
const int MAX = 10001;

using namespace std;

int dist[MAX];
vector<pair<int, int>> jireumgil[MAX];
int N, M;

void dijkstra(int start) {
    for(int i = start; i < M; i++) {
        dist[i + 1] = dist[i] + 1;
        for(int j = 0; j < jireumgil[i + 1].size(); j++) {
            dist[i + 1] = min(dist[i + 1], dist[jireumgil[i + 1][j].first] + jireumgil[i + 1][j].second);
        }
    }
}

int main() {
    cin >> N >> M;

    while(N--) {
        int u, v, w;
        cin >> u >> v >> w;

        if(v > M || v - u < w) continue;
        jireumgil[v].push_back({u, w});
    }
    
    dijkstra(0);
    cout << dist[M];
}