#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#define MAX 55
using namespace std;

int N, T;

//T,M,C 선호
unordered_map<char, int> seat_prefer[MAX][MAX];
//신앙심
int seat_trust[MAX][MAX];
//bfs용 visited
int visited[MAX][MAX];

void print_prefer() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            unordered_map<char, int> prefer = seat_prefer[i][j];
            cout << prefer['T'] << prefer['M'] << prefer['C'] << " ";
        }
        cout << "\n";
    }
}

void print_trust() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << seat_trust[i][j] << " ";
        }
        cout << "\n";
    }
}

//신앙심 모두 1 증가
void plus_trust() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            seat_trust[i][j] += 1;
        }
    }
}

//그룹화
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<pair<int, int>> cluster(int start_x, int start_y) {
    vector<pair<int, int>> group;

    if(visited[start_x][start_y] == 1) return group;
    
    unordered_map<char, int> prefer = seat_prefer[start_x][start_y];
    bool isT = prefer['T'] > 0;
    bool isM = prefer['M'] > 0;
    bool isC = prefer['C'] > 0;
    
    queue<pair<int, int>> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = 1;

    while(q.size()) {
        pair<int, int> xy = q.front();
        q.pop();
        int x = xy.first;
        int y = xy.second;
        group.push_back({ x, y });

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;

            if(visited[nx][ny] == 0) {
                unordered_map<char, int> t_prefer = seat_prefer[nx][ny];
                bool t_isT = t_prefer['T'] > 0;
                bool t_isM = t_prefer['M'] > 0;
                bool t_isC = t_prefer['C'] > 0;
            
                if(isT == t_isT && t_isM == isM && t_isC == isC) {
                    visited[nx][ny] = 1;
                    q.push({ nx, ny });
                }
            }
        }
    }
    return group;
}


bool compare_head(const pair<int, int>& n1, const pair<int, int>& n2) {
    int x1 = n1.first;
    int y1 = n1.second;
    int x2 = n2.first;
    int y2 = n2.second;
    if(seat_trust[x1][y1] != seat_trust[x2][y2]) return seat_trust[x1][y1] > seat_trust[x2][y2];

    if(x1 != x2) return x1 < x2;

    return y1 < y2;
}

pair<int, int> choice_head(vector<pair<int, int>> group) {
    sort(group.begin(), group.end(), compare_head);

    return group[0];
}


bool compare_spread(const pair<int, int>& n1, const pair<int, int>& n2) {
    int x1 = n1.first;
    int y1 = n1.second;
    int x2 = n2.first;
    int y2 = n2.second;

    unordered_map<char, int> prefer = seat_prefer[x1][y1];
    bool isT = prefer['T'] > 0;
    bool isM = prefer['M'] > 0;
    bool isC = prefer['C'] > 0;
    
    int prefer_count = isT + isM + isC;

    unordered_map<char, int> t_prefer = seat_prefer[x2][y2];
    bool t_isT = t_prefer['T'] > 0;
    bool t_isM = t_prefer['M'] > 0;
    bool t_isC = t_prefer['C'] > 0;

    int t_prefer_count = t_isT + t_isM + t_isC;

    if(prefer_count != t_prefer_count) return prefer_count < t_prefer_count;

    if(seat_trust[x1][y1] != seat_trust[x2][y2]) return seat_trust[x1][y1] > seat_trust[x2][y2];

    if(x1 != x2) return x1 < x2;

    return y1 < y2;
}

void spread(int start_x, int start_y, int dir, int gan) {
    int dx2[4] = { -1, 1, 0, 0 };
    int dy2[4] = { 0, 0, -1, 1 };
    int x = start_x;
    int y = start_y;
    while(1) {
        x = x + dx2[dir];
        y = y + dy2[dir];

        if(gan <= 0) break;
        if(x < 0 || x > N - 1 || y < 0 || y > N - 1) break;
        
        unordered_map<char, int> prefer = seat_prefer[start_x][start_y];
        bool isT = prefer['T'] > 0;
        bool isM = prefer['M'] > 0;
        bool isC = prefer['C'] > 0;

        unordered_map<char, int> t_prefer = seat_prefer[x][y];
        bool t_isT = t_prefer['T'] > 0;
        bool t_isM = t_prefer['M'] > 0;
        bool t_isC = t_prefer['C'] > 0;
        //신봉 음식이 같은 경우
        if(isT == t_isT && t_isM == isM && t_isC == isC) continue;
        //신봉 음식이 다른 경우
        else {
            //강한전파
            if(gan > seat_trust[x][y]) {
                //동일한 음식 신봉
                seat_prefer[x][y]['T'] = isT;
                seat_prefer[x][y]['M'] = isM;
                seat_prefer[x][y]['C'] = isC;

                //간절함 신앙심 + 1 만큼 깍기
                gan -= seat_trust[x][y] + 1;
                //전파 대상 신앙심 1 증가
                seat_trust[x][y] += 1;
                
            }
            //약한전파
            else {
                //없을 것들 관심
                if(t_isT == 0) seat_prefer[x][y]['T'] = isT;
                if(t_isM == 0) seat_prefer[x][y]['M'] = isM;
                if(t_isC == 0) seat_prefer[x][y]['C'] = isC;

                //간절함 0
                seat_trust[x][y] += gan;
                gan = 0;
            }
            seat_prefer[x][y]['s'] = 1;
        }

    }
}

void print_answer() {
    int answer[7] = { 0, 0, 0, 0, 0, 0, 0 };

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            unordered_map<char, int> prefer = seat_prefer[i][j];
            bool isT = prefer['T'] > 0;
            bool isM = prefer['M'] > 0;
            bool isC = prefer['C'] > 0;

            if(isT && isM && isC) {
                answer[0] += seat_trust[i][j];
            } else if(isT && isC) {
                answer[1] += seat_trust[i][j];
            } else if(isT && isM) {
                answer[2] += seat_trust[i][j];
            } else if(isC && isM) {
                answer[3] += seat_trust[i][j];
            } else if(isM) {
                answer[4] += seat_trust[i][j];
            } else if(isC) {
                answer[5] += seat_trust[i][j];
            } else {
                answer[6] += seat_trust[i][j];
            }
        }
    }

    for(int i = 0; i < 7; i++) {
        cout << answer[i] << " ";
    }
    cout << "\n";
}

int main() {
    cin >> N >> T;
    //신봉 음식 입력
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c;
            cin >> c;
            seat_prefer[i][j][c] += 1;
            
        }
    }

    //신앙심 입력
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int n;
            cin >> n;
            seat_trust[i][j] += n;
        }
    }
    
    while(T--) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                visited[i][j] = 0;
                seat_prefer[i][j]['s'] = 0;
            }
        }

        //아침
        //모두의 신앙심 1씩 오름
        plus_trust();

        //점심
        //같은 음식 그룹화 후 대표자 뽑기
        vector<pair<int, int>> heads;
        vector<pair<int, int>> group;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                //그룹화
                group = cluster(i, j);
                //대표자 뽑기
                if(group.size()) {
                    pair<int, int> head = choice_head(group);
                    heads.push_back(head);
                    //대표자에게 신앙심 1씩 넘김
                    int trust_sum = 0;
                    for(pair<int, int> mem : group) {
                        if(head.first != mem.first || head.second != mem.second) {
                            seat_trust[mem.first][mem.second] -= 1;
                            trust_sum++;
                        }
                    }

                    //대표는 넘겨진 만큼 신앙심 추가
                    seat_trust[head.first][head.second] += trust_sum;
                }
                
            }
        }

        //저녁 
        //전파할 순서 정렬
        sort(heads.begin(), heads.end(), compare_spread);

        for(int i = 0; i < heads.size(); i++) {
            pair<int, int> head = heads[i];
            int x = head.first;
            int y = head.second;

            //전파자 신앙심 1만 남기고 나머지는 간절함
            int trust = seat_trust[x][y];
            
            //전파
            int dir = trust % 4;
            if(seat_prefer[x][y]['s'] != 1) {
                int gan = trust - 1;
                seat_trust[x][y] = 1;
                spread(x, y, dir, gan);
            }
        }
        print_answer();
    }
}