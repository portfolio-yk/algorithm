// #include <string>
// #include <vector>
// #include <iostream>
// #define INF 1e8

// using namespace std;

// int min_cost = INF;
// int N;

// int dx[4] = { 0, 1, -1, 0 };
// int dy[4] = { 1, 0, 0, -1 };

// int visited[30][30];

// void dfs(vector<vector<int>>& board, int x, int y, int cost, int cur_d) {
//     if(x > N - 1 || x < 0 || y > N - 1 || y < 0) return;
    
//     if(visited[x][y] == 1 || board[x][y] == 1) return;
    
//     if(N - 1 == x && N - 1 == y) {
//         min_cost = min(min_cost, cost);
//         return;
//     }
    
//     for(int i = 0; i < 4; i++) {
//         visited[x][y] = 1;
        
//         int nx = x + dx[i];
//         int ny = y + dy[i];
        
        
//         if(cur_d == i) {
//             dfs(board, nx, ny, cost + 100, i);
//         } else {
//             dfs(board, nx, ny, cost + 600, i);
//         }
        
//         visited[x][y] = 0;
//     }
    
// }

// int solution(vector<vector<int>> board) {
//     int answer = 0;
//     N = board.size();
    
//     dfs(board, 0, 0, 0, 0);
//     dfs(board, 0, 0, 0, 1);
    
//     answer = min_cost;
//     return answer;
// }


#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#define INF 1e8

using namespace std;
int N;

int dx[4] = { 0, 1, -1, 0 };
int dy[4] = { 1, 0, 0, -1 };

int visited[30][30][4];

struct pos {
    int x;
    int y;
    int dir;
};

int bfs(vector<vector<int>>& board, int start_x, int start_y, int d) {
    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            for(int k = 0; k < 4; k++) {
                visited[i][j][k] = INF;   
            }
        }
    }
    
    queue<pos> q;
    q.push({ start_x, start_y , d});
    visited[start_x][start_y][d] = 0;
    
    while(q.size()) {
        pos p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;
        int dir = p.dir;
        
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int cost = 100;
            
            if(dir != i) cost += 500;
            
            if(nx > N - 1|| nx < 0 || ny > N - 1 || ny < 0) continue;
            if(board[nx][ny] == 1) continue;
            
            if(visited[nx][ny][i] > visited[x][y][dir] + cost) {
                visited[nx][ny][i] = visited[x][y][dir] + cost;
                q.push({ nx, ny, i });
            }
        }
    }
    
    int res = INF;
    for(int k = 0; k < 4; k++)                    // ← 도착칸은 모든 방향 중 최소
        res = min(res, visited[N-1][N-1][k]);
    return res;
}   

int solution(vector<vector<int>> board) {
    int answer = 0;
    N = board.size();
    answer = min(bfs(board, 0, 0, 0), bfs(board, 0, 0, 1));
    return answer;
}