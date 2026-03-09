#include <iostream>

using namespace std;

int A, B;

int main() {
    cin >> A >> B;

    int temp = B;
    int count = 0;
    while(1) {
        if(A == temp) break;
        else if(A > temp) {
            count = -1;
            cout << count;
            exit(0);
            break;
        } else {
            int first = temp % 10;
            if(first == 1) {
                temp = temp / 10;
                count++;
            } else if(first % 2 == 1) {
                count = -1;
                cout << count;
            exit(0);
                break;
            } else {
                temp = temp / 2;
                count++;
            }
        }
    }
    
    cout << count + 1;
}