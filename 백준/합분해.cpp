//! 시간 초과
// #include <iostream>
// #include <vector>

// #define MAX 201
// #define r int(1e9)
// using namespace std;

// int N, M;

// int numbers[MAX];
// int visited[MAX];
// vector<int> path;

// int c = 0;

// void dfs(int start) {
//     if(path.size() == M) {
//         int s = 0;
//         for(int i : path) {
//             s += i;
//         }
//         if(s == N) {
//             c += 1;
//         }
//         return;
//     }

//     for(int i = start; i <= N; i++) {
//         path.push_back(i);
//         dfs(i);
//         path.pop_back(); 
//     }
// }

// int main() {
//     cin >> N >> M;

//     for(int i = 0; i <= N; i++) {
//         numbers[i] = i;
//     }

//     dfs(0);
//     cout << c % r;
// }


#include <iostream>
#define r int(1e9)
using namespace std;

long long dp[201][201];

int main() {
    int N, K;
    cin >> N >> K;

    for(int i = 0; i <= N; i++) {
        dp[1][i] = 1;
    }
    
    for(int i = 1; i <= K; i++) {
        for(int j = 0; j <= N; j++) {
            for(int k = 0; k <= j; k++) {
                dp[i][j] += dp[i - 1][k] % r;
            }
        }
    }

    cout << dp[K][N] % r;
}