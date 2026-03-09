#include <iostream>
using namespace std; 

int money_list[6] = {500, 100, 50, 10, 5, 1};

int main() {
    int money;
    cin >> money;
    int change = 1000 - money;
    int count = 0;
    for(int i = 0; i < 6; i++) {
        int share = change / money_list[i];
        count += share;

        int left = change % money_list[i];
        change = left;
        if(left == 0) {
            break;
        }
    }

    cout << count;
}