#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, M;
int parent[1001];

class Edge {
public:
    int node[2];
    int distance;
    Edge(int a, int b, int distance) {
        this->node[0] = a;
        this->node[1] = b;
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
    cin >> N;
    cin >> M;
    int sum_dis = 0;
    vector<Edge> edge_list;

    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge_list.push_back(Edge(u, v, w));
    }

    sort(edge_list.begin(), edge_list.end());

    for(int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    for(Edge e: edge_list) {
        if(getParent(e.node[0]) != getParent(e.node[1])) {
            unionParent(e.node[0], e.node[1]);
            sum_dis += e.distance;
        }
    }

    cout << sum_dis;
}