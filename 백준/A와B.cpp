#include <iostream>
#include <string>
#include <queue>

using namespace std;

string S;
string T;

int main() {
    cin >> S;
    cin >> T;
    
    while(1) {
        if(S.size() == T.size()) {
            if(S == T) {
                cout << 1;
            } else {
                cout << 0;
            }
            break;
        }

        if(T.back() == 'A') {
            T.pop_back();
        } else {
            T.pop_back();
            queue<char> temp;
            while(T.size()) {
                temp.push(T.back());
                T.pop_back();
            }
            while(temp.size()) {
                T.push_back(temp.front());
                temp.pop();
            }
        }
    }
}