#include <iostream>

using namespace std; 

int main() {
    long long S;
    cin >> S;
    int count = 0;
    int i = 1;
    while(1) {
        S = S - i;
        count += 1;
        if(S <= i) {
            break;
        }
        i++;
    }
    cout << count;
}