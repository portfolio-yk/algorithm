#include <iostream>
#define MAX 6005
#define INF 1e9
using namespace std;

int N, M;

typedef struct egde {
    int from;
    int to;
    int cost;
} edge;

egde edges[MAX];

long long d[MAX];

bool bf(int start) {
    d[start] = 0;

    bool isCycle = false;

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < M; j++) {
            int from = edges[j].from;
            int to = edges[j].to;
            int cost = edges[j].cost;

            if(d[from] != INF && d[to] > d[from] + cost) {
                d[to] = d[from] + cost;

                if(i == N) {
                    isCycle = true;
                }
            }
        }
    }

    return isCycle;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    fill(d, d + N + 1, INF);

    for(int i = 0; i < M; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        edges[i] = { u, v, d };
    }

    bool isCycle = bf(1);

    if(!isCycle) {
        for(int i = 2; i <= N; i++) {
            if(d[i] != INF)
                cout << d[i] << "\n";
            else
                cout << -1 << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
}