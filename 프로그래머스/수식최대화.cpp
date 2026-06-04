#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

long long oper(long long num1, long long num2, long long oper) {
    if(oper == -1) {
        return num1 * num2;
    } else if(oper == -2) {
        return num1 + num2;
    } else {
        return num1 - num2;
    }
}

long long solution(string expression) {
    long long answer = 0;
    vector<pair<int, long long>> oper_q_back;
    vector<pair<int, long long>> blank_s;
    unordered_map<char, int> oper_map;
    oper_map['*'] = -1;
    oper_map['+'] = -2;
    oper_map['-'] = -3;
    
    string num_s;
    
    
    for(int i = 0; i < expression.size(); i++) 
    {
        char ch = expression[i];
        if(ch != '-' && ch != '+' && ch != '*') {
            num_s.push_back(ch);
        } else {
            oper_q_back.push_back({1, stoi(num_s)});
            oper_q_back.push_back({0, oper_map[ch]});
            num_s.clear();
        } 
    }
    oper_q_back.push_back({1, stoi(num_s)});
    
    int priority[6][3] = {{ -1, -2, -3 }, { -3, -2, -1 }, { -3, -1, -2 }, { -2 , -1, -3 }, { -2, -3, -1 } , { -1, -3, -2 }};
    
    for(int i = 0; i < 6; i++) {
        queue<pair<int, long long>> oper_q;
        
        for(pair<int,long long> d : oper_q_back) {
            oper_q.push(d);
        }
        
        for(int j = 0; j < 3; j++) {
            while(oper_q.size()) {
                pair<int,long long> p = oper_q.front();
                oper_q.pop();

                if(p.first == 0 && p.second == priority[i][j]) {
                    long long res = oper(blank_s.back().second, oper_q.front().second, p.second);
                    blank_s.pop_back();
                    oper_q.pop();
                    blank_s.push_back({1, res});
                } else {
                    blank_s.push_back(p);
                }

            }
            for(pair<int,long long> a : blank_s) {
                oper_q.push(a);
            }
            blank_s.clear();
        }
        if(answer < abs(oper_q.front().second)) {
            answer = abs(oper_q.front().second);
        }
    }
     
    return answer;
}