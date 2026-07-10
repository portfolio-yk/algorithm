#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance);
    
    int l = 0;
    int r = distance;
    
    while(l <= r) {
        int c = 0;
        int mid = (l + r) / 2;
        int prev = 0;
        for(int i = 0; i < rocks.size(); i++) {
            int diff = rocks[i] - prev;
            if(diff < mid) {
                c++;
            } else {
                prev = rocks[i];
            }
        }
        
        if(c <= n) {
            answer = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    } 
    
    
    
    return answer;
}