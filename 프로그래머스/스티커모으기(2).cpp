#include <iostream>
#include <vector>
#define INF 100005
using namespace std;

int solution(vector<int> sticker)
{
    int answer =0;
    
    int dp1[INF];
    int dp2[INF];
    
    dp1[0] = sticker[0];
    dp1[1] = sticker[1];
    dp1[2] = sticker[0] + sticker[2];
    
    for(int i = 3; i < sticker.size() - 1; i++) {
        dp1[i] = max(sticker[i] + dp1[i - 2], sticker[i] + dp1[i - 3]);
    }
    
    int max_dp1 = 0;
    
    for(int i = 0; i < sticker.size(); i++) {
        if(dp1[i] > max_dp1) {
            max_dp1 = dp1[i];
        }
    }
    
    dp2[1] = sticker[1];
    dp2[2] = sticker[2];
    dp2[3] = sticker[1] + sticker[3];
    
    for(int i = 4; i < sticker.size(); i++) {
        dp2[i] = max(sticker[i] + dp2[i - 2], sticker[i] + dp2[i - 3]);
    }
    
    int max_dp2 = 0;
    
    for(int i = 0; i < sticker.size(); i++) {
        if(dp2[i] > max_dp2) {
            max_dp2 = dp2[i];
        }
    }


    return max(max_dp2, max_dp1);
}