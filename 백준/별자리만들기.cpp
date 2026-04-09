#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAX 105
using namespace std;

double N;
pair<double, double> nodes[MAX];


typedef struct edge {
    double d;
    int node1;
    int node2;
} edge;

vector<edge> edges;

int parent[MAX];

int get_parent(int node) {
    if(parent[node] == node) return node;

    return parent[node] = get_parent(parent[node]);
}

void _union(int node1, int node2) {
    int a = get_parent(node1);
    int b = get_parent(node2);

    if(a < b) parent[b] = a;
    else parent[a] = b; 
}


bool compare(const edge& n1, const edge& n2) {
    return n1.d < n2.d;
}


double get_distance(int start_x, int start_y, int end_x, int end_y) {
    int a = start_x - end_x;
    int b = start_y - end_y;

    return sqrt(a * a + b * b);
}

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> nodes[i].first >> nodes[i].second;
        parent[i] = i;
    }

    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            double d = get_distance(nodes[i].first, nodes[i].second, nodes[j].first, nodes[j].second);
            edges.push_back({ d, i, j });
        }
    }

    sort(edges.begin(), edges.end(), compare);

    double ans = 0;
    for(edge e : edges) {
        if(get_parent(e.node1) != get_parent(e.node2)) {
            _union(e.node1, e.node2);
            ans += e.d;
        }
    }

    int b = ans * 100;
    ans = b / 100.0;
    cout << ans;
}