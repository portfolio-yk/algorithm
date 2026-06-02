#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    
    vector<int> stack;
    
    set<int> set_list[505];
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ',') continue;
        
        if(s[i] == '{') {
            stack.push_back(-1);
        } else if(s[i] == '}') {
            int c = 0;
            set<int> n_list;
            while(stack.back() != -1) {
                int ch = stack.back();
                //cout << ch << "\n";
                stack.pop_back();
                c++;
                if(ch != ',') {
                    n_list.insert(ch);
                }
            }
            stack.pop_back(); 
            set_list[c] = n_list;
        } else {
            string num_s;
            while(s[i] != ',' && s[i] != '}') {
                num_s.push_back(s[i]);
                i++;
            }
            i--;
            // cout << num_s << "\n";
            stack.push_back(stoi(num_s));
        }
    }
    
    // [[2], [2, 1], [2, 1, 3], [2, 1, 3, 4]]
    
    
    for(int i = 0; i < 505; i++) {
        // for(int a : set_list[i]) 
        // {
        //     cout << a << " ";   
        // }
        // cout << "\n";
        for(int n : answer) {
            set_list[i].erase(n);    
        }
        for(int a : set_list[i]) 
        {
            answer.push_back(a);    
        }
        
    }
    
    return answer;
}