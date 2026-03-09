#include <iostream>

using namespace std;

char board[51][51];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int N;

int cal_candy() {
    int max_count = 0;
    for(int i = 0; i < N; i++) { 
        int row_first = board[i][0];
        int row_count = 1;
        for(int j = 0; j < N - 1; j++) {
            if(board[i][j + 1] == row_first) {
                row_count++;
            } else {
                row_count = 1;
            }
            row_first = board[i][j + 1];
            max_count = max(max_count, row_count);
        }
    }

    for(int i = 0; i < N; i++) { 
        int col_first = board[0][i];
        int col_count = 1;
        for(int j = 0; j < N - 1; j++) {
            if(board[j + 1][i] == col_first) {
                col_count++;
            } else {
                col_count = 1;
            }
            col_first = board[j + 1][i];
            max_count = max(max_count, col_count);
        }
    }

    return max_count;
}

void board_swap(int x, int y, int x2, int y2) {
    int temp = board[x][y];
    board[x][y] = board[x2][y2];
    board[x2][y2] = temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for(int i = 0; i < N; i++) { 
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    int c = 0;
    for(int i = 0; i < N; i++) { 
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

                board_swap(i, j, nx, ny);
                c = max(c, cal_candy());
                board_swap(nx, ny, i, j);
            }
        }
    }

    cout << c;
}