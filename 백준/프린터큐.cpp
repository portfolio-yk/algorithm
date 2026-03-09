#include <iostream>
#include <queue>

using namespace std;

int T, N, M;

queue<pair<int, int>> q;

bool search(queue<pair<int, int>> q_avg, int num) {
    while(q_avg.size()) {
        pair<int,int> next = q_avg.front();
        if(num < next.second) {
            return true;
        }
        q_avg.pop();
    }
    return false;
} 

int main() {
    cin >> T;
    while(T--) {
        cin >> N >> M;

        int target; 

        for(int i = 0; i < N; i++) {
            int num;
            cin >> num;
            q.push({ i, num });
        }   
        queue<pair<int, int>> answer;
        
        while(q.size()) {
        
            pair<int,int> num = q.front();
            q.pop();
            if(search(q, num.second)) {
                q.push(num);
            } else {
                answer.push(num);
            }
        }

        for(int i = 1; i <= N; i++) {
            pair<int, int> a = answer.front();
            answer.pop();
            if(a.first == M) {
                cout << i << "\n";
            }
        }
    }
}