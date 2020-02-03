#include <iostream>
using namespace std;

int adj[2500+1][2500+1], dist[2500+1], vis[2500+1];

int main(int argc, const char * argv[]) {
    int n, c, s, e, debug = 0;
    cin >> n >> c >> s >> e;
    for (int i = 1; i <= n; i ++) {
        dist[i] = 1000000000;
    }
    for (int i = 1; i <= c; i ++) {
        int s, e, c;
        cin >> s >> e >> c;
        adj[s][e] = c;
        adj[e][s] = c;
    }
    dist[s] = 0;
    for (int i = 1; i <= n; i ++) {
        int minV = 1000000000, minI;
        for (int j = 1; j <= n; j ++) {
            if (dist[j] < minV and !vis[j]) {
                minV = dist[j];
                minI = j;
            }
        }
        for (int j = 1; j <= n; j ++) {
            if (adj[minI][j]) dist[j] = min (dist[j], dist[minI] + adj[minI][j]);
        }
        vis[minI] = 1;
        if (debug) cout << minI << " ";
    }
    if (debug) cout << endl;
    cout << dist[e];
    return 0;
}
