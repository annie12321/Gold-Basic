#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct point {
    int x;
    int y;
} ;

int main(int argc, const char * argv[]) {
    int n, m;
    cin >> n >> m;
    vector<point> points(n+1);
    double adj[n+1][n+1], val[n+1], ans = 0;
    int vis[n+1];
    for (int i = 1; i <= n; i ++) {
        cin >> points[i].x >> points[i].y;
        val[i] = 1000000000;
        vis[i] = 0;
    }
    val[1] = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <=n; j ++) {
            adj[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <=n; j ++) {
            if (i == j) adj[i][j] = 0;
            else {
                adj[i][j] = sqrt(pow((points[i].x - points[j].x), 2.0) + pow((points[i].y - points[j].y), 2.0));
                adj[j][i] = sqrt(pow((points[i].x - points[j].x), 2.0) + pow((points[i].y - points[j].y), 2.0));
            }
        }
    }
    for (int i = 1; i <= m; i ++) {
        int s, e;
        cin >> s >> e;
        adj[s][e] = 0;
        adj[e][s] = 0;
    }
    for (int i = 1; i <=n; i ++) {
        double minV = 1000000000;
        int minI;
        for (int j = 1; j <= n; j ++) {
            if (val[j] < minV and !vis[j]) {
                minV = val[j];
                minI = j;
            }
        }
        vis[minI] = 1;
        ans += minV;
        for (int j = 1; j <=n; j ++) {
            val[j] = min (val[j], adj[minI][j]);
        }
        
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}
