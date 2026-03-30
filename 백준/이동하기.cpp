//!시간초과
// #include <iostream>
// using namespace std;

// int N, M;

// int dp[1001][1001];
// int board[1001][1001];


// void dfs(int r, int c, int prev) {
//     if(dp[r][c] >= board[r][c] + prev) {
//         return;
//     }

//     if(r > N - 1 || c > M - 1) return;

    
//     dp[r][c] = board[r][c] + prev;

//     dfs(r + 1, c, dp[r][c]);
//     dfs(r, c + 1, dp[r][c]);
//     dfs(r + 1, c + 1, dp[r][c]);
// }

// int main() {
//     cin >> N >> M;

//     for(int i = 0; i < N; i++) {
//         for(int j = 0; j < M; j++) {
//             int num;
//             cin >> num;
//             board[i][j] = num;
//         }
//     }

//     dfs(1, 0, board[0][0]);
//     dfs(0, 1, board[0][0]);
//     dfs(1, 1, board[0][0]);

//     cout << dp[N - 1][M - 1];
// }


#include <iostream>
using namespace std;

int N, M;

int dp[1001][1001];
int board[1001][1001];


int main() {
    cin >> N >> M;

    for(int i = 1; i < N + 1; i++) {
        for(int j = 1; j < M + 1; j++) {
            int num;
            cin >> num;
            dp[i][j] = num;
        }
    }


    for(int i = 1; i < N + 1; i++) {
        for(int j = 1; j < M + 1; j++) {
            int a = max(dp[i][j - 1], dp[i - 1][j]);
            int m = max(a, dp[i - 1][j - 1]);

            dp[i][j] = dp[i][j] + m;
        }
    }

    cout << dp[N][M];
}