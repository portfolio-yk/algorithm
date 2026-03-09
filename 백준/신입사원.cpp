#include <iostream>
#include <algorithm>
#define MAX 100000
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int N;
        pair<int, int> applyer[MAX];
        cin >> N; 
        for(int i = 0; i < N; i++) {
            int a, b;
            cin >> a >> b;
            applyer[i] = { a, b };
        }
        sort(applyer, applyer + N);
    
        int c = 1;
        int worst = applyer[0].second;
        for(int i = 1; i < N; i++) {
            if(applyer[i].second < worst) {
                worst = applyer[i].second;
                c++;
            }
        }
        

    
        cout << c << "\n";
    }
}

