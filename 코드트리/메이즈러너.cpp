#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, M, K;

int board[15][15];

typedef struct person {
	int num;
	int x;
	int y;
	int d;
	int is_exit;
} person;

person people[25];

typedef struct pos {
	int x;
	int y;
} pos;

pos exit_pos;

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

int get_distance(int r1, int c1, int r2, int c2) {
	return abs(r1 - r2) + abs(c1 - c2);
}

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void move_people() {
	for (int num = 11; num < M + 11; num++) {
		person p = people[num];

		if (p.is_exit == 1) continue;

		int min_d = get_distance(p.x, p.y, exit_pos.x, exit_pos.y);
		int min_x = p.x;
		int min_y = p.y;

		for (int i = 0; i < 4; i++) {
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];

			//밖
			if (nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) continue;
			//벽
			if (board[nx][ny] > 0 && board[nx][ny] <= 9) continue;
			int dist = get_distance(nx, ny, exit_pos.x, exit_pos.y);
			
			if (min_d > dist) {
				min_d = dist;
				min_x = nx;
				min_y = ny;
			}
		}

		if (min_x != p.x || min_y != p.y) {
			//여러명 있을 수 있는데 ㄱㅊ을까?
			//탈출
			if (board[min_x][min_y] == -1) {
				people[num].is_exit = 1;
				people[num].d++;
			}
			else {
				//board[min_x][min_y] = num;
				people[num].x = min_x;
				people[num].y = min_y;
				people[num].d++;
			}
		}
		
	}
}


vector<person> find_person(int x, int y) {
	vector<person> p;
	for (int num = 11; num < M + 11; num++) {
		if (people[num].is_exit == 1) continue; // <-- 이것만 추가됨!

		if (people[num].x == x && people[num].y == y) {
			p.push_back(people[num]);
		}
	}
	return p;
}

bool rotate_90(int size) {
	
	int s_r;
	int s_c;
	int is_find = 0;
	for (int i = 0; i < N - size; i++) {
		for (int j = 0; j < N - size; j++) {
			int is_in_exit = 0;
			int is_in_person = 0;

			for (int i2 = i; i2 <= i + size; i2++) {
				for (int j2 = j; j2 <= j + size; j2++) {
					if(find_person(i2,j2).size()) {
						is_in_person = 1;
					}

					if (board[i2][j2] == -1) {
						is_in_exit = 1;
					}
				}
			}
			//둘 다 있으면 끝, 못찾는 경우도 있나???????
			if (is_in_exit == 1 && is_in_person == 1) {
				s_r = i;
				s_c = j;
				is_find = 1;
				break;
			}
		}
		if (is_find == 1) break;
	}

	if (is_find == 0) return false;

	//검증 필요
	double c_r = (s_r + s_r + size) / 2.0;
	double c_c = (s_c + s_c + size) / 2.0;

	int temp[15][15];

	for (int i = s_r; i <= s_r + size; i++) {
		for (int j = s_c; j <= s_c + size; j++) {
			double n_r = i - c_r;
			double n_c = j - c_c;

			int x = n_c + c_r;
			int y = -n_r + c_c;
			
			if (board[i][j] == -1) {
				exit_pos.x = x;
				exit_pos.y = y;
			}
			/*else if (find_person(i, j).size()) {
				int o_x = people[board[i][j]].x;
				int o_y = people[board[i][j]].y;
				for (int num = 11; num < M + 11; num++) {
					if (people[num].x == o_x && people[num].y == o_y) {
						people[num].x = x;
						people[num].y = y;
					}
				}
			}*/

			// 사람 배열(11~M+11)을 순회하면서, 회전 사각형 안에 있는 사람만 좌표를 갱신합니다.
			

			temp[x][y] = board[i][j];
		}
	}

	for (int num = 11; num < M + 11; num++) {
		if (people[num].is_exit == 1) continue; // 이미 나간 사람은 패스

		int px = people[num].x;
		int py = people[num].y;

		// 현재 사람의 위치가 회전하는 사각형(s_r ~ s_r+size, s_c ~ s_c+size) 안에 있다면?
		if (px >= s_r && px <= s_r + size && py >= s_c && py <= s_c + size) {
			// 작성해두신 수학 공식 적용!
			double n_r = px - c_r;
			double n_c = py - c_c;
			people[num].x = n_c + c_r;
			people[num].y = -n_r + c_c;
		}
	}

	for (int i = s_r; i <= s_r + size; i++) {
		for (int j = s_c; j <= s_c + size; j++) {
			board[i][j] = temp[i][j];

			//벽이라면 내구도 -1
			if (board[i][j] > 0 && board[i][j] <= 9) {
				board[i][j]--;
			}
		}
	}

	return true;
}

bool is_all_exit() {
	for (int i = 11; i < M + 11; i++) {
		if (people[i].is_exit == 0) {
			return false;
		}
	}
	return true;
}


int main() {
	cin >> N >> M >> K;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	
	for (int i = 11; i < M + 11; i++) {
		int x, y;
		cin >> x >> y;
		people[i] = { i, x - 1, y - 1, 0, 0 };
		//board[x - 1][y - 1] = i;
	}
	cin >> exit_pos.x >> exit_pos.y;
	exit_pos.x--;
	exit_pos.y--;
	board[exit_pos.x][exit_pos.y] = -1;
	//print_board();

	/*move_people();
	rotate_90(3 - 1);
	print_board();*/

	while (K--) {
		


		
		move_people();

		if (is_all_exit()) break;

		for (int i = 0; i < N; i++) {
			if (rotate_90(i)) {
				break;
			}
		}
	}

	int ans = 0;
	for (int i = 11; i < M + 11; i++) {
		ans += people[i].d;
	}

	cout << ans << "\n";
	cout << exit_pos.x + 1<< " " << exit_pos.y + 1;
}