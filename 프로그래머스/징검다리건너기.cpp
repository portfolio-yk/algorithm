#include <string>
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    int m = 0;
    for(int stone : stones) {
        if(m < stone) {
            m = stone;
        }
    }
    
    int l = 0;
    int r = m;
    
    while(1) {
        if(l > r) break;
        int mid = (l + r) / 2;
        
        int m_seq = 0;
        int seq = 0;
        for(int i = 0; i < stones.size(); i++) {
            int stone = stones[i];
            if(stone - mid <= 0) {
                seq++;
                m_seq = max(m_seq, seq);
            } else {
                seq = 0;
            }
        }
        
        if(m_seq >= k) {
            r = mid - 1;
        } else {
            answer = max(answer, mid);
            l = mid + 1;
        }
    }
    
    return answer + 1;
}