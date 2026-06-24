#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int N;

// n = 10 -> 10C5 = 252
// 뽑은 5개 주사위의 합 경우의 수 = 6^5
// => 252 * 6^5 * 6^5
// 

vector<vector<int>> choice_dice_A;
vector<int> count_A;
vector<vector<int>> choice_dice_B;

vector<int> path;

void dfs_dice(int start, int depth) {
    if(depth == N / 2) {
        choice_dice_A.push_back(path);

        vector<bool> used(N + 1, false);
        for(int num : path) used[num] = true;

        vector<int> path_B;
        for(int i = 1; i <= N; i++)
            if(!used[i]) path_B.push_back(i);

        choice_dice_B.push_back(path_B);
        return;
    }

    for(int i = start; i <= N; i++) {
        path.push_back(i);
        dfs_dice(i + 1, depth + 1);
        path.pop_back();
    }
}

vector<int> sum_A;
vector<int> sum_B;

void sum_count_A(vector<vector<int>>& dices, int depth, vector<int> choice_dice, int m_sum) {
    if(depth == N / 2) {
        sum_A.push_back(m_sum);
        return; 
    }
    for(int i = 0; i < 6; i++) {
        sum_count_A(dices, depth + 1, choice_dice, m_sum + dices[choice_dice[depth] - 1][i]);
    }
}

void sum_count_B(vector<vector<int>>& dices, int depth, vector<int> choice_dice, int m_sum) {
    if(depth == N / 2) {
        sum_B.push_back(m_sum);
        return; 
    }
    for(int i = 0; i < 6; i++) {
        sum_count_B(dices, depth + 1, choice_dice, m_sum + dices[choice_dice[depth] - 1][i]);
    }
}

vector<int> solution(vector<vector<int>> dice) {
    vector<int> answer;
    N = dice.size();
    dfs_dice(1, 0);
    for(int i = 0; i < choice_dice_A.size(); i++) {
        sum_count_A(dice, 0, choice_dice_A[i], 0);
        sum_count_B(dice, 0, choice_dice_B[i], 0);
        
        sort(sum_A.begin(), sum_A.end());
        sort(sum_B.begin(), sum_B.end());
        
        int c = 0;
        
        for(int j = 0; j < sum_A.size(); j++) {
            c += lower_bound(sum_B.begin(), sum_B.end(), sum_A[j]) - sum_B.begin();
        }
        
        count_A.push_back(c);
        sum_A.clear();
        sum_B.clear();
    }
    
    int max_i = -1;
    int max_win = -1;
    for(int i = 0; i < count_A.size(); i++) {
        if(max_win < count_A[i]) {
            max_win = count_A[i];
            max_i = i;
        }
    }

    answer = choice_dice_A[max_i];
    
    
    return answer;
}