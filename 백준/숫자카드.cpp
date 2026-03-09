#include <iostream>
#include <algorithm>
#define MAX 500001

using namespace std;

int num_list_s[MAX];
int num_list[MAX];
int N, M;

int find_card(int t) {
    int left = 0;
    int right = N - 1;
    while(left <= right) {
        int mid = (left + right) / 2;

        if(num_list_s[mid] == t) return 1;
        else if(num_list_s[mid] < t) {
            left = mid + 1;
        } else if(num_list_s[mid] > t) {
            right = mid - 1;
        }
    }

    return 0;
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        num_list_s[i] = num;
    }
    cin >> M;
    for(int i = 0; i < M; i++) {
        int num;
        cin >> num;
        num_list[i] = num;
    }

    sort(num_list_s, num_list_s + N);

    for(int i = 0; i < M; i++) {
        int res = find_card(num_list[i]);
        cout << res << " ";
    }
}