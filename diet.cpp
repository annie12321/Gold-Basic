#include <iostream>
using namespace std;

int dp[45001];

int main(int argc, const char * argv[]) {
    int c, n;
    cin >> c >> n;
    dp[0] = 1;
    for (int i = 0; i < n; i ++) {
        int h;
        cin >> h;
        for (int j = c; j >= 0; j --) {
            if (dp[j] and j+h<=c) {
                dp[j+h] = 1;
            }
        }
    }
    for (int i = c; i >= 0; i --) {
        if (dp[i] == 1) {
            cout << i;
            return 0;
        }
    }
    return 0;
}
