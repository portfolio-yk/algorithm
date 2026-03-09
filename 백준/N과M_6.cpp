#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 9

using namespace std;


int N, M;
vector<int> path = {};
vector<int> numbers = {};

int dfs(int start) {
    if(path.size() == M) {
        for(int i = 0; i < M; i++) {
            cout << path[i] << " ";
        } 
        cout << "\n";
        return 0;
    }

    for(int i = start; i < N; i++) {
        path.push_back(numbers[i]);
        dfs(i + 1);
        path.pop_back();
    }
    return 0;
}

int main() {
    
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        int n;
        cin >> n;
        numbers.push_back(n);
    }

    sort(numbers.begin(), numbers.end());

    dfs(0);
    return 0;
}