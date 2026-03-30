#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, int> map;

int main() {
    string first, second;
    cin >> first;
    cin >> second;

    for(char c : first) {
        map[c] += 1;
    }
    int ans = 0;
    for(char c : second) {
        if(!(map.find(c) == map.end())) {
            if(map[c] != 0) {
                ans++;
                map[c]--;
            }
            
        }
    }
    cout << first.size() - ans + second.size() - ans;
}