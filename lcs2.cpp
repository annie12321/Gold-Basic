#include <iostream>
using namespace std;

int dp[3][10001];

int main(int argc, const char * argv[]) {
    string a, b;
    getline (cin, a);
    getline (cin, b);
    if (a[0] == b[0]) dp[1][1] = 1;
    for (int i = 2; i <= a.length(); i ++) {
        dp[1][i] = dp[1][i-1];
        if (a[i-1] == b[0] and dp[1][i-1] == 0) dp[1][i] ++;
    }
    for (int i = 1; i < b.length(); i ++) {
        if (b[i] == a[0]) dp[2][1] = 1;
        for (int j = 2; j <= a.length(); j ++) {
            if (a[j-1] == b[i]) dp[2][j] = dp[1][j-1] + 1;
            else dp[2][j] = max (dp[1][j], dp[2][j-1]);
        }
        for (int j = 1; j <= a.length(); j ++) {
            swap (dp[1][j], dp[2][j]);
        }
    }
    cout << dp[1][a.length()];
    return 0;
}
