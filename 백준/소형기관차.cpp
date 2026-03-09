#include <iostream>
#define MAX 50001

using namespace std;
int N;
int train[MAX];
int parr[MAX];
int dp[3][MAX];
int length; 

int main() {
    cin >> N;    
    for(int i = 1; i <= N; i++) {
        cin >> train[i];
    }
    cin >> length;

    for(int i = 1; i <= N; i++) {
        parr[i] = parr[i - 1] + train[i];
    }

    for(int i = 1; i <= 3; i++) {
        for(int j = i * length; j <= N; j++) {
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - length] + parr[j] - parr[j - length]);
        }
    }

    cout << dp[3][N];
}