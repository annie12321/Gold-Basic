#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct met {
    int x;
    int y;
    int t;
} ;

struct point {
    int r;
    int c;
    int time;
} ;

bool comp (const met &a, const met &b);

int main(int argc, const char * argv[]) {
    int m, safe = 0, debug = 0;
    cin >> m;
    vector<met> meteor(m);
    for (int i = 0; i < m; i ++) {
        cin >> meteor[i].x >> meteor[i].y >> meteor[i].t;
    }
    int f[301][301], vis[301][301];
    for (int i = 0; i < 301; i ++) {
        for (int j = 0; j < 301; j ++) {
            f[i][j] = -1;
            vis[i][j] = 0;
        }
    }
    sort (meteor.begin(), meteor.end(), comp);
    for (int i = 0; i < m; i ++) {
        f[meteor[i].y][meteor[i].x] = meteor[i].t;
        if (meteor[i].y > 0)   f[meteor[i].y - 1][meteor[i].x] = meteor[i].t;
        if (meteor[i].y < 300) f[meteor[i].y + 1][meteor[i].x] = meteor[i].t;
        if (meteor[i].x > 0)   f[meteor[i].y][meteor[i].x - 1] = meteor[i].t;
        if (meteor[i].x < 300) f[meteor[i].y][meteor[i].x + 1] = meteor[i].t;
    }
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            if (debug) cout << f[i][j] << " ";
        }
        if (debug) cout << endl;
    }
    queue<point> q;
    point s, u, v;
    s = {0, 0, 0};
    q.push(s);
    while (!q.empty() and !safe) {
        u = q.front();
        if (debug) cout << "u: " << u.r << " " << u.c << " " << u.time << endl;
        q.pop();
        v = {u.r + 1, u.c, u.time + 1};
        if (f[v.r][v.c] < 0 and v.r < 301) safe = 1;
        if (v.time < f[v.r][v.c] and !vis[v.r][v.c] and v.r < 301) {
            if (debug) cout << "v: " << v.r << " " << v.c << " " << v.time << endl;
            q.push(v);
            vis[v.r][v.c] = 1;
        }
        v = {u.r - 1, u.c, u.time + 1};
        if (f[v.r][v.c] < 0 and v.r >= 0) safe = 1;
        if (v.time < f[v.r][v.c] and !vis[v.r][v.c] and v.r >= 0) {
            if (debug) cout << "v: " << v.r << " " << v.c << " " << v.time << endl;
            q.push(v);
            vis[v.r][v.c] = 1;
        }
        v = {u.r, u.c + 1, u.time + 1};
        if (f[v.r][v.c] < 0 and v.c < 301) safe = 1;
        if (v.time < f[v.r][v.c] and !vis[v.r][v.c] and v.c < 301) {
            if (debug) cout << "v: " << v.r << " " << v.c << " " << v.time << endl;
            q.push(v);
            vis[v.r][v.c] = 1;
        }
        v = {u.r, u.c - 1, u.time + 1};
        if (f[v.r][v.c] < 0 and v.c >= 0) safe = 1;
        if (v.time < f[v.r][v.c] and !vis[v.r][v.c] and v.c >= 0) {
            if (debug) cout << "v: " << v.r << " " << v.c << " " << v.time << endl;
            q.push(v);
            vis[v.r][v.c] = 1;
        }
    }
    if (!safe) {
        cout << "-1";
        return 0;
    }
    if (debug) cout << "vf: " << v.r << " " << v.c << " " << v.time << endl;
    cout << v.time;
    return 0;
}

bool comp (const met &a, const met &b) {
    return (a.t > b.t);
}
