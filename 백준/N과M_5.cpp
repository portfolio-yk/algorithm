#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> path = {};
bool visited[100];


int dfs(int end, vector<int> numbers, vector<int> path) {
    if(path.size() == end) {
        for(int i = 0; i < end; i++) {
            cout << path[i] << " ";
        } 
        cout << "\n";
        return 0;
    }

    for(int i = 0; i < N; i++) {
        if(!visited[i]){
            visited[i] = true;
            path.push_back(numbers[i]);
            dfs(end, numbers, path);
            path.pop_back();
            visited[i] = false;
        }
    }
    return 0;
}

int main() {
    
    cin >> N >> M;

    vector<int> numbers = {};

    for(int i = 0; i < N; i++) {
        int n;
        cin >> n;
        numbers.push_back(n);
    }

    sort(numbers.begin(), numbers.end());

    dfs(M, numbers, path);
    return 0;
}