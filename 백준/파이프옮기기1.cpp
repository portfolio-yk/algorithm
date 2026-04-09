#include<iostream>
#define MAX 20
using namespace std;

int board[MAX][MAX];
int N;
int ans = 0;

void dfs(int start_x, int start_y, int end_x, int end_y) {
    //cout << start_x << " " << start_y << " " << end_x << " " << end_y << " c : " << ans <<"\n";
    if(start_x < 0 || start_x > N -1 || start_y < 0 || start_y > N - 1) return;

    if(board[start_x][start_y] == 1) return; 

    if(start_x == end_x + 1 && start_y == end_y + 1) {
        if(board[start_x - 1][start_y] == 1 || board[start_x][start_y - 1] == 1) {
            //cout << start_x << " " << start_y << " " << end_x << " " << end_y << "\n";
            return;
        }
    }

    if(start_x == N - 1 && start_y == N - 1) {
        ans++;
        return;
    }

    //가로
    if(start_x == end_x) {
        //오른쪽
        dfs(start_x, start_y + 1, end_x, end_y + 1);
        //으론쪽 대각선
        dfs(start_x + 1, start_y + 1, end_x, end_y + 1);
    } 
    //세로
    else if(start_y == end_y) {
        //아래
        dfs(start_x + 1, start_y, end_x + 1, end_y);
        //으론쪽 대각선
        dfs(start_x + 1, start_y + 1, end_x + 1, end_y);
    }
    //대각선 && start_y == end_y + 1
    else if(start_x == end_x + 1 && start_y == end_y + 1) {
        dfs(start_x, start_y + 1, end_x + 1, end_y + 1);
        dfs(start_x + 1, start_y, end_x + 1, end_y + 1);
        dfs(start_x + 1, start_y + 1, end_x + 1, end_y + 1);
    }
}

int main() {
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    dfs(0, 1, 0, 0);

    cout << ans;

    
}