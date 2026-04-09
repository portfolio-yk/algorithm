#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
int board[1005][1005];
int board_back[1005][1005];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> C >> T;

    vector<int> cleaner_pos;

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            int num;
            cin >> num;
            board[i][j] = num;

            if(num == -1) {
                cleaner_pos.push_back(i);
            }
        }
    }

    while(T--) {
        //확산
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                if(board[i][j] != -1) {
                    board_back[i][j] = board[i][j] / 5;
                }
            }
        }

        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                if(board[i][j] != 0 && board[i][j] != -1) {
                    for(int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        if(nx < 0 || nx > R - 1 || ny < 0 || ny > C - 1) continue;
                        if(board[nx][ny] == -1) continue;

                        board[nx][ny] += board_back[i][j];
                        board[i][j] -= board_back[i][j];
                    }
                }
            }
        }

        //바람1 아래
        for(int i = cleaner_pos[0] - 1; i >= 0; i--) {
            if(i + 1 == cleaner_pos[0]) {
                board[i][0] = 0;
            } else {
                board[i + 1][0] = board[i][0];
                board[i][0] = 0;
            }
        }
        //바람1 왼쪽
        for(int i = 1; i < C; i++) {
            board[0][i - 1] = board[0][i];
            board[0][i] = 0;
        }
        //바람1 위쪽
        for(int i = 1; i <= cleaner_pos[0]; i++) {
            board[i - 1][C - 1] = board[i][C - 1];
            board[i][C - 1] = 0;
        }
        //바람1 오른쪽
        for(int i = C - 2; i >= 1; i--) {
            board[cleaner_pos[0]][i + 1] = board[cleaner_pos[0]][i];
            board[cleaner_pos[0]][i] = 0;
        }

        //바람2 위
        for(int i = cleaner_pos[1] + 1; i < R; i++) {
            if(i - 1 == cleaner_pos[1]) {
                board[i][0] = 0;
            } else {
                board[i - 1][0] = board[i][0];
                board[i][0] = 0;
            }
        }
        //바람2 왼쪽
        for(int i = 1; i < C; i++) {
            board[R - 1][i - 1] = board[R - 1][i];
            board[R - 1][i] = 0;
        }
        //바람2 아래
        for(int i = R - 2; i >= cleaner_pos[1]; i--) {
            board[i + 1][C - 1] = board[i][C - 1];
            board[i][C - 1] = 0;
        }
        //바람2 오른쪽
        for(int i = C - 2; i >= 1; i--) {
            board[cleaner_pos[1]][i + 1] = board[cleaner_pos[1]][i];
            board[cleaner_pos[1]][i] = 0;
        }
    }

    int ans = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(board[i][j] != -1) {
                ans += board[i][j];
            }
        }
    }

    cout << ans;

    return 0;
}