#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    int total = unordered_set<string>(gems.begin(), gems.end()).size();
    unordered_map<string, int> gems_c;

    int l = 0;
    int ansL = 0, ansR = gems.size() - 1;  // answer 대신 변수로 관리

    for (int r = 0; r < gems.size(); r++) {
        gems_c[gems[r]]++;

        // 모든 보석 포함 시 왼쪽 줄이기
        while (gems_c[gems[l]] > 1) {
            gems_c[gems[l]]--;
            l++;
        }

        if (gems_c.size() == total) {
            if (r - l < ansR - ansL) {
                ansL = l;
                ansR = r;
            }
        }
    }

    return {ansL + 1, ansR + 1};
}