#include <iostream>
#include <vector>

using namespace std;

int N, S;

int main() {
    cin >> N >> S;

    vector<int> numbers;

    for(int i = 0; i < N; i++) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    int left = 0;
    int right = 0;
    int sum = numbers[0];
    int min_length = 1000000;
    while(1) {
        if(sum >= S) {
            min_length = min(min_length, right - left + 1);
            sum -= numbers[left];
            left += 1;
        } else {
            right += 1;
            if(right > N - 1) break;
            sum += numbers[right];
        }
    }

    if(min_length == 1000000) {
        cout << "0";
        exit(0);
    }
    cout << min_length;
}