#include <iostream>
using namespace std;

int N, M; 
int dp[41];
int seats[41];

int main() {
    cin >> N;
    cin >> M;
    

    for(int i = 1; i <= M; i++) {
        int num;
        cin >> num;
        seats[num] = 1;
    }

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    
    if(seats[1] != 0) {
        if(seats[2] != 0 || seats[3] != 0) {
            dp[1] = 1; dp[2] = 1; dp[3] = 1;
        } else {
            dp[1] = 1; dp[2] = 2; dp[3] = 2;
        }
    } else if(seats[2] != 0) {
        dp[1] = 1; dp[2] = 1; dp[3] = 1;
    } else if(seats[3] != 0) {
        dp[1] = 1; dp[2] = 2; dp[3] = 2;
    }


    for(int i = 4; i <= N; i++) {
        if(seats[i] != 0) {
            dp[i] = dp[i - 1];
        } else {
            if(seats[i - 1] != 0) {
                dp[i] = dp[i - 1];
            } else if(seats[i - 2] != 0){
                dp[i] = dp[i - 2] * 2;
            } else {
                dp[i] = dp[i - 2] * 2 + dp[i - 3];
            }
        }
    }
    // for(int i = 1; i <= N; i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << "\n";
    cout << dp[N];
}