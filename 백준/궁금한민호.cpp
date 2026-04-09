#include <iostream>
#define INF 1e5
using namespace std;


int N;
int d[25][25];
int origin[25][25];

int main() {
    cin >> N;
    int ans = 0;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> d[i][j];
            origin[i][j] = d[i][j];
        }
    }

    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(i == k || i == j || j == k) continue;

                if(d[i][j] > d[i][k] + d[k][j]) {
                    ans = -1;
                    break;
                }

                if(d[i][j] == d[i][k] + d[k][j]) {
                    origin[i][j] = INF;
                }
            }
        }
    }
    if(ans == -1) {
        cout << ans;
    } else {
        ans = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1 + i; j <= N; j++) {
                if(origin[i][j] != INF) {
                    ans += origin[i][j];
                }
            }    
        }
        cout << ans;
    }
    
}