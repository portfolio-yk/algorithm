#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> graph[1000001];
int visited[1000001];

int dp[1000001][2];

queue<int> q;

void bfs() {
    q.push(1);
    vector<pair<int, int>> stack;

    while(q.size()) {
        int parent = q.front();
        q.pop();
        visited[parent] = 1;

        for(int child : graph[parent]) {
            if(visited[child] == 0) {
                q.push(child);
                stack.push_back({ parent, child });
            }
        }
    }

    while(stack.size()) {
        pair<int, int> node = stack.back();
        stack.pop_back();
        int parent = node.first;
        int child = node.second;

        dp[parent][0] += dp[child][1]; 
        dp[parent][1] += min(dp[child][0], dp[child][1]);
    }
}

int main() {
    int N;
    cin >> N;

    for(int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= N; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    bfs();
    cout << min(dp[1][0],dp[1][1]);
} 