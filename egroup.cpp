#include <iostream>
using namespace std;

int dp[4][30001];

int main(int argc, const char * argv[]) {
    int n, ans;
    cin >> n;
    int cow[n+1];
    for (int i = 1; i <= n; i ++) {
        cin >> cow[i];
    }
    for (int i = 1; i <= 3; i ++) {
        dp[i][1] = (cow[1] != i);
    }
    for (int i = 1; i <= n; i ++) {
        dp[1][i] = dp[1][i-1] + (cow[i] != 1);
        dp[2][i] = min (dp[1][i-1], dp[2][i-1]) + (cow[i] != 2);
        dp[3][i] = min (min (dp[1][i-1], dp[2][i-1]), dp[3][i-1]) + (cow[i] != 3);
    }
    ans = min (min (dp[1][n], dp[2][n]), dp[3][n]);
    for (int i = 1; i <= 3; i ++) {
        dp[i][n] = (cow[n] != i);
    }
    for (int i = n; i >= 1; i --) {
        dp[1][i] = dp[1][i+1] + (cow[i] != 1);
        dp[2][i] = min (dp[1][i+1], dp[2][i+1]) + (cow[i] != 2);
        dp[3][i] = min (min (dp[1][i+1], dp[2][i+1]), dp[3][i+1]) + (cow[i] != 3);
    }
    ans = min (min (ans, dp[3][1]), min (dp[1][1], dp[2][1]));
    cout << ans;
    return 0;
}
