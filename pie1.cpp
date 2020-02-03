#include <iostream>
using namespace std;

int pies[100+1][100+1], dp[100+1][100+1];

int main(int argc, const char * argv[]) {
    int r, c;
    cin >> r >> c;
    for (int i = 1; i <= r; i ++) {
        for (int j = 1; j <= c; j ++) {
            cin >> pies[i][j];
        }
    }
    
    for (int i = 1; i <= r; i ++) {
        for (int j = 1; j < i; j ++) {
            pies[i][j] = 0;
            
        }
    }
    dp[1][1] = pies[1][1];
    for (int j = 2; j <= c; j ++) {
        for (int i = 1; i <= r; i ++) {
            dp[i][j] = dp[i][j] + pies[i][j] + max(max(dp[i][j-1], dp[i-1][j-1]), dp[i+1][j-1]);
        }
    }
    cout << dp[r][c];
    return 0;
}
