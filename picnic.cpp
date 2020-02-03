#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int debug = 0;

#define N_MAX 1001
#define K_MAX 101
#define INF -1

struct component {
    long int x;
    long int y;
};

vector<int> C(K_MAX);
vector<vector<int>> G(N_MAX);

bool cmp (component a, component b) {
    return (a.y < b.y);
}

int K, N, M;

int dp[K_MAX][N_MAX];

void print_dp () {
    cout << "===========dp============"<<endl;
    for (int i=0;i<=K;i++) {
        for (int j=1;j<=N;j++) {
            if (dp[i][j]== INF)
                cout << "-1 ";
            else
                cout << dp[i][j] << "  ";
        }
        cout << endl;
    }
}

void bfs(int c) {
    int s = C[c];
    queue<int> q;
    q.push(s);
    if (debug) cout << "Push start node "<<s<<" into queue"<<endl;
    while (q.size()>0) {
        int u = q.front(); q.pop();
        if (debug) cout << "Get node "<<u<<" from queue"<<endl;
        if (dp[c][u]>0)
            continue;
        else {
            dp[c][u]=1;
            dp[0][u]++;
        }
        for (int i=0;i<G[u].size();i++) {
            int v = G[u][i];
            if (dp[c][v]<0) {
                q.push(v);
                if (debug) cout << "Push "<<v<<" into queue"<<endl;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> K >> N >> M;
    
    for (int i=1;i<=K;i++) {
        cin >> C[i];
    }
    
    for (int i=0;i<M;i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }
    
    for (int i=0;i<=K;i++) {
        for (int j=0;j<=N;j++) {
            if (i==0) dp[i][j]=0;
            else dp[i][j] = INF;
        }
    }
    
    if (debug) print_dp();
    for (int i=1;i<=K;i++) {
        bfs(i);
        if (debug) print_dp();
    }
    
    int ans=0;
    for (int i=0;i<=N;i++) {
        if (dp[0][i]==K) ans++;
    }
    cout << "Results:"<<ans<<endl;
    
    return 0;
}
