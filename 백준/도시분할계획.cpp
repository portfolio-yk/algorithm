#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;

int parent[100001];

class Edge {
public:
    int node[2];
    int distance;

    Edge(int node1, int node2, int distance) {
        this->node[0] = node1;
        this->node[1] = node2;
        this->distance = distance;
    }

    bool operator<(const Edge& edge) const {
        return this->distance < edge.distance;
    }
};

int getParent(int node) {
    if(parent[node] == node) return node;

    return parent[node] = getParent(parent[node]);
}

void unionParent(int node1, int node2) {
    int a = getParent(node1);
    int b = getParent(node2);

    if(a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {

    cin >> N >> M;

    vector<Edge> graph;

    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph.push_back(Edge(u, v, w));
    }

    for(int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    sort(graph.begin(), graph.end());
    int cost = 0;
    int last_bridge = 0;
    for(Edge e: graph) {
        if(getParent(e.node[0]) != getParent(e.node[1])) {
            unionParent(e.node[0], e.node[1]);
            cost += e.distance;
            last_bridge = e.distance;
        }
    }

    cout << cost - last_bridge;
}