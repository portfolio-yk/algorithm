#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N;

long long start_x, start_y, end_x, end_y;

vector<long long> distance_list;

int main() {
    cin >> N;

    cin >> start_x >> start_y >> end_x >> end_y;

    for(int i = 0; i < N; i++) {
        int c;
        cin >> c;
        pair<long long, long long> pos = { start_x, start_y };
        long long d = 0;
        while(c--) {
            long long x, y;
            cin >> x >> y;

            d += abs(pos.first - x) + abs(pos.second - y);
            pos = { x, y };
        }
        d += abs(pos.first - end_x) + abs(pos.second - end_y);

        distance_list.push_back(d);
    }

    long long ans = distance_list[0];
    int num = 1; 
    
    // 0번째는 이미 ans에 넣었으니, 1번째부터 비교 (가독성 개선)
    for(int i = 1; i < distance_list.size(); i++) {
        if(ans > distance_list[i]) {
            ans = distance_list[i];
            num = i + 1; // 1번부터 시작하므로 인덱스 + 1
        }
    }

    cout << num;
}