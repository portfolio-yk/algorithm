#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    vector<int> board_stack[35];
    vector<int> ans_stack;
    
    for(int i = 0; i < board.size(); i++) {
        vector<int> s;
        for(int j = board.size() - 1; j >= 0; j--) {
            if(board[j][i] != 0) {
                s.push_back(board[j][i]);    
            }
        }
        board_stack[i] = s;
    }
    
    for(int i = 0; i < moves.size(); i++) {
        int move = moves[i] - 1;
        if(!board_stack[move].size()) continue;
        int catched = board_stack[move].back();
        board_stack[move].pop_back();
        
        if(ans_stack.size() && ans_stack.back() == catched) {
            ans_stack.pop_back();
            answer += 2;
        } else {
            ans_stack.push_back(catched);
        }
    }
    
    return answer;
}