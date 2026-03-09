#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1000000000

using namespace std; 

const int MAX = 1000001;

int n, m, start{};

vector<pair<int, int>> graph[MAX];

int dist[MAX];

void dijkstra(int start) {
    priority_queue<pair<int, int>> pq;

    pq.push({ 0, start });
    dist[start] = 0;

    while(!pq.empty()) {
        int nowCost = -pq.top().first;

        int nowNode = pq.top().second;

        pq.pop();

        if(dist[nowNode] < nowCost) continue;

        for(int i = 0; i < graph[nowNode].size(); i++) {
            int cost = nowCost + graph[nowNode][i].second;

            int nextNode = graph[nowNode][i].first;

            if(cost < dist[nextNode]) {
                dist[nextNode] = cost;
                pq.push(make_pair(-cost, nextNode));
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
    }

    fill(dist, dist + MAX, INF);

    dijkstra(1);
    cout << dist[N];
}