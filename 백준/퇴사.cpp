#include <iostream>
using namespace std;

int N;

int dp[15];
int dp_time[15];
int dp_point[15];

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        int t, p;
        cin >> t >> p;

        dp_time[i] = t;
        dp_point[i] = p;
    }
    int max_money = 0;
    for(int i = 0; i <= N; i++) {
        int time = dp_time[i] + i;
        dp[i] = max(max_money, dp[i]); 
        if(time <= N) {
            dp[time] = max(dp[time], dp[i] + dp_point[i]);
        }
        max_money = dp[i]; 
    }
    cout << max_money;
}