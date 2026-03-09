#define WIDTH (8)

#include <vector>
#include <deque>

using namespace std;

deque<int> pre_tile_stacks[8];
int board[8][8];

int find_remove(bool toRemove[8][8]) {
    int stepScore = 0;

    for (int y = 0; y < 8; ++y) 
        for (int x = 0; x < 8; ++x) toRemove[y][x] = false;

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

    return stepScore; 
}

void remove(bool toRemove[8][8]) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (toRemove[y][x]) board[y][x] = 0;
        }
    }
}

struct BestResult {
    int y, x, dir; 
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
                swap(board[y][x], board[y][x + 1]); 
            }

            if (y - 1 >= 0) {
                bool toRemove[8][8] = {false};
                swap(board[y][x], board[y - 1][x]);
                int currentScore;
                if (currentScore = find_remove(toRemove)) {
                    if (currentScore > best.score) {
                        best = {y, x, 1, currentScore};
                    }
                }
                swap(board[y][x], board[y - 1][x]); 
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
    while (find_remove(toRemove) > 0) { 
        remove(toRemove);
        fill(); 
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

    if (target.dir == 0) {
        mRet[3] = target.y;
        mRet[4] = target.x + 1;
    } else { 
        mRet[3] = target.y - 1;
        mRet[4] = target.x;
    }

    swap(board[mRet[1]][mRet[2]], board[mRet[3]][mRet[4]]);
    
    mRet[1] = 8 - target.y - 1;
    mRet[2] = target.x;

    if (target.dir == 0) { 
        mRet[3] = mRet[1];
        mRet[4] = target.x + 1;
    } else { 
        mRet[3] = mRet[1] + 1;
        mRet[4] = target.x;
    }

    int totalScore = 0;
    bool toRemove[8][8] = {false};
    int currentStepScore;

    
    while ((currentStepScore = find_remove(toRemove)) > 0) {
        totalScore += currentStepScore; 
        remove(toRemove);          
        fill();                        
    }
    mRet[0] = totalScore;


    return mRet;
}