#include <iostream>
#include <vector>
using namespace std; 

vector<int> path;
vector<int> s;
int N;
pair<int, int> ingredients[11];
vector<vector<int>> com;
int b[11];

void dfs(int start, int length) {
    if(path.size() == length) {
        com.push_back(path);
        return;
    }

    for(int i = start; i < N; i++) {
        path.push_back(i);
        dfs(i + 1, length);
        path.pop_back();
    }
}

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        int S, T;
        cin >> S >> T;

        ingredients[i] = { S, T };
        b[i] = i;
    }
    for(int i = 0; i < N; i++) { 
        dfs(0, i + 1);
    }
    int min_sum = int(1e9);
    for(vector<int> a1 : com) {
        int ss = 1;
        int tt = 0;
        for(int a2 : a1) {
            pair<int, int> st = ingredients[a2];
            ss *= st.first;
            tt += st.second;
        }
        min_sum = min(min_sum, abs(ss - tt));
    }

    cout << min_sum;
}