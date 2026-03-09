#include <iostream>

using namespace std;

int board[128][128];
int blue_count;
int white_count;

int check_all(int s_r, int s_c, int size) {
    int a = board[s_r][s_c];
    for(int i = s_r; i < s_r + size; i++) {
        for(int j = s_c; j < s_c + size; j++) {
            int b = board[i][j];
            if(b != a) {
                return -1;
            }
            a = b;
        }
    }
    return a;
}

void seperate(int s_r, int s_c, int size) {
    int result = check_all(s_r, s_c, size);
    if(result == 1) {
        blue_count++;
    } else if(result == 0) {
        white_count++;
    } else {
        int seperate_size = size / 2;
        seperate(s_r, s_c, seperate_size);
        seperate(s_r + seperate_size, s_c, seperate_size);
        seperate(s_r, s_c + seperate_size, seperate_size);
        seperate(s_r + seperate_size, s_c + seperate_size, seperate_size);
    }
}

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int num;
            cin >> num;
            board[i][j] = num;
        }
    }

    seperate(0, 0, N);
    cout << white_count << "\n" << blue_count;
}