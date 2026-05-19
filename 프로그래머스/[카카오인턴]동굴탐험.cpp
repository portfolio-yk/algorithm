#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#define MAX 200005

using namespace std;

vector<int> graph[MAX];
int visited[MAX];
int waiting[MAX];
vector<int> waitFor[MAX];
unordered_map<int, int> hash_m;
int N;

int bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    
    while(q.size()) {
        int s = q.front();
        q.pop();
        
        for(int n : waitFor[s]) {
            visited[n] = 1;
            q.push(n);
        }
        waitFor[s].clear();
        
        for(int n : graph[s]) {
            if(visited[n] == 0) {
                if(hash_m.find(n) != hash_m.end() && visited[hash_m[n]] == 0){
                    if(waiting[n] == 0) {
                        waiting[n] = 1;
                        waitFor[hash_m[n]].push_back(n);
                    }
                    continue;
                }
                visited[n] = 1;
                q.push(n);
            } 
        }
        
    }
    for(int i = 0; i < N; i++) {
        if(visited[i] == 0) return false;
    }
    return true;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;
    N = n;
    
    for(vector<int> e : path) {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    for(vector<int> e : order) {
        if(e[1] == 0) return false;
        hash_m[e[1]] = e[0];
    }
    
    answer = bfs(0);
    
    
    
    return answer;
}