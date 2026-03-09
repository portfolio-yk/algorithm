#include <iostream>
#include <vector>

using namespace std;

int T;
int N, M, K;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };


bool dfs(vector<vector<int>>& field, int x, int y) {
    if(x < 0 || x > M - 1 || y < 0 || y > N - 1){
        return false;
    }

    if(field[y][x] == 1) {
        field[y][x] += 1;
        
        for(int i = 0; i < 4; i++) {
            dfs(field, x + dx[i], y + dy[i]);
        }
        
        return true;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    
    vector<int> answer;
    for(int tc = 0; tc < T; tc++){
        cin >> M >> N >> K;
        vector<vector<int>> field(N, vector<int>(M, 0));

        for(int i = 0; i < K; i++) {
            int x, y;
            cin >> x >> y;
            field[y][x] = 1;
        }

        int count = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(dfs(field, j, i)){
                    count += 1;
                }
            }
        }
        answer.push_back(count);
    }

    for(int a : answer){
        cout << a << "\n";
    }
}