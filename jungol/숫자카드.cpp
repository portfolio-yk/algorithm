#include <iostream>
#include <string>
#include <cstring>
using namespace std;

string s;
int N;

int dp[41];

int get_num(char n1, char n2) {
    return (n1 - '0') * 10 + (n2 - '0');
}

int main() {
    cin >> s;
    N = s.size();

    if(N == 1) {
        cout << 1;
        exit(0); 
    }

    int num = get_num(s[0], s[1]);
    dp[1] = 1;
    dp[2] = 2;
    if(num > 34 || num < 10) dp[2] = dp[1];
    if(num % 10 == 0) dp[2] = 1;

    for(int i = 3; i <= N; i++) {
        num = get_num(s[i - 2], s[i - 1]);
        if(s[i - 1] == '0' && num > 34  || num == 0) {
            cout << 0;
            exit(0);
        }

        dp[i] = dp[i - 1] + dp[i - 2];
        if(num > 34 || num < 10) dp[i] = dp[i - 1];
        if(num % 10 == 0) dp[i] = dp[i - 2];
    }

    cout << dp[N];    
}