#include <iostream>
using namespace std;

int N, M;
char A[51][51];
char B[51][51];

void change(int r, int c) {
    for(int i = r; i < r + 3; i++) {
        for(int j = c; j < c + 3; j++) {
            if(A[i][j] == '0') {
                A[i][j] = '1';
            } else {
                A[i][j] = '0';
            }
        }
    }
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char c;
            cin >> c;
            A[i][j] = c;
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char c;
            cin >> c;
            B[i][j] = c;
        }
    }

    

    int c = 0;
    for(int i = 0; i < N - 2; i++) {
        for(int j = 0; j < M - 2; j++) {
            if(A[i][j] != B[i][j]) {
                change(i, j);
                c++;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(A[i][j] != B[i][j]) {
                cout << -1;
                exit(0);
            }
        }
    }

    cout << c;

}