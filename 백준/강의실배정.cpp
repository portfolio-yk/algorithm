//! 시간초과
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// struct Time {
//     int start;
//     int end;
// };

// vector<vector<Time>> class_list;

// int N;

// bool compare(Time& a, Time& b) {
//     return a.end < b.end;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     cin >> N;

//     vector<Time> time_list;
//     for(int i = 0; i < N; i++) {
//         int S, T;
//         cin >> S >> T;

//         time_list.push_back({S, T});
//     }

//     sort(time_list.begin(), time_list.end(), compare);

//     vector<Time> c = {{time_list[0].start, time_list[0].end}};
//     class_list.push_back(c);

//     for(int i = 1; i < N; i++) {
//         Time t = time_list[i];

//         int min_class = 1000000;
//         int min_index = -1;    
//         for(int j = 0; j < class_list.size(); j++) {
//             auto& cla = class_list[j];
//             Time c = cla.back();
            
//             if(c.end <= t.start) {
//                 if(min_class > t.start - c.end) {
//                     min_class = t.start - c.end;
//                     min_index = j;
//                 }
//             }
//         }

//         if(min_index == -1) {
//             vector<Time> time_list = {{t.start, t.end}};
//             class_list.push_back(time_list);
//         } else {
//             class_list[min_index].push_back(t);
//         }
//     }

//     cout << class_list.size();
// }



//모든 시간을 다 배정행하니까. 시작 시간 순으로 정렬 
//우선순위 큐를 사용해 먼저 끝나는 시간 지우기
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main(){
    int n, tmp1, tmp2;
    vector<pair<int, int>> st;
    priority_queue<int, vector<int>, greater<int>> t;
    
    cin >> n;
    
    while(n--){
        cin >> tmp1 >> tmp2;
        st.push_back(make_pair(tmp1, tmp2));
    }
    
    sort(st.begin(), st.end());
    
    for(int i = 0; i < st.size(); i++){
        t.push(st[i].second);
        if(t.top() <= st[i].first) t.pop();
    }
    
    cout << t.size();
    
    
    return 0;
}