#include <iostream>
using namespace std;

int adj[2500+1][2500+1], dist[2500+1], vis[2500+1];
int main(int argc, const char * argv[]) {
    int v, e, s;
    cin >> v >> e >> s;
    for (int i = 1; i <= e; i ++) {
        int s, e, l;
        cin >> s >> e >> l;
        adj[s][e] = l;
        adj[e][s] = l;
    }
    for (int i = 1; i <= v; i ++) {
        dist[i] = 1000000000;
    }
    dist[s] = 0;
    for (int i = 1; i <= v; i ++) {
        int minV = 1000000000, minI;
        for (int j = 1; j <= v; j ++) {
            if (dist[j] < minV and !vis[j]) {
                minV = dist[j];
                minI = j;
            }
        }
        
        for (int j = 1; j <= v; j ++) {
            if (adj[minI][j]) dist[j] = min(dist[minI] + adj[minI][j], dist[j]);
        }
        vis[minI] = 1;
    }
    for (int i = 1; i <= v; i ++) {
        if (dist[i] == 1000000000) cout << "-1" << endl;
        else cout << dist[i] << endl;
    }
    return 0;
}
