#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    queue<char> q;

    string s;
    cin >> s;

    sort(s.begin(), s.end());

    for(char c : s) {
        q.push(c);
    }
    int l = 0;
    int r = s.size() - 1;
    char answer[55];
    int count = 0;
    while (q.size() > 1)
    {   
        if(count > s.size()) {
            cout << "I'm Sorry Hansoo";
            exit(0);
            break;
        }
        char first = q.front();
        q.pop();
        char second = q.front();
        if(first == second) {
            q.pop();
            answer[l] = first;
            answer[r] = second;
            l++;
            r--;
            count = 0;
        } else {
            count++;
            q.push(first);
        }
    }

    if(q.size()) {
        answer[s.size() / 2] = q.front();
    }
    
    for(int i = 0; i < s.size(); i++) {
        cout << answer[i];
    }
    
}