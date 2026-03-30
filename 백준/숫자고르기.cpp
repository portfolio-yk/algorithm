#include <iostream>
#include <vector>
#define MAX 101
using namespace std;

int board[MAX];
int visited[MAX];
int N;
vector<int> ans;

vector<int> find(int num) {
    vector<int> t;
    for(int i = 1; i <= N; i++) {
        if(board[i] == num) t.push_back(i);
    }
    return t;
}

int dfs(int start) {
    if(visited[start]) {
        ans.push_back(start);
        return 1;
    }

    visited[start] = 1;

    vector<int> re = find(start);
    if(re.size() == 0) {
        return -1;
    }

    for(int e : re) {
        dfs(e);
    }

    return 1;
}

int main() {
    cin >> N;

    for(int i = 1; i <= N; i++) {
        int num;
        cin >> num; 
        board[i] = num;
    }

    for(int i = 1; i <= N; i++) {
        dfs(i);
        for(int i = 1; i <= N; i++) {
            visited[i] = 0;
        }
    }
    
    cout << ans.size() << "\n";
    for(int a : ans) {
        cout << a << "\n";
    }
}

// 1 2 3 4 5 6 7
// 3 1 7 2 5 4 6