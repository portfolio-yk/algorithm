#include <iostream>
#define MAX 500005
using namespace std;

int N, M;

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

int main() {
    cin >> N >> M;
    int end_time = 0; 
    int end_flag = 0;

    for(int i = 0; i < N; i++) {
        parent[i] = i;
    }

    for(int i = 1; i <= M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        if(end_time == 0 && get_parent(node1) == get_parent(node2)) {
            end_time = i;
        }
        _union(node1, node2);
    }

    cout << end_time;
}