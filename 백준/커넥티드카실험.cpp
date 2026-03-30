#include <iostream>
#include <queue>
#include <vector>
using namespace std; 

int N, S;

vector<int> position;
vector<int> fuel;
vector<bool> visited;
queue<int> q;

int main() {
    ios_base :: sync_with_stdio(false);

    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> S;

    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        position.push_back(num);
        visited.push_back(false);
    }

    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        fuel.push_back(num);
    }

    q.push(S);
    visited[S - 1] = true;
    int r = S - 1;
    int l = S - 1;

    while(q.size()) {
        int car_num = q.front();
        q.pop();

        int x = position[car_num - 1];
        int h = fuel[car_num - 1];

        while(r + 1 < N && position[r + 1] <= x + h) {
            r++;
            if(!visited[r]) {
                visited[r] = true;
                q.push(r + 1);
            }
        } 

        while(l - 1 > -1 && position[l - 1] >= x - h) {
            l--;
            if(!visited[l]) {
                visited[l] = true;
                q.push(l + 1);
            }
        } 
    }

    for(int i = 0; i < N; i++) {
        if(visited[i]) {
            cout << i + 1 << " ";
        }
    }
}