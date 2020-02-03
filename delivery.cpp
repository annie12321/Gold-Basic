#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 101
#define M_MAX 5*N_MAX


int debug = 0;
int debug1 = 0; // shortest path
int debug2 = 0; // is_path_x/y

int N;
int CNT=0;
int G[M_MAX][M_MAX];
int e[M_MAX];
int z[M_MAX];

set<pair<int,int>> nodeset;
vector<pair<int,int>> nodes(N_MAX);
vector<pair<int,int>> nodes5(M_MAX);
vector<int> idx(N_MAX);

void print_G () {
    cout << "------------------------------"<<endl;
    cout << "G :" << endl;
    for (int i=0;i<CNT;i++) {
        for (int j=0;j<CNT;j++) {
            cout << G[i][j] << " ";
        }
        cout << endl;
    }
}

int dist (int m, int n) {
    int x1 = nodes5[m].first;
    int x2 = nodes5[n].first;
    int y1 = nodes5[m].second;
    int y2 = nodes5[n].second;
    return (abs(x1-x2)+abs(y1-y2));
}

// shortest path from node a to node b
int sp(int a, int b) {
    
    // initialization
    for (int i=0;i<CNT;i++) {
        e[i] = 1e9;
        z[i] = 0;
    }
    for (int i=0;i<N;i++) {
        z[idx[i]] = 1;
    }
    e[idx[a]] = 0;
    z[idx[a]] = 0; z[idx[b]] = 0;

    pair<int,int> s = {0, idx[a]};
    
    priority_queue<pair<int,int>> Q;
    Q.push(s);
    
    int d, m;
    while (!Q.empty()) {
        pair<int,int> u = Q.top(); Q.pop();
        d = u.first; m = u.second;
        if (debug1) cout << "Pop {"<<d<<","<<m<<"("<<nodes5[m].first<<","<<nodes5[m].second<<")} from queue"<<endl;
        
        if (m==idx[b]) break;
        if (z[m]) continue;
        
        z[m] = 1;
        for (int i=0;i<CNT;i++) {
            //if (debug) cout <<"i="<<i<<",G[m][i]="<<G[m][i]<<",e[i]="<<e[i]<<",e[m]="<<e[m]<<","<<dist(i,m)<<endl;
            if (G[m][i] && e[i]> e[m] + dist(i,m)) {
                e[i] = e[m] + dist(i,m);
                Q.push({-e[i], i});
                if (debug1) cout << "Push {"<<-e[i]<<","<<i<<"("<<nodes5[i].first<<","<<nodes5[i].second<<")} to queue"<<endl;
            }
        }
        if (debug1) {
            cout << "z:"<<endl;
            for (int i=0;i<CNT;i++) {
                cout <<z[i]<< "  ";
            }
            cout <<endl;
            
            cout << "e:"<<endl;
            for (int i=0;i<CNT;i++) {
                if (e[i]==1e9)
                    cout <<"-1 ";
                else
                    cout <<e[i]<< "  ";
            }
            cout <<endl;
        }
    }
    
    return e[idx[b]];
}

bool is_new_node (int x, int y) {
    int ans = false;
    if (nodeset.find({x,y}) == nodeset.end()) ans = true;
    return ans;
}

bool is_path_x(int x, int y1, int y2) {
    int ans = true;
    int y_min = min(y1,y2); int y_max = max(y1,y2);
    for (int i=1;i<=N;i++) {
        if (x==nodes[i].first && y_min<nodes[i].second && y_max>nodes[i].second) ans = false;
    }
    if (debug2) cout << "is_path_x("<<x<<","<<y1<<","<<y2<<") = "<<ans<<endl;
    return ans;
}

bool is_path_y(int x1, int x2, int y) {
    int ans = true;
    int x_min = min(x1,x2); int x_max = max(x1,x2);
    for (int i=1;i<=N;i++) {
        if (y==nodes[i].second && x_min<nodes[i].first && x_max>nodes[i].first) ans = false;
    }
    if (debug2) cout << "is_path_y("<<x1<<","<<x2<<","<<y<<") = "<<ans<<endl;
    return ans;
}

bool is_path (int x1, int y1, int x2, int y2) {
    int ans;
    ans = (x1==x2) || (y1==y2) || nodeset.find({x1,y2})==nodeset.end();
    if (ans && is_path_x(x1,y1,y2) && is_path_y(x1,x2,y2)) {
        ans = true;
        if (debug2) cout << "\tis_path("<<x1<<","<<y1<<","<<x2<<","<<y2<<") = "<<ans<<endl;
        return ans;
    }
    
    ans = (x1==x2) || (y1==y2) || nodeset.find({x2,y1})==nodeset.end();
    if (ans && is_path_y(x1,x2,y1) && is_path_x(x2,y1,y2)) {
        ans = true;
        if (debug2) cout << "\tis_path("<<x1<<","<<y1<<","<<x2<<","<<y2<<") = "<<ans<<endl;
        return ans;
    }
    if (debug2) cout << "\tis_path("<<x1<<","<<y1<<","<<x2<<","<<y2<<") = "<<ans<<endl;
    return false;
}



int main(int argc, const char * argv[]) {
    cin >> N;
    
    for (int i=1;i<=N;i++) {
        int a, b;
        cin >> a >> b;
        nodes[i] = {a,b};
        nodeset.insert({a,b});
    }
    
    if (debug) cout <<"is_new_node(6,5)="<<is_new_node(6,5)<<endl;
    
    int cnt=0;
    for (int i=1;i<=N;i++) {
        nodes5[cnt++] = nodes[i]; idx[i] =cnt-1;
        int x = nodes[i].first;
        int y = nodes[i].second;
        if (is_new_node(x+1,y)) nodes5[cnt++] = {x+1,y};
        if (is_new_node(x-1,y)) nodes5[cnt++] = {x-1,y};
        if (is_new_node(x,y+1)) nodes5[cnt++] = {x,y+1};
        if (is_new_node(x,y-1)) nodes5[cnt++] = {x,y-1};
    }
    
    for (int i=0;i<cnt;i++){
        for (int j=i+1;j<cnt;j++) {
            if (is_path(nodes5[i].first, nodes5[i].second, nodes5[j].first, nodes5[j].second)){
                G[i][j] = 1;
                G[j][i] = 1;
            }
        }
    }
    
    
    CNT = cnt;
    
    if (debug) {
        for (int i=0;i<cnt;i++){
            cout << "i="<<i<<": "<<nodes5[i].first<<","<<nodes5[i].second<<endl;
        }
    }
    
    if (debug) print_G();
    
    if (debug) is_path(6,4,5,5);
    if (debug) is_path(6,4,6,5);
    
    cout << "Result: ";
    int total=0;
    for (int i=1;i<N;i++) {
        int t = sp(i,i+1);
        if (debug) cout << "sp("<<i<<","<<i+1<<")="<<t<<endl;
        if (t<1e9)
            total = total + t;
        else {
            cout << -1 << endl;
            return 0;
        }
    }
    
    int t = sp(N,1);
    
    if (debug) cout << "sp("<<N<<","<<1<<")="<<t<<endl;
    if (t<1e9)
        cout << total + t << endl;
    else
        cout << -1 << endl;

    return 0;
    
}
