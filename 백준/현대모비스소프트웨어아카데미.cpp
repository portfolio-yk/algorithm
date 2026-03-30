#include <iostream>
#include <algorithm>
using namespace std; 

int N, M;

int available[100005];

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        available[i] = num;
    }

    sort(available, available + N);

    int r = N - 1;
    int l = 0;
    int c = 0;

    while(l < r) {
        if(available[l] + available[r] >= M) {
            c++;
            r--;
            l++;
        } else {
            l++;
        }
    }

    cout << c;
}