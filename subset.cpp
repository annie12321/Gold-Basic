#include <iostream>
using namespace std;

long dp[40][400];

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    dp[0][0] = 1;
    if (n*(n+1)%4 != 0) {
        cout << "0";
        return 0;
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j <= n*(n+1)/4; j ++) {
            dp[i][j] = dp[i-1][j] + dp[i-1][j-i];
        }
    }
    cout << dp[n][n*(n+1)/4]/2;
    return 0;
}
