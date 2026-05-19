#include <iostream>

using namespace std;

int numbers[10000];

int main() {
    int N;
    int total;
    
    cin >> N;

    int max_money = 0;

    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        numbers[i] = num;

        if(max_money < num) {
            max_money = num;
        }
    }

    cin >> total;

    int left = 0;
    int right = max_money;
    int result = max_money;

    if(total > max_money * N) {
        cout << max_money;
        exit(0);
    }

    while(left <= right) {  
        int mid = (left + right) / 2;
        
        int t = total;
        for(int i = 0; i < N; i++) {
            if(mid > numbers[i]) {
                t -= numbers[i];
            } else {
                t -= mid;
            }
        }
        if(t < 0) {
            right = mid - 1;
        } else {
            result = mid;
            left = mid + 1;
        }
    }
    cout << result;
}