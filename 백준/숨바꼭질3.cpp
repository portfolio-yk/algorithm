#include <iostream>
#include <queue>

using namespace std;

#define MAX 100001

int location[MAX] = { 0 };
int visited[MAX] = { 0 };

int N;
int K;

queue<int> q;

int dx[3] = {0, -1, 1};

void bfs() {
    q.push(N);

    while(q.size()) {
        int x = q.front();
        q.pop();
        visited[x] = 1;
        if(x == K) {
            cout << location[x];
            break;
        }

        for(int i = 0; i < 3; i++) {
            int nx;
            if(dx[i] == 0) {
                nx = x * 2;
            } else {
                nx = x + dx[i];
            }

            if(nx < 0 || nx > MAX - 1) {
                continue;
            }

            if(visited[nx] == 0) {
                visited[nx] = 1;
                if(dx[i] != 0) {
                    location[nx] = location[x] + 1;
                } else {
                    location[nx] = location[x];
                }
                q.push(nx);
            }
        }

    }
}

int main() {
    cin >> N >> K;

    bfs();
}