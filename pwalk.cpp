#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct qu {
    int n;
    int d;
} ;

int main(int argc, const char * argv[]) {
    int n, q, debug = 0;
    cin >> n >> q;
    int adj[n+1][n+1];
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            adj[i][j] = 0;
        }
    }
    for (int i = 1; i < n; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a][b] = c;
        adj[b][a] = c;
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (debug) cout << adj[i][j] << " ";
        }
        if (debug) cout << endl;
    }
    for (int i = 1; i <= q; i ++) {
        if (debug) cout << "i = " << i << endl;
        queue<qu> query;
        qu s, u, v;
        int a;
        cin >> s.n >> a;
        s.d = 0;
        query.push(s);
        int vis[n+1];
        for (int j = 1; j <=n; j ++) {
            vis[j] = 0;
        }
        while (query.size() != 0) {
            u = query.front();
            if (u.n == a) break;
            if (debug) cout << "u: " << u.n << " " << u.d << endl;
            query.pop();
            for (int j = 1; j <= n; j ++) {
                if (debug) cout << "entered" << endl;
                if (adj[j][u.n] != 0 and !vis[j]) {
                    v.n = j;
                    v.d = u.d + adj[j][u.n];
                    if (debug) cout << "v: " << v.n << " " << v.d << endl;
                    query.push(v);
                }
            }
            vis[u.n] = 1;
            if (debug) cout  << "visited: ";
            for (int j = 1; j <= n; j ++) if (debug) cout << vis[j] << " ";
            if (debug) cout << endl;
        }
        cout << u.d << endl;
        
    }
    return 0;
}
