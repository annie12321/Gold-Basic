#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    int n, m, t;
    cin >> n >> m >> t;
    int best[n+1][n+1];
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            best[i][j] = 1000000000;
        }
    }
    for (int i = 0; i < m; i ++) {
        int s, e, h;
        cin >> s >> e >> h;
        s--; e--;
        best[s][e] = min(h, best[s][e]);
    }
    for (int k = 0; k < n; k ++) {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                best[i][j]=min(best[i][j], max(best[i][k],best[k][j]));
            }
        }
    }
    for (int i = 0; i < t; i ++) {
        int s, e;
        cin >> s >> e;
        if (best[s-1][e-1] == 1000000000) {
            cout << "-1" << endl;
        }
        else cout << best[s-1][e-1] << endl;
    }
    
    return 0;
}


/*
 for k=1...N
    for i=1...N
        for j=1...N
            best[i][j]=min(best[i][j], max(best[i][k],best[k][j]))
*/
