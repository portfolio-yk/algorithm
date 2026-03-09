#include <iostream>

using namespace std;

int board[100][100];
int visited[100][100];
int N;


int dfs(int s_x, int s_y, char color) {
    if(s_x < 0 || s_x > N - 1 || s_y < 0 || s_y > N - 1) {
        return 0;
    }

    if(visited[s_x][s_y] == 0 && board[s_x][s_y] == color) {
        visited[s_x][s_y] = 1;
        dfs(s_x + 1, s_y, color);
        dfs(s_x - 1, s_y, color);
        dfs(s_x, s_y + 1, color);
        dfs(s_x, s_y - 1, color);
        return 1;
    } else {
        return 0;
    }  
}
int main() {
    cin >> N;
    int count = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char color; 
            cin >> color;
            board[i][j] = color; 
        }
    }
    //일반인
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int res = dfs(i, j, board[i][j]);
            
            if(res == 1) {
                count++;
            } 
        }
    }

    cout << count << " ";

    //적록색약
    count = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            visited[i][j] = 0;
            if(board[i][j] == 'G') {
                board[i][j] = 'R';
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int res = dfs(i, j, board[i][j]);
            if(res == 1) {
                count++;
            } 
        }
    }
    cout << count;
}