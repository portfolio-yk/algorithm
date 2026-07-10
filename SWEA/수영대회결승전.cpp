#include<iostream>
#include <queue>
#include <cstring>
#define INF 1e6

using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int bfs(int start_x, int start_y, int end_x, int end_y, int board[15][15], int N) {
    int visited[15][15];
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            visited[i][j] = INF;
        }
    }
    
    queue<pair<int, int>> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 0;
    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;
        
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx > N - 1 || ny > N - 1) continue;
            
            if(visited[nx][ny] > visited[x][y] + 1 && board[nx][ny] != 1) {
                visited[nx][ny] = visited[x][y] + 1;
                if(board[nx][ny] == 2) {
                    visited[nx][ny] += 2 - (visited[x][y] % 3);
                }
                //cout << nx << " " << ny << " " << visited[nx][ny] << "\n";
//                cout << x << " " << y  << " " <<  nx << " " << ny << "\n";
                q.push({ nx, ny });
            }
        }
    }
    if(visited[end_x][end_y] == INF) visited[end_x][end_y] = -1;
    return visited[end_x][end_y];
} 

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{///////////////////////////////////////////////////////////////////////////////
        int N;
		int board[15][15];
        int start_x, start_y, end_x, end_y;
        
		cin >> N;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                int num;
                cin >> num;
            	board[i][j] = num;        
            }
        }
        cin >> start_x >> start_y;
        cin >> end_x >> end_y;
        cout << "#"<< test_case << " " << bfs(start_x, start_y, end_x, end_y, board, N) << "\n";
	}
	return 0;
}