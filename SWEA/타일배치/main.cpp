#define WIDTH (8)
#include <iostream>
#include <vector>
#include <deque>
#include <iomanip> // 출력 간격을 맞추기 위해 사용

using namespace std;

deque<int> pre_tile_stacks[8];
int board[8][8];



void printBoard() {
    cout << "\n========== CURRENT BOARD (8x8) ==========\n";
    cout << "    [0] [1] [2] [3] [4] [5] [6] [7] (Col)\n"; // 열 번호 표시
    cout << "------------------------------------------\n";

    for (int r = 0; r < 8; ++r) {
        cout << "[" << r << "] "; // 행 번호 표시
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] == 0) {
                // 빈 공간은 인식하기 쉽게 '.' 이나 공백으로 표시 가능
                cout << " .  "; 
            } else {
                // 숫자를 3칸 간격으로 우측 정렬해서 출력
                cout << setw(2) << board[r][c] << "  ";
            }
        }
        cout << "\n";
    }
    cout << "==========================================\n" << endl;
}

int find_remove(bool toRemove[8][8]) {
    int stepScore = 0;
    // 초기화
    for (int y = 0; y < 8; ++y) 
        for (int x = 0; x < 8; ++x) toRemove[y][x] = false;

    // 가로 체크 및 점수 계산
    for (int y = 0; y < 8; ++y) {
        int count = 1;
        for (int x = 1; x <= 8; ++x) {
            if (x < 8 && board[y][x] != 0 && board[y][x] == board[y][x-1]) {
                count++;
            } else {
                if (count >= 3) {
                    if (count == 3) stepScore += 1;
                    else if (count == 4) stepScore += 4;
                    else if (count >= 5) stepScore += 9;
                    for (int k = 1; k <= count; ++k) toRemove[y][x-k] = true;
                }
                count = 1;
            }
        }
    }

    // 세로 체크 및 점수 계산
    for (int x = 0; x < 8; ++x) {
        int count = 1;
        for (int y = 1; y <= 8; ++y) {
            if (y < 8 && board[y][x] != 0 && board[y][x] == board[y-1][x]) {
                count++;
            } else {
                if (count >= 3) {
                    if (count == 3) stepScore += 1;
                    else if (count == 4) stepScore += 4;
                    else if (count >= 5) stepScore += 9;
                    for (int k = 1; k <= count; ++k) toRemove[y-k][x] = true;
                }
                count = 1;
            }
        }
    }

    return stepScore; // 이번 단계에서 얻은 점수 반환 (0이면 매칭 없음)
}

void remove(bool toRemove[8][8]) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (toRemove[y][x]) board[y][x] = 0;
        }
    }
}

int countMatches(bool toRemove[8][8]) {
    int score = 0;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (toRemove[y][x]) score++;
        }
    }
    return score;
}

int calculateScore(bool toRemove[8][8]) {
    int totalScore = 0;

    // 1. 가로 점수 계산
    for (int y = 0; y < 8; ++y) {
        int count = 1;
        for (int x = 1; x <= 8; ++x) {
            if (x < 8 && board[y][x] != 0 && board[y][x] == board[y][x-1]) {
                count++;
                //cout << x << " " << y  << " "  << count << "\n";
            } else {
                if (count >= 3) {
                    if (count == 3) totalScore += 1;
                    else if (count == 4) totalScore += 4;
                    else if (count >= 5) totalScore += 9;
                    
                    //cout << "? " << count << "\n";
                                        // 제거 표시
                    //for (int k = 1; k <= count; ++k) toRemove[y][x-k] = true;
                }
                count = 1;
            }
        }
    }

    // 2. 세로 점수 계산
    for (int x = 0; x < 8; ++x) {
        int count = 1;
        for (int y = 1; y <= 8; ++y) {
            if (y < 8 && board[y][x] != 0 && board[y][x] == board[y-1][x]) {
                count++;
            } else {
                if (count >= 3) {
                    if (count == 3) totalScore += 1;
                    else if (count == 4) totalScore += 4;
                    else if (count >= 5) totalScore += 9;
                    
                    // 제거 표시
                    //for (int k = 1; k <= count; ++k) toRemove[y-k][x] = true;
                }
                count = 1;
            }
        }
    }
    return totalScore;
}

struct BestResult {
    int y, x, dir; // dir 0: 오른쪽, 1: 위쪽
    int score;
};

BestResult findBestMove() {
    BestResult best = {-1, -1, -1, -1};
    

    for (int y = 7; y >= 0; --y) {
        for (int x = 0; x < 8; ++x) {
            if (x + 1 < 8) {
                bool toRemove[8][8] = {false};
                swap(board[y][x], board[y][x + 1]);
                int currentScore;
                if (currentScore =find_remove(toRemove)) {
                    if (currentScore > best.score) {
                        best = {y, x, 0, currentScore};
                    }
                }
                swap(board[y][x], board[y][x + 1]); // 원상복구
            }

            // 2. 위쪽 타일과 교환 시뮬레이션
            if (y - 1 >= 0) {
                bool toRemove[8][8] = {false};
                swap(board[y][x], board[y - 1][x]);
                int currentScore;
                if (currentScore = find_remove(toRemove)) {
                    if (currentScore > best.score) {
                        best = {y, x, 1, currentScore};
                    }
                }
                swap(board[y][x], board[y - 1][x]); // 원상복구
            }
        }
    }
    return best;
}

void fill() {
    int rows = 8;
    int cols = 8;

    for (int x = 0; x < cols; ++x) {
        vector<int> temp;

        for (int y = rows - 1; y >= 0; --y) {
            if (board[y][x] != 0) {
                temp.push_back(board[y][x]);
            }
        }

        //밑으로 밀기
        int y = rows - 1;
        for (int tile : temp) {
            board[y][x] = tile;
            y--;
        }

        // 예비타일로 채우기
        while (y >= 0) {
            board[y][x] = pre_tile_stacks[x].front();
            pre_tile_stacks[x].pop_front();
            y--;
        }
    }
}

void init(int N, int mTiles[][WIDTH])
{
    for (int i = 0; i < 8; ++i) {
        pre_tile_stacks[i].clear();
    }

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < 8; ++x) {
            pre_tile_stacks[x].push_back(mTiles[y][x]);
        }
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            board[y][x] = 0;
        }
    }

    fill();

    bool toRemove[8][8];
    while (find_remove(toRemove) > 0) { // 채워진 판에서 터질 게 있다면
        remove(toRemove);
        fill(); // 다시 채우기 (연쇄 반복)
    }
    
    BestResult target;
    while (true) {
        target = findBestMove();

        if (target.score > 0) break;

        for (int y = 0; y < 8; ++y)
            for (int x = 0; x < 8; ++x) board[y][x] = 0;

        fill();

        bool toRemove[8][8];
        while (find_remove(toRemove) > 0) {
            remove(toRemove);
            fill();
        }

    }
    //printBoard();
}

int mRet[5];
int* takeTurn() {
    BestResult target;
    while (true) {
        target = findBestMove();

        if (target.score > 0) break;

        for (int y = 0; y < 8; ++y)
            for (int x = 0; x < 8; ++x) board[y][x] = 0;

        fill();

        bool toRemove[8][8];
        while (find_remove(toRemove) > 0) {
            remove(toRemove);
            fill();
        }

    }

    mRet[0] = target.score;
    mRet[1] = target.y;
    mRet[2] = target.x;

    if (target.dir == 0) { // 오른쪽과 교환
        mRet[3] = target.y;
        mRet[4] = target.x + 1;
    } else { // 위쪽과 교환
        mRet[3] = target.y - 1;
        mRet[4] = target.x;
    }

    swap(board[mRet[1]][mRet[2]], board[mRet[3]][mRet[4]]);
    
    mRet[1] = 8 - target.y - 1;
    mRet[2] = target.x;

    if (target.dir == 0) { // 오른쪽과 교환
        mRet[3] = mRet[1];
        mRet[4] = target.x + 1;
    } else { // 위쪽과 교환
        mRet[3] = mRet[1] + 1;
        mRet[4] = target.x;
    }

    int totalScore = 0;
    bool toRemove[8][8] = {false};
    int currentStepScore;

    // find_remove가 점수를 반환하므로, 0보다 클 때까지 계속 반복
    while ((currentStepScore = find_remove(toRemove)) > 0) {
        totalScore += currentStepScore; // 매 단계(콤보) 점수 누적
        remove(toRemove);          // 보드에서 삭제 (0으로)
        fill();                         // 내리기 & 예비 타일 채우기
    }
    mRet[0] = totalScore;

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "여기 " << mRet[i] << " ";
    // }
    // cout << "\n";

    //printBoard();
    return mRet;
}

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

const int CMD_INIT = 100;
const int CMD_TAKETURN = 200;

static int tiles[10000][WIDTH];


static bool run()
{
	bool okay = false;
	int Q, N;

	scanf("%d", &Q);

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		int correct_ans[5];
		int* user_ans;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d", &N);
			for (int y = 0; y < N; y++)
			{
				for (int x = 0; x < WIDTH; x++)
				{
					scanf("%d", tiles[y] + x);
				}
			}

			init(N, tiles);
			okay = true;
			break;
		case CMD_TAKETURN:
			user_ans = takeTurn();
			for (int i = 0; i < 5; i++)
			{
				scanf("%d", correct_ans + i);
				if (user_ans[i] != correct_ans[i])
					okay = false;
			}
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	//	freopen("sample_input.txt", "r", stdin);

	int TC, MARK;

	scanf("%d %d", &TC, &MARK);
	for (int tc = 1; tc <= TC; ++tc)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}