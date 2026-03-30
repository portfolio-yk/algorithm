#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;

    while(T--) {
        int N;
        int sticker[2][100005];
        int dp[2][100005];
        cin >> N;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < N; j++) {
                int num;
                cin >> num;
                sticker[i][j] = num;
            }
        }

        dp[0][0] = 0;
        dp[1][0] = 0;
        dp[0][1] = sticker[0][0];
        dp[1][1] = sticker[1][0];

        for(int i = 1; i < N; i++) {
            dp[0][i + 1] = sticker[0][i] + max(dp[1][i], dp[1][i - 1]);
            dp[1][i + 1] = sticker[1][i] + max(dp[0][i], dp[0][i - 1]);
        }

        cout << max(dp[0][N], dp[1][N]) << "\n";
    }
}