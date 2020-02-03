#include <iostream>
using namespace std;
int debug = 0;

int dp[501][10001];
int n, m;

void print_dp (){
    for (int i = 0; i <= m; i ++) {
        for (int j = 0; j <= n; j ++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cin >> n >> m;
    int dist[n+1];
    for (int i = 1; i <= n; i ++)
        cin >> dist[i];
    for (int i = 0; i <= m; i ++)
        for (int j = 0; j <= n; j ++)
            dp[i][j] = -1;
    dp[0][0] = 0;
    for (int j = 1; j <= n; j ++) {
        for (int i = 0; i <= m; i ++) {
            if (debug) cout << "i="<<i<<",j="<<j<<endl;
            /*
            if (i == 0) dp[i][j] = max (dp[i+1][j-1], dp[i][j-1]);
            else if (dp[i-1][j-1] == -1) dp[i][j] = -1;
            else if (i == m or dp[i+1][j-1] == -1) dp[i][j] = dp[i-1][j-1] + dist[j];
            else dp[i][j] = max (dp[i-1][j-1] + dist[j], dp[i+1][j-1]);
             */
            int a, b;
            if (i==0) // first row
                a = dp[i][j-1];
            else
                a = (dp[i-1][j-1]==-1) ? -1 : dp[i-1][j-1]+dist[j];
            
            if (i==m) // last row
                b = -1;
            else
                b = (dp[i+1][j-1]==-1) ? -1 : dp[i+1][j-1];
            dp[i][j] = max (a, b);
            if (debug) print_dp();
        }
    }

    cout << dp[0][n];
    return 0;
}
