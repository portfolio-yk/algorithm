#include <iostream>
#include <string>
#include <vector>

using namespace std;

string s1;
string s2;


int main() {
    cin >> s1;
    cin >> s2;


    int len = s2.size();
    string stack_s;

    string cmp_s2;
    while(s2.size()) {
        char s = s2.back();
        s2.pop_back();
        cmp_s2.push_back(s);
    }

    for(int i = 0; i < s1.size(); i++) {
        stack_s.push_back(s1[i]);

        if(stack_s.size() >= len) {
            string cmp_s;
            for(int j = 0; j < len; j++) {
                char a = stack_s.back();
                stack_s.pop_back();
                cmp_s.push_back(a);
            }
            if(cmp_s != cmp_s2) {
                for(int j = 0; j < len; j++) {
                    char a = cmp_s.back();
                    cmp_s.pop_back();
                    stack_s.push_back(a);
                }
            }
        }
    }
    if(stack_s.empty()) cout << "FRULA";
    else cout << stack_s;
}