#include <iostream>

using namespace std; 

int main() {
    int money;
    cin >> money;
    if(money == 1 || money == 3) {
        cout << -1;
        exit(0);
    }
    int count = 0;
    int share = money / 5;
    count += share;
    int left = money % 5;

    if(left % 2 == 0) {
        count += left / 2;
    } else {
        left = left + 5;
        count -= 1;
        count += left / 2;
    }

    cout << count;
} 