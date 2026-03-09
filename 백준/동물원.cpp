#include <iostream>
#define MAX 1000000
using namespace std;

long long dp[MAX][3] = { {1, 1, 1} };

int N;

int main() {
    cin >> N;

    for(int i = 1; i < N; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % 9901;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % 9901;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % 9901;
    }

    cout << (dp[N - 1][0] + dp[N - 1][1] + dp[N - 1][2]) % 9901;
}
