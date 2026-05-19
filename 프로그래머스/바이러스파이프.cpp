#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define MAX 105

using namespace std;

int infected[MAX];
int visited[MAX];
vector<pair<int, int>> graph[MAX];
vector<vector<int>> cases;
vector<int> path;
int K;

void dfs(int depth) {
    if(depth == K) {
        cases.push_back(path);
        return;
    }
    
    for(int i = 1; i <= 3; i++) {
        path.push_back(i);
        dfs(depth + 1);
        path.pop_back();
    }
}

void infect(queue<int>& q, int pipe) {
    while(q.size()) {
        int node = q.front();
        q.pop();
        
        for(pair<int, int> n : graph[node]) {
            if(visited[n.first] == 0 && n.second == pipe) {
                visited[n.first] = 1;
                infected[n.first] = 1;
                q.push(n.first);
            }
        }
    }
}

int solution(int n, int infection, vector<vector<int>> edges, int k) {
    int answer = 0;
    K = k;
    dfs(0);
    
    for(vector<int> a : cases) {
        for(int z : a) {
            cout << z << "";
        }
        cout << "\n";
    }
    
    for(vector<int> e : edges) {
        graph[e[0]].push_back({ e[1], e[2] });
        graph[e[1]].push_back({ e[0], e[2] });
    }
    
    for(int i = 0; i < cases.size(); i++) {
        int c = 0;
        infected[infection] = 1;
        for(int j = 0; j < cases[i].size(); j++) {
            queue<int> infected_q;
            
            for(int k = 1; k <= n; k++) {
                if(infected[k] == 1) {
                    visited[k] = 1;
                    infected_q.push(k);
                }
            }
            
            infect(infected_q, cases[i][j]);
            
        }
        
        for(int k = 1; k <= n; k++) {
            if(infected[k] == 1) {
                c++;
            }
        }
        answer = max(answer, c);
        
        for(int k = 0; k <= n; k++) {
            infected[k] = 0;
            visited[k] = 0;
        }
    }
    
    return answer;
}