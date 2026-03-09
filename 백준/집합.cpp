#include <iostream>
#include <set>
#include <string>

using namespace std;

set<int> s; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int M;
    cin >> M;

    while(M--) {
        string event;
        int num;

        cin >> event;
        if(event != "all" and event != "empty") {
            cin >> num;
        }

        if(event == "add") {
            s.insert(num);
        } else if(event == "check") {
            if(s.find(num) != s.end()) {
                cout << "1" << "\n";
            } else {
                cout << "0" << "\n";
            }
        } else if(event == "remove") {
            s.erase(num);
        } else if(event == "toggle") {
            if(s.find(num) != s.end()) {
                s.erase(num);
            } else {
                s.insert(num);
            }
        } else if(event == "all") {
            for(int i = 1; i <= 20; i++) {
                s.insert(i);
            }
        } else if(event == "empty") {
            s.clear();
        }
    }


    return 0;
}

