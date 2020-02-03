#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int,int> pairs;

int vis[50001], ans[50001];
vector<pairs> adj[50001];

int main(int argc, const char * argv[]) {
    int v, e, s;
    cin >> v >> e >> s;
    
    for (int i = 1; i <= e; i ++) {
        int s, e, l;
        cin >> s >> e >> l;
        adj[s].emplace_back(e, l);
        adj[e].emplace_back(s, l);
    }
    for (int i=1; i<=v; i++) {
        ans[i] = -1;
    }
    priority_queue<pairs> p;
    p.push(make_pair(0, s));
    
    while (!p.empty()) {
        pairs z = p.top();
        int x = z.first; // distance
        int y = z.second; // node
        p.pop();
        
        if (!vis[y]) {
            vis[y] = 1;
            for (auto i: adj[y]) {
                p.push(make_pair(-i.second + x, i.first));
            }
            ans[y] = -x;
        }
        
    }
    for (int i = 1; i <= v; i ++) {
        cout << ans[i] << endl;
    }
    
    return 0;
}
