//! 메모리 초과
// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;

// int N;
// vector<vector<int>> stack_list;
// priority_queue<pair<int, int>> max_heap;

// int main() {
//     cin >> N;

//     for(int i = 0; i < N; i++) {
//         vector<int> stack;
//         stack_list.push_back(stack);
//     }

//     for(int i = 0; i < N; i++) {
//         for(int j = 0; j < N; j++) {
//             int num;
//             cin >> num;
//             stack_list[j].push_back(num);
//         }
//     }

//     for(int i = 0; i < N; i++) {
//         max_heap.push({ stack_list[i][N - 1], i });
//     }

//     int count = 0;
//     int ans;
//     while(count < 5) {
//         pair<int, int> e = max_heap.top();
//         max_heap.pop();
//         int index = e.second;
//         ans = e.first;
//         stack_list[index].pop_back();

//         if(stack_list[index].size()) {
//             int next = stack_list[index].back();
//             stack_list[index].pop_back();
//             max_heap.push({ next, index });
//         }
        
//         count++;
//     }

//     cout << ans;
// }

#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> min_heap;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int num;
            cin >> num;
            min_heap.push(num);
        }

        while(min_heap.size() > N) {
            min_heap.pop();
        }
    }

    cout << min_heap.top();
}