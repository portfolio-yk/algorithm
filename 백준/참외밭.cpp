#include <iostream>
#include <vector>
using namespace std;

int N;

int main() {
    cin >> N;

    int direction[6];
    int length[6];

    for(int i = 0; i < 6; i++) {
        int d, l;
        cin >> d >> l;
        direction[i] = d;
        length[i] = l;
    }

    vector<int> longest_index;
    vector<int> shortes_index;

    for(int i = 0; i < 6; i++) {
        int a = direction[i];
        int b = 0;
        for(int j = 0; j < 6; j++) {
            if(direction[j] == a) {
                b++;
            }
        }
        if(b == 1) longest_index.push_back(i);
    }

    int first_long = longest_index.front();
    int seconde_long = longest_index.back();
    int first_short = (first_long + 3) % 6;
    int seconde_short = (seconde_long + 3) % 6;
    
    cout << N * (length[first_long] * length[seconde_long] - (length[first_short] * length[seconde_short]));
}