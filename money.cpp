#include <iostream>
using namespace std;

#define int long long

int dp[10001];

main() {
    int n, c;
    cin >> n >> c;
    dp[0] = 1;
    for (int i = 0; i < n; i ++) {
        int v;
        cin >> v;
        for (int j = 0; j < c; j ++) {
            if (dp[j] != 0 and j+v<=c) {
                dp[j+v] += dp[j];
            }
        }
    }
    cout << dp[c];
    return 0;
}
