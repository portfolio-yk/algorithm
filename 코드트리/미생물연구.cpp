    #include <iostream>
    #include <queue>
    #include <set>
    #define MAX 20 
    using namespace std;

    int board[MAX][MAX];
    int visited[MAX][MAX];
    int new_board[MAX][MAX];

    int N, Q;

    struct misangmul {
        int num;
        int size;
        int r;
        int c;
        vector<pair<int, int>> pos; 
    };

    misangmul misangmul_list[55];

    void print_board() {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void print_newboard() {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                cout << new_board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void put_misangmul(int num, int r1, int c1, int r2, int c2) {
        for(int i = c1 + 1; i <= c2; i++) {
            for(int j = r1 + 1; j <= r2; j++) {
                board[i][j] = num;
            }
        }
    }

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };
    vector<pair<int, int>> bfs(int start_x, int start_y) {
        vector<pair<int, int>> pos;
        

        if(board[start_x][start_y] == 0) return pos;
        if(visited[start_x][start_y] == 1) return pos;

        // cout << "a" << start_x << " " << start_y << "\n";

        queue<pair<int, int>> q;
        q.push({ start_x, start_y });
        visited[start_x][start_y] = 1;

        int num = board[start_x][start_y];

        while(q.size()) {
            pair<int, int> xy = q.front();
            q.pop();
            int x = xy.first;
            int y = xy.second;

            pos.push_back({ x, y });
            
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if(nx < 0 || nx > N || ny < 0 || ny > N) continue;

                if(visited[nx][ny] == 0 && board[nx][ny] == num) {
                    visited[nx][ny] = 1;
                    q.push({ nx, ny });
                }
            }
        }
        
        return pos;
    }

    bool compare(const misangmul& n1, const misangmul& n2) {
        if(n1.size != n2.size) return n1.size > n2.size;
        return n1.num < n2.num;
    }

    vector<misangmul> get_misangmul() {
        vector<misangmul> misangmuls;
        int split_count[55] = {0}; // 함수 내 선언 또는 초기화
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                vector<pair<int, int>> pos = bfs(i, j);
                if(pos.size()) {
                    int num = board[i][j];
                    split_count[num]++;

                    if(split_count[num] == 1) {
                        misangmul_list[num].num = num;
                        misangmul_list[num].size = pos.size();
                        misangmul_list[num].pos = pos;
                        misangmul_list[num].r = i;
                        misangmul_list[num].c = j;
                    } else {
                        misangmul_list[num].num = 0; // 2번이든 3번이든 확실하게 소멸
                    }
                }
                
            }
        }

        for(int i = 1; i <= Q; i++) {
            if(misangmul_list[i].num != 0) {
                misangmuls.push_back(misangmul_list[i]);
            }
        }

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                visited[i][j] = 0;
            }
        }


        sort(misangmuls.begin(), misangmuls.end(), compare);

        for(int i = 0; i < misangmuls.size(); i++) {
            misangmul_list[misangmuls[i].num].num = 0;
        }

        // for(int i = 0; i < misangmuls.size(); i++) {
        //     misangmuls[i].num = i + 1;
        // }

        
        
        return misangmuls;
    }



    int move_misangmul(misangmul m) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                int diff_r = j - m.r;
                int diff_c = i - m.c;

                int f = 1;
                for(pair<int, int> xy : m.pos) {
                    int nr = xy.first + diff_r;
                    int nc = xy.second + diff_c;
                    if(nr < 1 || nr > N || nc < 1 || nc > N || new_board[nr][nc] != 0) {
                    f = 0; break;
                    }
                }

                if(f) {
                    for(pair<int, int> xy : m.pos) {
                        new_board[xy.first + diff_r][xy.second + diff_c] = m.num;
                    }
                    return 1;
                }
            }
        }

        return 0;
    }

    set<int> get_near(int start_x, int start_y, int target) {
        set<int> nears;

        if(board[start_x][start_y] == 0) return nears; 
        if(visited[start_x][start_y] == 1) return nears;

        queue<pair<int, int>> q;
        q.push({ start_x, start_y });

        visited[start_x][start_y] = 1;

        while(q.size()) {
            pair<int, int> xy = q.front();
            q.pop();
            int x = xy.first;
            int y = xy.second;

            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if(nx < 0 || nx > N || ny < 0 || ny > N) continue;

                if(visited[nx][ny] == 0 && board[nx][ny] != 0) {
                    visited[nx][ny] = 1;
                    if(board[nx][ny] != target) {
                        nears.insert(board[nx][ny]);   
                    } else {   
                        q.push({ nx, ny });
                    }
                }
            }
        }
        return nears;
    }

    int get_result(vector<misangmul> misangmuls) {
        int near_arr[55][55];
        int size_map[55] = {0};

        for(int i = 0; i < 55; i++) {
            for(int j = 0; j < 55; j++) {
                near_arr[i][j] = 0;
            }
        }

        for(misangmul m : misangmuls) {
            size_map[m.num] = m.size;
        }
        int result = 0;

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(board[i][j] != 0) {
                    set<int> nears = get_near(i, j, board[i][j]);
                    for(int a : nears) {
                        // cout << "what" << a << "\n";
                        near_arr[board[i][j]][a] = 1;
                        near_arr[a][board[i][j]] = 1;
                    }

                    for(int i2 = 1; i2 <= N; i2++) {
                        for(int j2 = 1; j2 <= N; j2++) {
                            visited[i2][j2] = 0;
                        }
                    }
                }
            }
        }
        
        for(int i = 0; i < 55; i++) {
            for(int j = i + 1; j < 55; j++) {
                if(near_arr[i][j] == 1) {
                    //cout << i << " " << j << " " << misangmuls[i - 1].size << " " << misangmuls[j - 1].size << "\n";
                    result += size_map[i] * size_map[j];
                }
            }
        }

        return result;
    }

    int main() {
        cin >> N >> Q;

        

        for(int i = 1; i <= Q; i++) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            //misangmuls.push_back({ i, r1, c1, r2, c2 });
            put_misangmul(i, r1, c1, r2, c2);

            vector<misangmul> misangmuls = get_misangmul();
            for(misangmul m : misangmuls) {
                // cout << "b" << m.num << "\n";
                move_misangmul(m);
            }

            //출력
            for(int i = 1; i <= N; i++) {
                for(int j = 1; j <= N; j++) {
                    board[i][j] = 0;
                    board[i][j] = new_board[i][j];
                }
            }

            for(int i = 1; i <= N; i++) {
                for(int j = 1; j <= N; j++) {
                    new_board[i][j] = 0;
                }
            }

            cout << get_result(misangmuls) << "\n";

        }

        //print_board();
    }