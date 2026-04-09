#include <iostream>
#define MAX 55
using namespace std;

int look_board[MAX][MAX];
int board[MAX][MAX];
int army_board[MAX][MAX];

int N, M;

pair<int, int> medusa;
pair<int, int> park;
pair<int, int> armys[305];

void print_look_board() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << look_board[i][j] << " ";
        }
        cout << "\n";
    }
}

void print_board() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int get_direction(int x, int y) {
    int r = medusa.first;
    int c = medusa.second;

    int diff_x = r - x;
    int diff_y = c - y;

    if(diff_x < 0 && diff_y == 0) return 0; // 북
    if(diff_x < 0 && diff_y > 0)  return 1; // 북동
    if(diff_x == 0 && diff_y > 0) return 2; // 동
    if(diff_x > 0 && diff_y > 0)  return 3; // 남동
    if(diff_x > 0 && diff_y == 0) return 4; // 남
    if(diff_x > 0 && diff_y < 0)  return 5; // 남서
    if(diff_x == 0 && diff_y < 0) return 6; // 서
    if(diff_x < 0 && diff_y < 0)  return 7; // 북서

    return -1; // 같은 위치 (x, y == medusa)
}

int look(int dir) {
    int r = medusa.first;
    int c = medusa.second;

    //상
    if(dir == 0) {
        //쭉 위로
        for(int i = r - 1; i >= 0; i--) {
            look_board[i][c] = 1;
        }
        //오른쪽 쭉
        for(int i = c + 1, k = 1; i < N; i++, k++) {
            for(int j = r - k; j >= 0; j--) {
                look_board[j][i] = 1;
            }
        }

        //왼쪽 쭉
        for(int i = c - 1, k = 1; i >= 0; i--, k++) {
            for(int j = r - k; j >= 0; j--) {
                look_board[j][i] = 1;
            }
        }
    }

    //하
    if(dir == 1) {
        //쭉 아래
        for(int i = r + 1; i < N; i++) {
            look_board[i][c] = 1;
        }
        //오른쪽 쭉
        for(int i = c + 1, k = 1; i < N; i++, k++) {
            for(int j = r + k; j < N; j++) {
                look_board[j][i] = 1;
            }
        }

        //왼쪽 쭉
        for(int i = c - 1, k = 1; i >= 0; i--, k++) {
            for(int j = r + k; j < N; j++) {
                look_board[j][i] = 1;
            }
        }
    }

    //좌
    if(dir == 2) {
        //쭉 왼쪽
        for(int i = c - 1; i >= 0; i--) {
            look_board[r][i] = 1;
        }
        //위쪽 쭉
        for(int i = r - 1, k = 1; i >= 0; i--, k++) {
            for(int j = c - k; j >= 0; j--) {
                look_board[i][j] = 1;
            }
        }
        //아래쪽 쭉
        for(int i = r + 1, k = 1; i < N; i++, k++) {
            for(int j = c - k; j >= 0; j--) {
                look_board[i][j] = 1;
            }
        }
    }

    //우
    if(dir == 3) {
        //쭉 오른쪽
        for(int i = c + 1; i < N; i++) {
            look_board[r][i] = 1;
        }
        //위쪽 쭉
        for(int i = r - 1, k = 1; i >= 0; i--, k++) {
            for(int j = c + k; j < N; j++) {
                look_board[i][j] = 1;
            }
        }
        //아래쪽 쭉
        for(int i = r + 1, k = 1; i < N; i++, k++) {
            for(int j = c + k; j < N; j++) {
                look_board[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(look_board[i][j] == 1 && army_board[i][j] == 2) {
                int dir = get_direction(i, j);

                switch(dir) {
                    case 0: // 북: 북서~북 사이
                        for(int k = 1; i-k >= 0; k++)
                            for(int col = max(0, j-k); col <= j; col++)
                                look_board[i-k][col] = 0;
                        break;

                    case 1: // 북동: 북~북동 사이
                        for(int k = 1; i-k >= 0; k++)
                            for(int col = j; col <= min(N-1, j+k); col++)
                                look_board[i-k][col] = 0;
                        break;

                    case 2: // 동: 북동~동 사이
                        for(int k = 1; j+k < N; k++)
                            for(int row = max(0, i-k); row <= i; row++)
                                look_board[row][j+k] = 0;
                        break;

                    case 3: // 남동: 동~남동 사이
                        for(int k = 1; j+k < N; k++)
                            for(int row = i; row <= min(N-1, i+k); row++)
                                look_board[row][j+k] = 0;
                        break;

                    case 4: // 남: 남동~남 사이
                        for(int k = 1; i+k < N; k++)
                            for(int col = j; col <= min(N-1, j+k); col++)
                                look_board[i+k][col] = 0;
                        break;

                    case 5: // 남서: 남~남서 사이
                        for(int k = 1; i+k < N; k++)
                            for(int col = max(0, j-k); col <= j; col++)
                                look_board[i+k][col] = 0;
                        break;

                    case 6: // 서: 남서~서 사이
                        for(int k = 1; j-k >= 0; k++)
                            for(int row = i; row <= min(N-1, i+k); row++)
                                look_board[row][j-k] = 0;
                        break;

                    case 7: // 북서: 서~북서 사이
                        for(int k = 1; j-k >= 0; k++)
                            for(int row = max(0, i-k); row <= i; row++)
                                look_board[row][j-k] = 0;
                        break;
                }
            }
        }
    }

    int c = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(look_board[i][j] == 1 & army_board[i][j] == 2) {
                c++;
            }
        }
    }
    return c;
}

int main() {
    cin >> N >> M;

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    medusa.first = r1; medusa.second = c1;
    board[r1][c1] = 3;
    park.first = r2; park.second = c2;
    board[r2][c2] = 4;

    for(int i = 0; i < M; i++) {
        int r, c;
        cin >> r >> c;
        armys[i] = { r, c };
        army_board[r][c] = 2;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int num;
            cin >> num;
            if(num == 1) {
                board[i][j] = 1;
            }
        }
    }
    print_board();
    // look(0);
    // print_look_board();

}