#include <iostream>
using namespace std;

int adj[1000+1][1000+1], dist[1000+1], vis[1000+1];

int main(int argc, const char * argv[]) {
    int p, w, b, debug = 0; // #pastures, #ways/paths, #bulls
    cin >> p >> w >> b;
    for (int i = 1; i <= w; i ++) {
        int s, e, l;
        cin >> s >> e >> l;
        if (adj[s][e] == 0){
            adj[s][e] = adj[e][s] = l;
        }
        else
        adj[s][e] = adj[e][s] = min(adj[e][s], l);
        dist[i] = 1000000000;
    }
    dist[1] = 0;
    for (int i = 1; i <= p; i ++) {
        int minV = 1000000000, minI;
        for (int j = 1; j <= p; j ++) {
            if (dist[j] < minV and !vis[j]) {
                minV = dist[j];
                minI = j;
            }
        }
        if (debug) cout << minI << ": " << minV << endl;
        for (int j = 1; j <= p; j ++) {
            if (adj[minI][j]) dist[j] = min (dist[j], dist[minI] + adj[minI][j]);
            if (debug) cout << "dist[" << j << "] = " << dist[j] << endl;
        }
        vis[minI] = 1;
    }
    for (int i = 1; i <= b; i ++) {
        int bu, c;
        cin >> bu >> c;
        if (debug) cout << bu << " " << c << "...";
        if(debug) cout << dist[bu] << " " << dist[c] << " -->";
        cout << dist[bu] + dist[c] << endl;
    }
    return 0;
}
