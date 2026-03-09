// 1 -> 1  (1)
// 2 -> 1 + 1, 2(2)
// 3 -> 1 + 2   , 3(3)
// 4 -> 1 + 3, 2 + 2 ()
// 5 -> 1 + 1 + 1 + 1 + 1, 1 + 1 + 1 + 2, 1 + 2 + 2, 1 + 1 + 3, 2 + 3
// 6 -> 1 + 5, 2 + 4, 3 + 3, 

#include <iostream>
#define MAX 10001

using namespace std;

int dp[MAX][3] = { {1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, {} };

int main() {
    int T;
    cin >> T;
    for(int tc = 0; tc < T; tc++) {
        int N;
        cin >> N; 
    
        for(int i = 3; i < N; i++) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 2][0] + dp[i - 2][1];
            dp[i][2] = dp[i - 3][0] + dp[i - 3][1] + dp[i - 3][2];
        }
        cout << dp[N - 1][0] + dp[N - 1][1] + dp[N - 1][2] << "\n";
    }

}