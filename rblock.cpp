#include <iostream>
#include <algorithm>    // std::copy

using namespace std;

int adj[100+1][100+1], vis[100+1], from[100+1], oldfrom[100+1];
int dist[100+1], minC[99+1];

int sp(int n) {
    for (int i = 1; i <= n; i ++) {
        dist[i] = 100000000000000;
        vis[i] = 0;
        from[i] = 0; 
    }
    dist[1] = 0;
    for (int i = 1; i <= n; i ++) {
        int minV = 100000000000000;
        int minI = 1;
        for (int j = 1; j <= n; j ++) {
            if (dist[j] < minV and !vis[j]) {
                minV = dist[j];
                minI = j;
            }
        }
        //cout << "minI = " << minI << endl;
        for (int j = 1; j <= n; j ++) {
            if (adj[minI][j] and dist[j] > dist[minI] + adj[minI][j]) {
                dist[j] = dist[minI] + adj[minI][j];
                from[j] = minI;
            }
        }
        vis[minI] = 1;
    }
    return dist[n];
} ;

int main(int argc, const char * argv[]) {
    int n, m, debug = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int s, e, l;
        cin >> s >> e >> l;
        adj[s][e] = adj[e][s] = l;
    }
    unsigned long long int oDistance = sp (n);
    std::copy_n(from, 101, oldfrom);
    if (debug) cout << oDistance << endl;
    int back = n;
    while (back > 1) {
        adj[oldfrom[back]][back] *= 2;
        adj[back][oldfrom[back]] *= 2;
        minC[back] = sp (n);
        adj[back][oldfrom[back]] /= 2;
        adj[oldfrom[back]][back] /= 2;
        back = from[back];
    }
    int distance = 0;
    for (int i = 1; i <= n; i ++) {
        if (minC[i] != 0) distance = max (minC[i], distance);
    }
    cout << distance - oDistance;
    return 0;
}

