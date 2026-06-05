#include <string>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

int solution(vector<int> players, int m, int k) {
    int answer = 0;
    deque<int> server;
    
    for(int i = 0; i < players.size(); i++) {
        while(server.size() && server.front() == 0) {
            server.pop_front();
        }
        
        int player = players[i];
        
        if(player >= m) {
            int required_server = player / m;
            
            if(required_server > server.size()) {
                int install_c = required_server - server.size();
                
                for(int j = 0; j < install_c; j++) {
                    server.push_back(k);
                    answer++;
                }
            }
        }
        
        
        for(int j = 0; j < server.size(); j++) {
            server[j]--;
        }
    }
    
    
    return answer;
}