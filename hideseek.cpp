#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int,int> pairs;

int vis[50001], ans[50001];
vector<pairs> adj[50001];

int main(int argc, const char * argv[]) {
    int v, e, s, debug = 0;
    cin >> v >> e;
    for (int i = 1; i <= e; i ++) {
        int s, e;
        cin >> s >> e;
        adj[s].emplace_back(e, 1);
        adj[e].emplace_back(s, 1);
    }
    priority_queue<pairs> p;
    p.push(make_pair(0, 1));
    
    while (!p.empty()) {
        pairs z = p.top();
        int x = z.first; // distance
        int y = z.second; // node
        if (debug) cout << "node = " << y << ", distance = " << -x << endl;
        p.pop();
        
        if (!vis[y]) {
            vis[y] = 1;
            if (debug) cout << y << " visited" << endl;
            for (auto i: adj[y]) {
                p.push(make_pair(-i.second + x, i.first));
                if (debug) cout << i.second - x << " " << i.first << endl;
            }
            ans[y] = -x;
        }
        
    }
    int minV = 1000000000, minI, cnt = 0;
    for (int i = v; i >= 1; i --) {
        if (ans[i] < minV and ans[i] != 0) {
            minV = ans[i];
            minI = i;
        }
    }
    for (int i = 1; i <= v; i ++) {
        if (ans[i] == minV) cnt ++;
    }
    cout << minI << " " << minV << " " << cnt;
    return 0;
}
