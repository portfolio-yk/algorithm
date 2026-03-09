#include <iostream>

using namespace std;

int N, row, col;
int c;

void seperate(int size, int ro, int co) {
    if(size == 1) {
        cout << c;
        exit(0);
        return;
    }
        

    int se_size = size / 2;
    int se_r = 0;
    int se_c = 0; 
    
    if(ro >= se_size && co >= se_size) {
        c += se_size * se_size * 3;
        se_r = se_size;
        se_c = se_size;
        ro -= se_size;
        co -= se_size;
    } else if(ro >= se_size && co < se_size) {
        c += se_size * se_size * 2;
        se_r = se_size;
        ro -= se_size;
    } else if(ro < se_size && co >= se_size) {
        c += se_size * se_size;
        se_c = se_size;
        co -= se_size;
    }
    
    seperate(se_size, ro, co);
}

int main() {
    
    cin >> N;
    cin >> row;
    cin >> col;
    
    int size = 1;
    
    for(int i = 0; i < N; i++) {
        size *= 2;
    }
    seperate(size, row, col);
}