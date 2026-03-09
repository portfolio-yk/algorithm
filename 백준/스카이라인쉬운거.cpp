#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> stack_floor;

int main() {
    int T;
    cin >> T;

    int x, y;
    cin >> x >> y;
    stack_floor.push_back({x, y});
    int count = 0;
    for(int i = 0; i < T - 1; i++) {

        int x, y;
        cin >> x >> y;

        while(stack_floor.size()) {
            pair<int, int> xy = stack_floor.back();

            if(y < xy.second) {
                stack_floor.pop_back();
                count += 1;
            } else if (y == xy.second) {
                stack_floor.pop_back();
            } else {
                break;
            }
        }
        
        if(y != 0) {
            stack_floor.push_back({x, y});
        }
    }
    for(pair<int, int> xy : stack_floor) {
        if(xy.second != 0) {
            count += 1;
        }
    }
    cout << count;
}