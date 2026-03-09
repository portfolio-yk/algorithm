#include <iostream>
#define MAX 100000

using namespace std;


int N;
int numbers[MAX];

int main() {
    int left, right;
    int ans;
    cin >> N;

    left = 0;
    right = N - 1;

    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        numbers[i] = num;
    }
    int diff = abs(numbers[left] + numbers[right]);
    int ans_left = left;
    int ans_right = right;
    while(left < right) {
        int sum = numbers[left] + numbers[right];
        
        if(diff >= abs(sum)) {
            diff = abs(sum);
            ans_left = left;
            ans_right = right;
        }
        
        if(sum == 0) {
            left += 1;
            right -= 1;
        } else if(sum < 0) {
            left += 1;
        } else {
            right -= 1;
        }
    }

    cout << numbers[ans_left] << " " << numbers[ans_right];
    return 0;
}