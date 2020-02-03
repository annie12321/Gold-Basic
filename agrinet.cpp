#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    int n, ans = 0;
    cin >> n;
    int adj[n+1][n+1], vis[n+1], val[n+1];
    for (int i = 1; i <= n; i ++) {
        vis[i] = 0;
        val[i] = 1000000000;
        for (int j = 1; j <=n; j ++) {
            cin >> adj[i][j];
        }
    }
    val[1] = 0;
    for (int i = 1; i <=n; i ++) {
        int min1 = 100001, minI;
        for (int j = 1; j <= n; j ++) {
            if (val[j] < min1 and !vis[j]) {
                min1 = val[j];
                minI = j;
            }
        }
        vis[minI] = 1;
        ans += min1;
        for (int j = 1; j <=n; j ++) {
            val[j] = min(val[j], adj[minI][j]);
            
        }
    }
    cout << ans;
    return 0;
}
