#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


bool compare(pair<string, int>& a, pair<string, int>& b) {
    // 1순위 조건: Value(가격)가 다르면 가격이 큰 순서대로 (내림차순)
    if (a.second != b.second) {
        return a.second > b.second; 
    }
    
    // 2순위 조건: 가격이 같다면 이름(Key)의 길이가 긴 순서대로
    if (a.first.length() != b.first.length()) {
        return a.first.length() > b.first.length();
    }

    // 3순위 조건: 길이까지 같다면 사전 순서대로
    return a.first < b.first;
}

int main() {
    // 1. C 동기화 해제
    ios_base::sync_with_stdio(false);
    // 2. 입력과 출력의 묶음 해제
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    map<string, int> word_map;

    //N
    for(int i = 0; i < N; i++) {
        string word;
        cin >> word;
        if(word.size() >= M) {
            //N
            if(word_map.count(word) > 0) {
                word_map[word] += 1;
            } else {
                word_map[word] = 1;
            }
        }
    }

    vector<pair<string, int>> word_list(word_map.begin(), word_map.end());

    sort(word_list.begin(), word_list.end(), compare);

    for(auto const& word : word_list) {
        cout << word.first << "\n";
    }
}