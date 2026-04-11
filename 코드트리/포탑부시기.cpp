#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;

int current_turn = 1;


typedef struct tower {
	int attack;
	int attack_turn;
	int damage_turn;
	int x;
	int y;
} tower;

tower board[15][15];

typedef struct pos {
	int x;
	int y;
} pos;


void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j].attack << " ";
		}
		cout << "\n";
	}
}

bool compare_wick(const tower& n1, const tower& n2) {
	if (n1.attack != n2.attack) return n1.attack < n2.attack;
	if (n1.attack_turn != n2.attack_turn) {
		return current_turn - n1.attack_turn < current_turn - n2.attack_turn;
	}
	if (n1.x + n1.y != n2.x + n2.y) return n1.x + n1.y > n2.x + n2.y;
	return n1.y > n2.y;
}

tower choice_wickest_tower() {
	int min_attack = 1e9;
	vector<tower> towers;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j].attack > 0) {
				if (min_attack >= board[i][j].attack) {
					towers.push_back(board[i][j]);
				}
			}
		}
	}

	sort(towers.begin(), towers.end(), compare_wick);

	board[towers[0].x][towers[0].y].attack += N + M;
	
	return board[towers[0].x][towers[0].y];
}

bool compare_strong(const tower& n1, const tower& n2) {
	if (n1.attack != n2.attack) return n1.attack > n2.attack;
	if (n1.attack_turn != n2.attack_turn) {
		return current_turn - n1.attack_turn > current_turn - n2.attack_turn;
	}
	if (n1.x + n1.y != n2.x + n2.y) return n1.x + n1.y < n2.x + n2.y;
	return n1.y < n2.y;
}

tower choice_strongest_tower(tower attacker) {
	int max_attack = 0;
	vector<tower> towers;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == attacker.x && j == attacker.y) continue;
			if (board[i][j].attack > 0) {
				if (max_attack <= board[i][j].attack) {
					towers.push_back(board[i][j]);
				}
			}
		}
	}

	sort(towers.begin(), towers.end(), compare_strong);

	return board[towers[0].x][towers[0].y];
}

int visited[15][15];
int dx[8] = { 0, 1, 0, -1, 1, -1, 1, -1 };
int dy[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };

int attack(int start_x, int start_y, int t_x, int t_y) {
	queue<pos> q;
	q.push({ t_x, t_y });
	visited[t_x][t_y] = 1;
	board[start_x][start_y].attack_turn = current_turn;

	while (q.size()) {
		pos p = q.front();
		q.pop();
		int x = p.x;
		int y = p.y;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0) {
				nx = N - 1;
			}
			else if(nx > N - 1) {
				nx = 0;
			}
			else if (ny < 0) {
				ny = M - 1;
			}
			else if (ny > M - 1) {
				ny = 0;
			}
			

			if (visited[nx][ny] == 0 && board[nx][ny].attack > 0) {
				visited[nx][ny] = visited[x][y] + 1;
				q.push({ nx, ny });
			}
		}
	}

	pos lazer_pos = { start_x, start_y };
	if (visited[start_x][start_y] != 0) {
		while (lazer_pos.x != t_x || lazer_pos.y != t_y) {
			for (int i = 0; i < 4; i++) {
				int nx = lazer_pos.x + dx[i];
				int ny = lazer_pos.y + dy[i];

				if (nx < 0) {
					nx = N - 1;
				}
				else if (nx > N - 1) {
					nx = 0;
				}
				else if (ny < 0) {
					ny = M - 1;
				}
				else if (ny > M - 1) {
					ny = 0;
				}

				if (visited[nx][ny] > 0 && visited[lazer_pos.x][lazer_pos.y] - 1== visited[nx][ny]) {
					if (!(nx == t_x && ny == t_y)) {
						board[nx][ny].attack -= board[start_x][start_y].attack / 2;
						board[nx][ny].damage_turn = current_turn;
					}
					lazer_pos = { nx, ny };
					break;
				}
			}
		}
		board[t_x][t_y].attack -= board[start_x][start_y].attack;
		board[t_x][t_y].damage_turn = current_turn;
	}
	else {
		for (int i = 0; i < 8; i++) {
			int nx = t_x + dx[i];
			int ny = t_y + dy[i];

			if (nx < 0) {
				nx = N - 1;
			}
			else if (nx > N - 1) {
				nx = 0;
			}
			if (ny < 0) {
				ny = M - 1;
			}
			else if (ny > M - 1) {
				ny = 0;
			}

			if (board[nx][ny].attack > 0 && !(nx == start_x && ny == start_y)) {
				board[nx][ny].attack -= board[start_x][start_y].attack / 2;
				board[nx][ny].damage_turn = current_turn;
			}
		}
		board[t_x][t_y].attack -= board[start_x][start_y].attack;
		board[t_x][t_y].damage_turn = current_turn;
	}

	memset(visited, 0, sizeof(visited));

	return 1;
}

void upgrade() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j].attack > 0 && board[i][j].damage_turn != current_turn && board[i][j].attack_turn != current_turn) {
				board[i][j].attack++;
			}
		}
	}
}

int get_tower_count() {
	int c = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j].attack > 0){
				c++;
			}
		}
	}
	return c;
}


int main() {
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int num;
			cin >> num;
			//공격 받은턴 맞는지 체크
			board[i][j] = { num, 0, 0, i, j };
		}
	}

	while (K--) {
		
		tower a_t = choice_wickest_tower();
		tower d_t = choice_strongest_tower(a_t);
		attack(a_t.x, a_t.y, d_t.x, d_t.y);
		if (get_tower_count() <= 1) break;
		upgrade();
		current_turn++;
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j].attack > ans) {
				ans = board[i][j].attack;
			}
		}
	}

	cout << ans;
}