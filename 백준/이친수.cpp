#include <iostream>
using namespace std;
#define MAX 92
int N;

long long dp[MAX];

int main() {
    cin >> N;

    dp[1] = 1;
    dp[2] = 1;

    for(int i = 3; i <= N; i++) {
        for(int j = i - 2; j >= 1; j--) {
            dp[i] += dp[j];
        }
        dp[i] += 1;
    }

    cout << dp[N];
}