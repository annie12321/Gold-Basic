#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef pair<int,int> pairs;

int vis[50000];
int v, e, ans;


int main(int argc, const char * argv[]) {
    cin >> v >> e;
    
    vector<pairs> adj[v];
    for (int i = 0; i < e; i ++) {
        int s, e, l;
        cin >> s >> e >> l;
        s --; e --;
        adj[s].emplace_back(e, l);
        adj[e].emplace_back(s, l);
    }
    
    priority_queue<pairs> s;
    s.push(make_pair(0, 0));
    
    while(!s.empty()) {
        pairs z = s.top();
        int x = z.first;
        int y = z.second; // y is the node
        s.pop();
        
        if (!vis[y]) {
            vis[y] = 1;
            for (auto i: adj[y]) {
                s.push(make_pair(-i.second, i.first));
            }
            ans += -x;
        }
    }
    cout << ans;
    return 0;
}
