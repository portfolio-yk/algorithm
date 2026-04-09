#include <iostream>
#include <queue>
#define MAX 25
using namespace std;

//0: 밑면, 1: 동, 2: 서, 3: 남, 4: 북, 5: 윗면
int board[6][MAX][MAX];
int visited[6][MAX][MAX];
int N, M, F;

typedef struct position {
    int face;
    int x;
    int y;
} position;

int cube_r, cube_c; // 밑면에서 3의 시작 위치

// input()에서 찾기
void find_cube_offset() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(board[0][i][j] == 3) {
                cube_r = i; cube_c = j; return;
            }
}

void input() {
    //밑면
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int num;
            cin >> num;
            board[0][i][j] = num;
        }
    }
    for(int k = 1; k < 6; k++) {
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < M; j++) {
                int num;
                cin >> num;
                board[k][i][j] = num;
            }
        }
    }

    find_cube_offset();
}

// 0 : 동, 1 : 서, 2: 남, 3: 북
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int next_face[6][4] = {
    { 2, 1, 4, 3 },
    { 0, 5, 3, 4 },
    { 5, 0, 3, 4 },
    { 1, 2, 0, 5 },
    { 2, 1, 0, 5 },
    { 1, 2, 3, 4 },
};


// 주의: 인자 이름이 from_face로 바뀌었습니다!
pair<int, int> transform(int from_face, int dir, int x, int y) {
    int to_face = next_face[from_face][dir];

    // 1. 측면/윗면 -> 밑면(0) 진입 (작성하신 논리 그대로 유지)
    if (to_face == 0) {
        if (from_face == 1) return { cube_r + x, cube_c + M };  // 동 -> 바닥 (우측 진입)
        if (from_face == 2) return { cube_r + x, cube_c - 1 };  // 서 -> 바닥 (좌측 진입)
        if (from_face == 3) return { cube_r + M, cube_c + y };  // 남 -> 바닥 (아래 진입)
        if (from_face == 4) return { cube_r - 1, cube_c + y };  // 북 -> 바닥 (위 진입)
    }

    // 2. 윗면(5) <-> 측면 진입
    if (from_face == 5) {
        if (to_face == 1) return { x, 0 };
        if (to_face == 2) return { x, M - 1 };
        if (to_face == 3) return { 0, y };
        if (to_face == 4) return { 0, y }; // 주의: 북면은 x=0이 윗면과 연결됨!
    }
    if (to_face == 5) {
        if (from_face == 1) return { x, M - 1 };
        if (from_face == 2) return { x, 0 };
        if (from_face == 3) return { M - 1, y };
        if (from_face == 4) return { 0, y }; // 주의: 북면은 x=0이 윗면과 연결됨!
    }

    // 3. 측면 <-> 측면 진입 (3D 모서리 회전)
    // 동면(1) <-> 남면(3)
    if (from_face == 1 && to_face == 3) return { y, M - 1 };
    if (from_face == 3 && to_face == 1) return { M - 1, x };

    // 동면(1) <-> 북면(4)
    if (from_face == 1 && to_face == 4) return { y, 0 };
    if (from_face == 4 && to_face == 1) return { 0, x };

    // 서면(2) <-> 남면(3)
    if (from_face == 2 && to_face == 3) return { M - 1 - y, 0 };
    if (from_face == 3 && to_face == 2) return { M - 1, M - 1 - x };

    // 서면(2) <-> 북면(4)
    if (from_face == 2 && to_face == 4) return { M - 1 - y, M - 1 };
    if (from_face == 4 && to_face == 2) return { 0, M - 1 - x };

    return { x, y };
}

// 밑면 → 측면 진입 시도 동일하게 offset 빼기
pair<int, int> transform_from_bottom(int dir, int prev_x, int prev_y) {
    int fx = prev_x - cube_r;
    int fy = prev_y - cube_c;
    
    // dir은 바닥에서의 이동 방향. (0:동, 1:서, 2:남, 3:북)
    if (dir == 0) return { fx, 0 };             // 바닥 동쪽 이동 -> 서면(2)의 y=0
    if (dir == 1) return { fx, M - 1 };         // 바닥 서쪽 이동 -> 동면(1)의 y=M-1
    if (dir == 2) return { M - 1, fy };         // 바닥 남쪽 이동 -> 북면(4)의 x=M-1 (아래쪽)
    if (dir == 3) return { M - 1, fy };         // 바닥 북쪽 이동 -> 남면(3)의 x=M-1 (아래쪽)
    
    return { 0, 0 };
}

int bfs(int s_face, int s_x, int s_y) {
    queue<position> q;
    q.push({ s_face, s_x, s_y });
    visited[s_face][s_x][s_y] = 1;

    while(q.size()) {
        cout << "?\n";
        position pos = q.front();
        q.pop();
        int face = pos.face;
        int x = pos.x;
        int y = pos.y;

        if(board[face][x][y] == 4) {
            return visited[face][x][y];
        }

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int n_face = face;
            //밑면 아닐 떄
            if(face != 0) {
                if(nx < 0 || nx > M - 1 || ny < 0 || ny > M - 1) {
                    n_face = next_face[face][i];
                    pair<int, int> xy = transform(face, i, x, y);
                    nx = xy.first;
                    ny = xy.second;
                }

                if (n_face == 0 && (nx < 0 || nx >= N || ny < 0 || ny >= N)) continue;

                if(visited[n_face][nx][ny] == 0 && (board[n_face][nx][ny] == 0 || board[n_face][nx][ny] == 4)) {
                    visited[n_face][nx][ny] = visited[face][x][y] + 1;
                    q.push({ n_face, nx, ny });
                }
            } else {
                if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

                if(board[n_face][nx][ny] == 3) {
                    n_face = next_face[n_face][i];
                    pair<int, int> xy = transform_from_bottom(i, x, y);
                    nx = xy.first;
                    ny = xy.second;
                }
                if(visited[n_face][nx][ny] == 0 && (board[n_face][nx][ny] == 0 || board[n_face][nx][ny] == 4)) {
                    visited[n_face][nx][ny] = visited[face][x][y] + 1;
                    q.push({ n_face, nx, ny });
                }
            }
        }
    }
    return -1;
}

int main() {
    
    cin >> N >> M;

    input();
    int res = -1;
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < M; j++) {
            if(board[5][i][j] == 2) {
                res = bfs(5, i, j);
            }
        }
    }

    cout << res;
    
    
}