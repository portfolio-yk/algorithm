#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int N, S; 
string DNA_string;
int A, C, G, T;
unordered_map<char, int> my_pw;

int main() {
    cin >> N >> S;
    cin >> DNA_string;
    cin >> A >> C >> G >> T;

    int left = 0;
    int right = S - 1;
    int ans = 0;

    my_pw['A'] = 0;
    my_pw['C'] = 0;
    my_pw['G'] = 0;
    my_pw['T'] = 0;

    for(int i = left; i <= right; i++) {
        my_pw[DNA_string[i]]++;
    }

    while(right < DNA_string.size()) {
        
        if(A <= my_pw['A'] && C <= my_pw['C'] && G <= my_pw['G'] && T <= my_pw['T']) {
            ans++;
        }
        
        my_pw[DNA_string[left]]--;
        left++;

        right++;
        my_pw[DNA_string[right]]++;
    } 

    cout << ans;
}