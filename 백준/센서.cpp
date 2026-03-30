#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int sensors[10005];
int sensors_diff[10005];

int main() {
    cin >> N;
    cin >> K;
    
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        sensors[i] = num;
    }

    sort(sensors, sensors + N);

    for(int i = 1; i < N; i++) {
        sensors_diff[i - 1] = sensors[i] - sensors[i - 1];
    }

    sort(sensors_diff, sensors_diff + N - 1, greater<>());

    int ans = 0;

    for(int i = K - 1; i < N - 1; i++) {
        ans += sensors_diff[i];
    }

    cout << ans;
}