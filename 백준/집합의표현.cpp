#include <iostream>
#define MAX int(1e7)

using namespace std;

int parent[MAX];

int getParent(int node) {
    if(parent[node] == node) return node;
    return parent[node] = getParent(parent[node]);
}

void unionNode(int node1, int node2) {
    int a = getParent(node1);
    int b = getParent(node2);

    if(a == b) return;

    if(a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {
    ios_base :: sync_with_stdio(false);

    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    for(int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    for(int i = 0; i < M; i++) {
        int e, n1, n2;

        cin >> e >> n1 >> n2;

        if(e == 0) {
            unionNode(n1, n2);
        } else {
            int a = getParent(n1);
            int b = getParent(n2);

            if(a != b) cout << "NO" << "\n";
            else cout << "YES" << "\n";
        }
    }
}