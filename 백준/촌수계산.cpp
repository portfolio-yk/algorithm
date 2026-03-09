#include <iostream>
#include <vector>
#include <queue>
#define MAX 101
using namespace std;

int N;
int x, y;
int m;

vector<int> graph[MAX];
int visited[MAX];
queue<int> q;

int search(int start, int end) {
    q.push(start);

    while(q.size()) {
        int node = q.front();
        q.pop();
        if(node == end) return visited[node];

        for(int n : graph[node]) {
            if(visited[n] == 0) {
                visited[n] = visited[node] + 1;
                q.push(n);
            }
        }
    }

    return -1;
}

int main() {
    cin >> N;
    cin >> x >> y;
    cin >> m;

    for(int i = 0; i < m; i++) {
        int node1, node2;
        cin >> node1 >> node2;

        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    cout << search(x, y);
}