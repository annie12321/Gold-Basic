#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    int sequence[n+1], dp[n+1];
    for (int i = 1; i <= n; i ++) {
        cin >> sequence[i];
    }
    for (int i = 1; i <= n; i ++) {
        dp[i] = 1;
        for (int j = 1; j < i; j ++) {
            if (sequence[j] < sequence[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    int x = 0;
    for (int i = 1; i <= n; i ++) {
        x = max (x, dp[i]);
    }
    cout << x;
    return 0;
}
