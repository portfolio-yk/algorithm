#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
vector<string> s_list;
vector<pair<int, int>> s_range_list;
unordered_map<string, int> s_map;
unordered_map<string, int> all_s_map;
vector<int> visited;

int solution(string message, vector<vector<int>> spoiler_ranges) {
    int answer = 0;
    
    string s;
    int prev = 0;
    message.push_back(' ');
    for(int i = 0; i < message.size(); i++) {
        if(message[i] == ' ') {
            s_list.push_back(s);
            s_range_list.push_back({prev, i - 1});
            visited.push_back(0);
            all_s_map[s]++;
            s.clear();
            prev = i + 1;
        } else {
            s.push_back(message[i]);
        }
    }

    
    for(int i = 0; i < s_range_list.size(); i++) {
        pair<int, int> a = s_range_list[i];
        int f = 0;
        for(vector<int> r : spoiler_ranges) {
            if((r[0] >= a.first && r[0] <= a.second) || (r[0] < a.first && r[1] > a.second) || (r[1] >= a.first && r[1] <= a.second)) {
                if(visited[i] == 0) {
                    visited[i] = 1;
                    s_map[s_list[i]]++;      
                }
                
            }
            
        }
    }

    for (int i = 0; i < (int)s_list.size(); i++) {
        if (visited[i] == 0) continue;  // 스포 안 걸친 단어
        if (all_s_map[s_list[i]] - s_map[s_list[i]] == 0) {
            answer++;
            s_map[s_list[i]]--;
        }
    }
    
    return answer;
}