#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 25
#define SHARK 9
using namespace std;

int board[MAX][MAX];
int viisited[MAX][MAX];

int N;

typedef struct Node {
    int d;
    int x;
    int y;
} Node;

bool compare(const Node& n1, const Node& n2) {
    if(n1.d != n2.d) return n1.d < n2.d;

    if(n1.x != n2.x) return n1.x < n2.x;

    return n1.y < n2.y;
}

int shark_size = 2;
int fish_count = 0;
pair<int, int> shark_pos;

int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { 1, 0, 0, -1 };

vector<Node> bfs(int start_x, int start_y) {
    vector<Node> eatable_fish;

    queue<pair<int, int>> q;
    q.push({ start_x, start_y });

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

            if(viisited[nx][ny] == 0 && board[nx][ny] <= shark_size) {
                viisited[nx][ny] = viisited[x][y] + 1;
                q.push({ nx, ny });
                if(board[nx][ny] > 0 && board[nx][ny] < 7 && board[nx][ny] < shark_size) {
                    eatable_fish.push_back({ viisited[nx][ny] , nx, ny });
                }
            }
        }
    }
    return eatable_fish;
}

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
            if(board[i][j] == SHARK) shark_pos = { i, j };
        }
    }


    int ans = 0;
    vector<Node> fish_list;
    //먹을 수 있는 애
    fish_list = bfs(shark_pos.first, shark_pos.second);

    while(fish_list.size()) {
        sort(fish_list.begin(), fish_list.end(), compare);
        Node n = fish_list[0];
        int x = n.x;
        int y = n.y;

        board[x][y] = 0;
        ans += viisited[x][y];
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                viisited[i][j] = 0;
            }
        }
        

        fish_count++;
        if(shark_size <= fish_count) {
            shark_size++;
            fish_count = 0;
        }
        
        
        board[shark_pos.first][shark_pos.second] = 0;
        board[x][y] = SHARK; 
        shark_pos = { x, y };
        
        fish_list = bfs(shark_pos.first, shark_pos.second);
    }

    cout << ans;
}