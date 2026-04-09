#include <iostream>
#include <vector>
#define MAX 4e6
using namespace std;

int N;
vector<int> numbers;

void sieve(int n) {
    // 0과 1은 소수가 아니므로 false, 나머지는 true로 초기화
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        // is_prime[p]가 true이면 소수
        if (is_prime[p]) {
            // p의 배수들을 false로 변경
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }

    // 소수 출력
    for (int p = 2; p <= n; p++) {
        if (is_prime[p])
            numbers.push_back(p);
    }
}

int main() {
    cin >> N;
    if(N == 1) {
        cout << 0;
        return 0;
    }

    if (N == 2) {
        cout << 1;
        return 0;
    }

    sieve(N);

    int left = 0;
    int right = 1;
    int value = numbers[left] + numbers[right];
    int ans = 0;
    while(left < right) {
        if(value == N) {
            ans++;
        }

        if(value > N) {
            value -= numbers[left];
            left++;
        } else {            
            right++;
            value += numbers[right];
        }
    }

    for(int number : numbers) {
        if(N == number) ans++;
    }

    cout << ans;
}