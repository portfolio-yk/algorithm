#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> signals) {
    int answer = 0;
    
    int s = 1;
    
    for(vector<int> signal : signals) {
        int signal_s = signal[0] + signal[1] + signal[2];
        s *= signal_s;
    }
    
    for(int i = 1; i <= s; i++) {
        int is_ok = 1;
        for(vector<int> signal : signals) {
            int signal_s = signal[0] + signal[1] + signal[2];
            int start = i;
            
            if(!(i % signal_s >= signal[0] + 1
                && i % signal_s <= signal[0] + signal[1])) {
                is_ok = 0;
            }
        }
        if(is_ok) {
            answer = i;
            break;
        }
    }
    
    return answer == 0 ? -1 : answer;
}