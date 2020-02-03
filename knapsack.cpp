#include <iostream>
#include <vector>
using namespace std;

int dp[1000+1][5000+1];

struct obj {
    int s;
    int v;
} ;

int main() {
    int n, c;
    cin >> n >> c;
    vector<obj> object(n+1);
    for (int i = 1; i <= n; i ++) {
        cin >> object[i].s >> object[i].v;
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= c; j ++) {
            if (j-object[i].s < 0) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max (dp[i-1][j], dp[i-1][j-object[i].s] + object[i].v);
        }
    }
    cout << dp[n][c];
}
