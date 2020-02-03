#include <iostream>
using namespace std;

int dp[1001][1001];

int main(int argc, const char * argv[]) {
    string a, b;
    getline (cin, a);
    getline (cin, b);
    if (a[0] != b[0]) dp[0][0] = 1;
    for (int i = 1; i < b.length(); i ++) {
        dp[i][0] = dp[i-1][0] + 1;
        if (a[0] == b[i]) dp[i][0] = i;
    }
    for (int i = 1; i < a.length(); i ++) {
        dp[0][i] = dp[0][i-1] + 1;
        if (b[0] == a[i]) dp[0][i] = i;
    }
    for (int i = 1; i < b.length(); i ++) {
        for (int j = 1; j < a.length(); j ++) {
            if (b[i] == a[j]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min (min (dp[i-1][j] + 1, dp[i][j-1] + 1), dp[i-1][j-1] + 1);
        }
    }
    cout << dp[b.length()-1][a.length()-1];
    return 0;
}
