#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string str;
    int T, K;
    cin >> T;

    for(int tc = 0; tc < T; tc++) {
        cin >> str;
    cin >> K;

    vector<int> alpha[26];

    for(int i = 0; i < str.size(); i++) {
        alpha[str[i] - 'a'].push_back(i);
    }

    int min_temp = 100000;
    int max_temp = -1;

    for(int i = 0; i < 26; i++) {
        if(alpha[i].size() >= K) {
            for(int j =0; j < alpha[i].size() - (K - 1); j++) {
                min_temp = min(min_temp, alpha[i][j + K - 1] - alpha[i][j] + 1);
                max_temp = max(max_temp, alpha[i][j + K - 1] - alpha[i][j] + 1);
            }
        }
    }
    if(min_temp == 100000 || max_temp == -1) {
        cout << "-1" << "\n";
        continue;
    }
    cout << min_temp << " " << max_temp << "\n";
    }
}