#include<iostream>
#include<vector>
#define MAX 100
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
    long long N, X;
    long long jump[MAX];
	for(test_case = 1; test_case <= T; ++test_case)
	{
long long N, X;
        cin >> N >> X;
        X = abs(X); // 거리는 절대값으로 계산

        vector<long long> jump(N);
        long long total_sum = 0;
        long long max_in_one_cycle = 0;

        for (int i = 0; i < N; i++) {
            cin >> jump[i];
            total_sum += jump[i];
            if (jump[i] > max_in_one_cycle) max_in_one_cycle = jump[i];
        }

        // X가 0이면 0번 점프 (문제 조건에 따라 0 또는 N 확인 필요)
        if (X == 0) {
            cout << "0" << "\n";
            continue;
        }

        long long count = 0;
        long long current_sum = 0;
        long long current_max = 0;

        // 1. X가 매우 큰 경우, total_sum을 이용해 빠르게 점프 횟수를 줄임
        // 안전을 위해 X가 total_sum의 2배 정도 남을 때까지만 건너뜁니다.
        if (X > total_sum * 2 && total_sum > 0) {
            long long cycles = (X / total_sum);
            count = cycles * N;
            current_sum = cycles * total_sum;
            current_max = max_in_one_cycle;
        }

        // 2. 한 땀 한 땀 점프하며 삼각형 부등식 조건 체크
        for (int i = 0; ; i++) {
            // 이미 위에서 cycles만큼 뛰었다면 i는 그 다음부터 시작하는 효과
            long long d = jump[i % N];
            current_sum += d;
            if (d > current_max) current_max = d;
            count++;

            // 도달 조건 판단 (삼각형 부등식)
            if (count == 1) {
                // 한 번 점프할 때는 정확히 일치해야 함
                if (current_sum == X) break;
            } else {
                // 여러 번 점프할 때는:
                // 1. 모든 점프의 합이 X보다 크거나 같아야 함
                // 2. 가장 긴 점프 하나가 (나머지 점프들 합 + X)보다 작거나 같아야 함 (삼각형 형성 가능 조건)
                if (current_sum >= X && current_max <= (current_sum - current_max) + X) {
                    break;
                }
            } 
        }
        if (count > 100000000) {
            cout << "-1\n";
            return 0;
        }
        cout << count << "\n";
	}
	return 0;
}