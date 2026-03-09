#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;

vector<string> s;
 
int main() {
    cin >> N;
    int len = 0;
    for(int i = 0; i < N; i++) {
        string a;
        cin >> a;
        len = a.length();
        s.push_back(a);
    }
    
    string ans;

    for(int i = 0; i < len; i++) {
        char c = s.front()[i];
        int flag = 1;
        for(string f: s) {
            if(c != f[i]) {
                ans.push_back('?');
                flag = 0;
                break;
            }
        }
        if(flag == 1) {
            ans.push_back(c);
        }
    }

    cout << ans;
}