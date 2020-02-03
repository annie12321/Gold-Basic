#include <iostream>
#include <queue>
using namespace std;

struct point {
    int x;
    int t;
} ;

int main(int argc, const char * argv[]) {
    int n, k, debug = 0, done = 0;
    cin >> n >> k;
    if (n == k) {
        cout << "0"; // corner case
        return 0;
    }
    if (n > k) {
        cout << n - k;
        return 0;
    }
    int vis[2*k];
    for (int i = 0; i < 2*k; i ++) {
        vis[i] = 0;
    }
    queue<point> q;
    point s, u, v;
    s = {n, 0};
    q.push(s);
    if (debug) cout << "s: " << s.x << " " << s.t << endl;
    while (!done) {
        u = q.front();
        if (debug) cout << "u: " << u.x << " " << u.t << endl;
        q.pop();
        v = {u.x + 1, u.t + 1};
        if (v.x == k) done = 1;
        if (v.x <= 2*k and !vis[v.x]) {
            if (debug) cout << "v: " << v.x << " " << v.t << endl;
            q.push(v);
            vis[v.x] = 1;
        }
        v = {u.x - 1, u.t + 1};
        if (v.x == k) done = 1;
        if (v.x >= 0 and !vis[v.x]) {
            if (debug) cout << "v: " << v.x << " " << v.t << endl;
            q.push(v);
            vis[v.x] = 1;
        }
        v = {u.x*2, u.t + 1};
        if (v.x == k) done = 1;
        if (v.x >= 0 and v.x <= 2*k and !vis[v.x]) {
            if (debug) cout << "v: " << v.x << " " << v.t << endl;
            q.push(v);
            vis[v.x] = 1;
        }
    }
    cout << v.t;
    return 0;
}
